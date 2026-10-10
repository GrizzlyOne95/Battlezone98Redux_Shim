// Direct3D 11 buffer restore: give a recreated device its vertex and index
// buffers back in place, so Ogre does not have to reload every mesh.
//
// Why: after a device loss, RenderSystem_Direct3D11's handleDeviceLost
// recreates the device and then calls MeshManager::reloadAll, because its
// hardware buffers are not device resources and die with the old device. A
// reloaded mesh makes every Entity using it re-initialise on its next frame,
// which deletes the Entity's SkeletonInstance and with it every Bone. The
// game caches raw Bone pointers in its render objects (FUN_0067e260 and
// FUN_0067e430 store them at +0xC8 and +0xCC after setManuallyControlled), so
// the first craft update after a restore (FUN_004eb7e0 -> FUN_00681a00)
// called through a freed bone: on 2026-10-08 a clean in-mission restore on an
// RTX 5080 crashed at 0x00681AAA reading 0x20. The same reload also replaces
// the sub-entities, materials and animation states the game set up, and
// loses manual meshes that have no loader.
//
// What: the renderer's D3D11HardwareBuffer keeps a CPU copy of its contents.
// Locks hand out the copy and unlocks send the written range to the GPU
// buffer (d3d11_buffer_mirror_policy.h); GPU-side copies between buffers are
// mirrored too. When handleDeviceLost reaches the mesh reload, each buffer
// that still belongs to the old device gets a new ID3D11Buffer on the new one,
// created from its copy, and the reload is skipped. Constant and stream-output
// buffers are left alone. If any buffer was seen that predates the hooks, the
// copies are incomplete and the stock reload runs as before.
//
// How: the renderer is built with incremental linking, so every call to the
// constructor, destructor, lockImpl, unlockImpl, copyDataImpl and
// handleDeviceLost goes through a five-byte jump thunk; those jumps are
// retargeted. The reload is MeshManager's vtable slot 12 (handleDeviceLost
// calls it as [vtable+0x30]). Only the renderer build the layout was read from
// (RenderSystem_Direct3D11.dll, TimeDateStamp 0x586F03D3, the same on GOG and
// Steam) is patched.
//
// Config: on with [Graphics] D3D11DeviceLossRecovery;
// OPENSHIM_DISABLE_D3D11_BUFFER_RESTORE=1 turns this part off alone.
#include "bool_token.h"
#include "com_vtable_patch.h"
#include "d3d11_buffer_mirror_policy.h"
#include "d3d11_buffer_restore.h"
#include "hook_engine.h"
#include "shim_log.h"

#include <Windows.h>
#include <d3d11.h>

#include <atomic>
#include <cstdint>
#include <cstring>
#include <string>
#include <unordered_map>

namespace BZROpenShim
{
    namespace
    {
        using namespace D3D11BufferMirror;

        constexpr char kComponent[] = "dx11-recovery";

        constexpr DWORD kRendererTimeDateStamp = 0x586F03D3;
        constexpr DWORD kRendererSizeOfImage = 0xF3000;

        // D3D11HardwareBuffer in that build, read from its constructor.
        constexpr size_t kOffSizeInBytes = 0x04;  // HardwareBuffer::mSizeInBytes
        constexpr size_t kOffD3DBuffer = 0x28;    // ID3D11Buffer* mlpD3DBuffer
        constexpr size_t kOffBufferType = 0x38;   // 0 vertex, 1 index, 2 constant
        constexpr size_t kOffDevice = 0x3C;       // D3D11Device*: +0 ID3D11Device*, +4 immediate context
        constexpr size_t kOffDesc = 0x40;         // D3D11_BUFFER_DESC mDesc
        constexpr uint32_t kConstantBuffer = 2;
        constexpr size_t kMeshManagerReloadAllSlot = 12;

        constexpr uint64_t kMirrorLogStep = 128ull << 20;

        // __thiscall functions, called and implemented as __fastcall with an
        // unused edx; the callee pops the stack arguments in both. Bools are
        // passed as whole stack slots and forwarded untouched.
        using FnCtor = void*(__fastcall*)(void*, void*, uint32_t, uint32_t, uint32_t, void*, uint32_t, uint32_t, uint32_t);
        using FnDtor = void(__fastcall*)(void*, void*);
        using FnLockImpl = void*(__fastcall*)(void*, void*, uint32_t, uint32_t, uint32_t);
        using FnUnlockImpl = void(__fastcall*)(void*, void*);
        using FnCopyDataImpl = void(__fastcall*)(void*, void*, void*, uint32_t, uint32_t, uint32_t, uint32_t);
        using FnHandleDeviceLost = void(__fastcall*)(void*, void*);
        using FnReloadAll = void(__fastcall*)(void*, void*, uint32_t);
        using FnGetSingletonPtr = void*(__cdecl*)();

        FnCtor g_RealCtor = nullptr;
        FnDtor g_RealDtor = nullptr;
        FnLockImpl g_RealLockImpl = nullptr;
        FnUnlockImpl g_RealUnlockImpl = nullptr;
        FnCopyDataImpl g_RealCopyDataImpl = nullptr;
        FnHandleDeviceLost g_RealHandleDeviceLost = nullptr;
        void* g_RealReloadAll = nullptr;

        const void* g_BufferVtable = nullptr;
        FnGetSingletonPtr g_MeshManagerPtr = nullptr;
        void* g_ExpectedReloadAll = nullptr;

        struct Mirror
        {
            uint8_t* data;      // null when the buffer predates the hooks
            size_t size;
            bool valid;         // data matches the buffer's contents
            bool locked;        // the current lock was handed the mirror
            uint32_t lockOffset;
            uint32_t lockLength;
            uint32_t lockOptions;
        };

        // Never destroyed: the renderer frees buffers during process exit,
        // after static destructors would have run.
        SRWLOCK g_MapLock = SRWLOCK_INIT;
        std::unordered_map<const void*, Mirror*>* g_Mirrors = new std::unordered_map<const void*, Mirror*>();

        std::atomic<bool> g_Active{false};
        std::atomic<bool> g_InDeviceLost{false};
        std::atomic<bool> g_RestoredThisLoss{false};
        std::atomic<bool> g_MeshHookTried{false};
        std::atomic<bool> g_MeshHookInstalled{false};

        std::atomic<uint64_t> g_MirrorBytes{0};
        std::atomic<uint64_t> g_MirrorBytesLogged{0};
        std::atomic<uint32_t> g_LateBuffers{0};
        std::atomic<uint32_t> g_Invalidated{0};
        std::atomic<uint32_t> g_AllocFailures{0};
        std::atomic<uint32_t> g_UploadFailures{0};

        template <class T>
        T& Field(const void* object, size_t offset)
        {
            return *reinterpret_cast<T*>(const_cast<uint8_t*>(static_cast<const uint8_t*>(object)) + offset);
        }

        ID3D11Device* DeviceOf(const void* buffer)
        {
            auto* wrapper = Field<uint8_t*>(buffer, kOffDevice);
            return wrapper ? *reinterpret_cast<ID3D11Device**>(wrapper) : nullptr;
        }

        ID3D11DeviceContext* ContextOf(const void* buffer)
        {
            auto* wrapper = Field<uint8_t*>(buffer, kOffDevice);
            return wrapper ? *reinterpret_cast<ID3D11DeviceContext**>(wrapper + 4) : nullptr;
        }

        bool IsMirrorable(const void* buffer)
        {
            return Field<uint32_t>(buffer, kOffBufferType) != kConstantBuffer &&
                   (Field<D3D11_BUFFER_DESC>(buffer, kOffDesc).BindFlags & D3D11_BIND_STREAM_OUTPUT) == 0;
        }

        Mirror* Find(const void* buffer)
        {
            AcquireSRWLockShared(&g_MapLock);
            const auto it = g_Mirrors->find(buffer);
            Mirror* mirror = it == g_Mirrors->end() ? nullptr : it->second;
            ReleaseSRWLockShared(&g_MapLock);
            return mirror;
        }

        void Insert(const void* buffer, Mirror* mirror)
        {
            AcquireSRWLockExclusive(&g_MapLock);
            Mirror*& slot = (*g_Mirrors)[buffer];
            Mirror* stale = slot;
            slot = mirror;
            ReleaseSRWLockExclusive(&g_MapLock);
            if (stale)
            {
                // An address reused without our destructor running: the old
                // record is meaningless now.
                if (stale->data)
                {
                    g_MirrorBytes.fetch_sub(stale->size);
                    HeapFree(GetProcessHeap(), 0, stale->data);
                }
                delete stale;
            }
        }

        void NoteMirrorGrowth()
        {
            const uint64_t bytes = g_MirrorBytes.load();
            uint64_t logged = g_MirrorBytesLogged.load();
            while (bytes >= logged + kMirrorLogStep)
            {
                const uint64_t next = bytes - bytes % kMirrorLogStep;
                if (g_MirrorBytesLogged.compare_exchange_weak(logged, next))
                {
                    LogShimA(LogLevel::Info, kComponent, "[DX11 Buffers] CPU copies now hold %llu MB",
                             static_cast<unsigned long long>(next >> 20));
                    break;
                }
            }
        }

        void Track(const void* buffer)
        {
            if (!g_Active.load(std::memory_order_acquire) || !IsMirrorable(buffer))
                return;
            const size_t size = Field<uint32_t>(buffer, kOffSizeInBytes);
            if (size == 0 || Field<D3D11_BUFFER_DESC>(buffer, kOffDesc).ByteWidth != size)
                return;
            auto* data = static_cast<uint8_t*>(HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, size));
            if (!data)
            {
                if (g_AllocFailures.fetch_add(1) == 0)
                    LogShimA(LogLevel::Warn, kComponent,
                             "[DX11 Buffers] no memory for a %zu-byte CPU copy; that buffer will come back empty after a device loss",
                             size);
            }
            Insert(buffer, new Mirror{data, size, data != nullptr, false, 0, 0, 0});
            if (data)
            {
                g_MirrorBytes.fetch_add(size);
                NoteMirrorGrowth();
            }
        }

        // A buffer created before the hooks, met at its first lock or copy.
        // It is recreated empty after a loss, and its presence means the
        // copies are incomplete, so the stock mesh reload stays on.
        Mirror* TrackLate(const void* buffer)
        {
            if (!g_Active.load(std::memory_order_acquire) || !g_BufferVtable ||
                *reinterpret_cast<const void* const*>(buffer) != g_BufferVtable || !IsMirrorable(buffer))
                return nullptr;
            auto* mirror = new Mirror{nullptr, Field<uint32_t>(buffer, kOffSizeInBytes), false, false, 0, 0, 0};
            Insert(buffer, mirror);
            if (g_LateBuffers.fetch_add(1) == 0)
                LogShimA(LogLevel::Warn, kComponent,
                         "[DX11 Buffers] buffer 0x%p predates the hooks; a device loss will use Ogre's mesh reload", buffer);
            return mirror;
        }

        void Untrack(const void* buffer)
        {
            AcquireSRWLockExclusive(&g_MapLock);
            Mirror* mirror = nullptr;
            const auto it = g_Mirrors->find(buffer);
            if (it != g_Mirrors->end())
            {
                mirror = it->second;
                g_Mirrors->erase(it);
            }
            ReleaseSRWLockExclusive(&g_MapLock);
            if (!mirror)
                return;
            if (mirror->data)
            {
                g_MirrorBytes.fetch_sub(mirror->size);
                HeapFree(GetProcessHeap(), 0, mirror->data);
            }
            delete mirror;
        }

        void Invalidate(Mirror& mirror, const void* buffer, const char* why)
        {
            if (!mirror.valid)
                return;
            mirror.valid = false;
            if (g_Invalidated.fetch_add(1) < 5)
                LogShimA(LogLevel::Warn, kComponent,
                         "[DX11 Buffers] CPU copy of buffer 0x%p dropped (%s); it will come back empty after a device loss",
                         buffer, why);
        }

        void NoteUploadFailure(const void* buffer, HRESULT hr)
        {
            const uint32_t n = g_UploadFailures.fetch_add(1);
            if (n < 5 || n % 1000 == 0)
                LogShimA(LogLevel::Warn, kComponent,
                         "[DX11 Buffers] upload to buffer 0x%p failed hr=0x%08lX (%u so far); the CPU copy keeps the data",
                         buffer, static_cast<unsigned long>(hr), n + 1);
        }

        void Upload(const void* buffer, const Mirror& mirror, uint32_t offset, uint32_t length, uint32_t options)
        {
            const D3D11_BUFFER_DESC& desc = Field<D3D11_BUFFER_DESC>(buffer, kOffDesc);
            const UploadPlan plan = PlanUpload(desc.Usage, options, offset, length, mirror.size);
            if (plan.kind == UploadKind::None)
                return;
            ID3D11Buffer* target = Field<ID3D11Buffer*>(buffer, kOffD3DBuffer);
            ID3D11DeviceContext* context = ContextOf(buffer);
            if (!target || !context)
            {
                NoteUploadFailure(buffer, E_POINTER);
                return;
            }
            const uint8_t* source = mirror.data + plan.offset;
            if (plan.kind == UploadKind::UpdateSubresource)
            {
                const D3D11_BOX box = {static_cast<UINT>(plan.offset), 0, 0,
                                       static_cast<UINT>(plan.offset + plan.count), 1, 1};
                context->UpdateSubresource(target, 0, &box, source, 0, 0);
                return;
            }
            const D3D11_MAP type = plan.kind == UploadKind::MapDiscard       ? D3D11_MAP_WRITE_DISCARD
                                   : plan.kind == UploadKind::MapNoOverwrite ? D3D11_MAP_WRITE_NO_OVERWRITE
                                                                             : D3D11_MAP_WRITE;
            D3D11_MAPPED_SUBRESOURCE mapped = {};
            const HRESULT hr = context->Map(target, 0, type, 0, &mapped);
            if (FAILED(hr) || !mapped.pData)
            {
                NoteUploadFailure(buffer, hr);
                return;
            }
            std::memcpy(static_cast<uint8_t*>(mapped.pData) + plan.offset, source, plan.count);
            context->Unmap(target, 0);
        }

        void* __fastcall HookCtor(void* self, void*, uint32_t type, uint32_t size, uint32_t usage, void* device,
                                  uint32_t systemMemory, uint32_t shadow, uint32_t streamOut)
        {
            void* result = g_RealCtor(self, nullptr, type, size, usage, device, systemMemory, shadow, streamOut);
            Track(self);
            return result;
        }

        void __fastcall HookDtor(void* self, void*)
        {
            Untrack(self);
            g_RealDtor(self, nullptr);
        }

        void* __fastcall HookLockImpl(void* self, void*, uint32_t offset, uint32_t length, uint32_t options)
        {
            Mirror* mirror = Find(self);
            if (!mirror)
                mirror = TrackLate(self);
            if (mirror && mirror->valid && !mirror->locked)
            {
                if (RangeFits(offset, length, mirror->size) && Field<uint32_t>(self, kOffSizeInBytes) == mirror->size)
                {
                    mirror->locked = true;
                    mirror->lockOffset = offset;
                    mirror->lockLength = length;
                    mirror->lockOptions = options;
                    return mirror->data + offset;
                }
                Invalidate(*mirror, self, "a lock outside the copy");
            }
            return g_RealLockImpl(self, nullptr, offset, length, options);
        }

        void __fastcall HookUnlockImpl(void* self, void*)
        {
            Mirror* mirror = Find(self);
            if (!mirror || !mirror->locked)
            {
                g_RealUnlockImpl(self, nullptr);
                return;
            }
            mirror->locked = false;
            Upload(self, *mirror, mirror->lockOffset, mirror->lockLength, mirror->lockOptions);
        }

        void __fastcall HookCopyDataImpl(void* self, void*, void* source, uint32_t sourceOffset, uint32_t offset,
                                         uint32_t length, uint32_t discard)
        {
            Mirror* target = Find(self);
            if (!target)
                target = TrackLate(self);
            if (target && target->valid)
            {
                Mirror* from = source ? Find(source) : nullptr;
                if (from && from->valid && RangeFits(sourceOffset, length, from->size) &&
                    RangeFits(offset, length, target->size))
                    std::memmove(target->data + offset, from->data + sourceOffset, length);
                else
                    Invalidate(*target, self, "a GPU copy from a buffer without a CPU copy");
            }
            g_RealCopyDataImpl(self, nullptr, source, sourceOffset, offset, length, discard);
        }

        struct RestoreSummary
        {
            unsigned restored = 0;
            unsigned withoutData = 0;
            unsigned current = 0;
            unsigned failed = 0;
            uint64_t bytes = 0;
            HRESULT firstFailure = S_OK;
        };

        // Every mirrored buffer still on another device gets a new
        // ID3D11Buffer on its wrapper's current device, made from its copy.
        RestoreSummary RestoreBuffers()
        {
            RestoreSummary summary;
            AcquireSRWLockShared(&g_MapLock);
            for (const auto& entry : *g_Mirrors)
            {
                const void* buffer = entry.first;
                const Mirror& mirror = *entry.second;
                ID3D11Device* device = DeviceOf(buffer);
                if (!device)
                {
                    ++summary.failed;
                    continue;
                }
                ID3D11Buffer*& slot = Field<ID3D11Buffer*>(buffer, kOffD3DBuffer);
                if (slot)
                {
                    ID3D11Device* owner = nullptr;
                    slot->GetDevice(&owner);
                    const bool onCurrent = owner == device;
                    if (owner)
                        owner->Release();
                    if (onCurrent)
                    {
                        ++summary.current;
                        continue;
                    }
                }
                const D3D11_BUFFER_DESC desc = Field<D3D11_BUFFER_DESC>(buffer, kOffDesc);
                const bool withData = mirror.valid && mirror.data && desc.ByteWidth == mirror.size;
                D3D11_SUBRESOURCE_DATA initial = {withData ? mirror.data : nullptr, 0, 0};
                ID3D11Buffer* fresh = nullptr;
                const HRESULT hr = device->CreateBuffer(&desc, withData ? &initial : nullptr, &fresh);
                if (FAILED(hr) || !fresh)
                {
                    if (summary.failed++ == 0)
                        summary.firstFailure = hr;
                    continue;
                }
                if (slot)
                    slot->Release();
                slot = fresh;
                ++summary.restored;
                if (withData)
                    summary.bytes += mirror.size;
                else
                    ++summary.withoutData;
            }
            ReleaseSRWLockShared(&g_MapLock);
            return summary;
        }

        void __fastcall HookMeshReloadAll(void* manager, void*, uint32_t flags)
        {
            if (g_Active.load(std::memory_order_acquire) && g_InDeviceLost.load(std::memory_order_acquire) &&
                !g_RestoredThisLoss.exchange(true))
            {
                const RestoreSummary s = RestoreBuffers();
                const uint32_t late = g_LateBuffers.load();
                LogShimA(LogLevel::Info, kComponent,
                         "[DX11 Buffers] device restore: %u buffers recreated in place (%llu MB from CPU copies, %u empty), %u already current, %u failed",
                         s.restored, static_cast<unsigned long long>(s.bytes >> 20), s.withoutData, s.current, s.failed);
                if (s.failed)
                    LogShimA(LogLevel::Warn, kComponent,
                             "[DX11 Buffers] first CreateBuffer failure hr=0x%08lX; the next device loss retries them",
                             static_cast<unsigned long>(s.firstFailure));
                if (late == 0)
                {
                    LogShimA(LogLevel::Info, kComponent,
                             "[DX11 Buffers] skipped Ogre's mesh reload: entities keep their skeletons, bones and materials");
                    return;
                }
                LogShimA(LogLevel::Warn, kComponent,
                         "[DX11 Buffers] %u buffers predate the hooks; running Ogre's mesh reload as stock", late);
            }
            reinterpret_cast<FnReloadAll>(g_RealReloadAll)(manager, nullptr, flags);
        }

        // MeshManager exists once Ogre's Root does; the hook goes on the first
        // time it can, and handleDeviceLost asks again before the reload.
        void EnsureMeshManagerHook()
        {
            if (g_MeshHookInstalled.load(std::memory_order_acquire) || !g_MeshManagerPtr)
                return;
            void* manager = g_MeshManagerPtr();
            if (!manager)
                return;
            void** vtable = *reinterpret_cast<void***>(manager);
            if (!vtable)
                return;
            if (vtable[kMeshManagerReloadAllSlot] != g_ExpectedReloadAll &&
                vtable[kMeshManagerReloadAllSlot] != reinterpret_cast<void*>(&HookMeshReloadAll))
            {
                if (!g_MeshHookTried.exchange(true))
                    LogShimA(LogLevel::Warn, kComponent,
                             "[DX11 Buffers] MeshManager vtable slot %zu is not ResourceManager::reloadAll; mesh reload left as stock",
                             kMeshManagerReloadAllSlot);
                return;
            }
            const auto result =
                ComVtablePatch::PatchEntry(manager, kMeshManagerReloadAllSlot, reinterpret_cast<void*>(&HookMeshReloadAll),
                                           g_RealReloadAll, ComVtablePatch::OnForeignWrapper::Refuse);
            if (ComVtablePatch::Succeeded(result))
            {
                g_MeshHookInstalled.store(true, std::memory_order_release);
                LogShimA(LogLevel::Info, kComponent, "[DX11 Buffers] mesh reload after a device loss now restores buffers in place");
            }
            else if (!g_MeshHookTried.exchange(true))
            {
                LogShimA(LogLevel::Warn, kComponent, "[DX11 Buffers] could not hook MeshManager::reloadAll (result %d)",
                         static_cast<int>(result));
            }
        }

        void __fastcall HookHandleDeviceLost(void* renderSystem, void*)
        {
            EnsureMeshManagerHook();
            struct Scope
            {
                Scope()
                {
                    g_RestoredThisLoss.store(false);
                    g_InDeviceLost.store(true, std::memory_order_release);
                }
                ~Scope() { g_InDeviceLost.store(false, std::memory_order_release); }
            } scope;
            g_RealHandleDeviceLost(renderSystem, nullptr);
        }

        struct ThunkSite
        {
            const char* exportName;
            void* hook;
            void** original;
            uint32_t thunk;
            uint8_t bytes[5];
        };

        bool ReadThunk(HMODULE module, ThunkSite& site)
        {
            const auto address = reinterpret_cast<uint32_t>(GetProcAddress(module, site.exportName));
            if (!address || !HookEngine::ReadMemory(address, site.bytes, sizeof(site.bytes)) || site.bytes[0] != 0xE9)
                return false;
            int32_t rel = 0;
            std::memcpy(&rel, site.bytes + 1, sizeof(rel));
            site.thunk = address;
            *site.original = reinterpret_cast<void*>(address + 5 + rel);
            return true;
        }

        // Replaces the five bytes at `address` (expected to be `from`) with
        // `to` in one locked compare-exchange of the eight bytes there; the
        // three after the jump are written back unchanged. The eight bytes
        // must not cross a cache line, or the exchange would be a split lock.
        bool SwapThunk(uint32_t address, const uint8_t* from, const uint8_t* to)
        {
            if ((address & 63u) > 56u)
                return false;
            auto* target = reinterpret_cast<volatile LONG64*>(address);
            DWORD oldProtect = 0;
            if (!VirtualProtect(reinterpret_cast<void*>(address), 8, PAGE_EXECUTE_READWRITE, &oldProtect))
                return false;
            LONG64 current = 0;
            std::memcpy(&current, reinterpret_cast<const void*>(address), sizeof(current));
            bool swapped = false;
            if (std::memcmp(&current, from, 5) == 0)
            {
                LONG64 replacement = current;
                std::memcpy(&replacement, to, 5);
                swapped = InterlockedCompareExchange64(target, replacement, current) == current;
            }
            DWORD ignored = 0;
            VirtualProtect(reinterpret_cast<void*>(address), 8, oldProtect, &ignored);
            FlushInstructionCache(GetCurrentProcess(), reinterpret_cast<void*>(address), 8);
            return swapped;
        }

        bool IsKnownRenderer(HMODULE renderer)
        {
            const auto* dos = reinterpret_cast<const IMAGE_DOS_HEADER*>(renderer);
            if (dos->e_magic != IMAGE_DOS_SIGNATURE)
                return false;
            const auto* nt = reinterpret_cast<const IMAGE_NT_HEADERS32*>(reinterpret_cast<const uint8_t*>(renderer) + dos->e_lfanew);
            return nt->Signature == IMAGE_NT_SIGNATURE && nt->FileHeader.TimeDateStamp == kRendererTimeDateStamp &&
                   nt->OptionalHeader.SizeOfImage == kRendererSizeOfImage;
        }
    }

    bool InstallD3D11BufferRestore(HMODULE renderer)
    {
        char value[16] = {};
        const DWORD n = GetEnvironmentVariableA("OPENSHIM_DISABLE_D3D11_BUFFER_RESTORE", value,
                                                static_cast<DWORD>(sizeof(value)));
        if (n > 0 && n < sizeof(value) && BoolToken::IsTruthy(value, n))
        {
            LogShimA(LogLevel::Info, kComponent, "[DX11 Buffers] disabled by OPENSHIM_DISABLE_D3D11_BUFFER_RESTORE");
            return false;
        }
        if (!renderer || !IsKnownRenderer(renderer))
        {
            LogShimA(LogLevel::Warn, kComponent,
                     "[DX11 Buffers] RenderSystem_Direct3D11.dll is not the build this was written for; buffers left as stock");
            return false;
        }
        HMODULE ogre = GetModuleHandleW(L"OgreMain.dll");
        g_BufferVtable = reinterpret_cast<const void*>(GetProcAddress(renderer, "??_7D3D11HardwareBuffer@Ogre@@6B@"));
        g_MeshManagerPtr = ogre ? reinterpret_cast<FnGetSingletonPtr>(GetProcAddress(ogre, "?getSingletonPtr@MeshManager@Ogre@@SAPAV12@XZ"))
                                : nullptr;
        g_ExpectedReloadAll = ogre ? reinterpret_cast<void*>(GetProcAddress(
                                         ogre, "?reloadAll@ResourceManager@Ogre@@UAEXW4LoadingFlags@Resource@2@@Z"))
                                   : nullptr;

        // The destructor goes first, so no buffer the constructor hook records
        // can be freed unseen.
        ThunkSite sites[] = {
            {"??1D3D11HardwareBuffer@Ogre@@UAE@XZ", reinterpret_cast<void*>(&HookDtor),
             reinterpret_cast<void**>(&g_RealDtor), 0, {}},
            {"??0D3D11HardwareBuffer@Ogre@@QAE@W4BufferType@01@IW4Usage@HardwareBuffer@1@AAVD3D11Device@1@_N33@Z",
             reinterpret_cast<void*>(&HookCtor), reinterpret_cast<void**>(&g_RealCtor), 0, {}},
            {"?lockImpl@D3D11HardwareBuffer@Ogre@@MAEPAXIIW4LockOptions@HardwareBuffer@2@@Z",
             reinterpret_cast<void*>(&HookLockImpl), reinterpret_cast<void**>(&g_RealLockImpl), 0, {}},
            {"?unlockImpl@D3D11HardwareBuffer@Ogre@@MAEXXZ", reinterpret_cast<void*>(&HookUnlockImpl),
             reinterpret_cast<void**>(&g_RealUnlockImpl), 0, {}},
            {"?copyDataImpl@D3D11HardwareBuffer@Ogre@@QAEXAAVHardwareBuffer@2@III_N@Z",
             reinterpret_cast<void*>(&HookCopyDataImpl), reinterpret_cast<void**>(&g_RealCopyDataImpl), 0, {}},
            {"?handleDeviceLost@D3D11RenderSystem@Ogre@@QAEXXZ", reinterpret_cast<void*>(&HookHandleDeviceLost),
             reinterpret_cast<void**>(&g_RealHandleDeviceLost), 0, {}},
        };
        if (!g_BufferVtable || !g_MeshManagerPtr || !g_ExpectedReloadAll)
        {
            LogShimA(LogLevel::Warn, kComponent, "[DX11 Buffers] renderer or OgreMain exports missing; buffers left as stock");
            return false;
        }
        for (ThunkSite& site : sites)
        {
            if (!ReadThunk(renderer, site))
            {
                LogShimA(LogLevel::Warn, kComponent, "[DX11 Buffers] %s is not a jump thunk; buffers left as stock",
                         site.exportName);
                return false;
            }
        }

        // No thread runs these thunks yet (no device, so no buffer), and each
        // jump is swapped in one locked 8-byte exchange, so the other threads
        // are not suspended: HookEngine's suspend deadlocked in NtSuspendThread
        // while the game thread was still loading plugins.
        HookEngine::CodePatchLock lock;
        g_Active.store(true, std::memory_order_release);
        size_t written = 0;
        for (; written < sizeof(sites) / sizeof(sites[0]); ++written)
        {
            const ThunkSite& site = sites[written];
            const auto jump = HookEngine::MakeJmp5Payload(site.thunk, reinterpret_cast<uint32_t>(site.hook));
            if (!SwapThunk(site.thunk, site.bytes, jump.data()))
                break;
        }
        if (written != sizeof(sites) / sizeof(sites[0]))
        {
            g_Active.store(false, std::memory_order_release);
            for (size_t i = 0; i < written; ++i)
            {
                const auto jump = HookEngine::MakeJmp5Payload(sites[i].thunk, reinterpret_cast<uint32_t>(sites[i].hook));
                SwapThunk(sites[i].thunk, jump.data(), sites[i].bytes);
            }
            LogShimA(LogLevel::Warn, kComponent, "[DX11 Buffers] could not patch %s; buffers left as stock",
                     sites[written].exportName);
            return false;
        }

        EnsureMeshManagerHook();
        LogShimA(LogLevel::Info, kComponent,
                 "[DX11 Buffers] installed: vertex and index buffers keep CPU copies for in-place restore after a device loss");
        return true;
    }
}
