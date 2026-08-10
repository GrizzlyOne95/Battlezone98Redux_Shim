#include "ogre_animation_profiler.h"
#include "ogre_runtime.h"
#include "shim_log.h"

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <Windows.h>
#include <d3d11.h>
#include <dxgi.h>
#include <process.h>

// The retail BZR Ogre is not ABI-identical to pristine upstream 1.10.0.
// We use the pinned headers only for the small POD-facing VertexData surface
// needed by this diagnostic, and sanity-check vertexCount before recording it.
#ifndef register
#define OPENSHIM_OGRE_RESTORE_REGISTER
#define register
#endif
#ifndef _STLP_MSVC
#define _STLP_MSVC 1
#endif
#include <OgreVertexIndexData.h>
#ifdef OPENSHIM_OGRE_RESTORE_REGISTER
#undef register
#undef OPENSHIM_OGRE_RESTORE_REGISTER
#endif

#include <array>
#include <atomic>
#include <bit>
#include <cctype>
#include <cstdint>
#include <cstring>
#include <limits>
#include <mutex>
#include <string>
#include <utility>
#include <vector>

namespace BZROpenShim
{
    namespace
    {
        constexpr char kComponent[] = "ogre-profile";
        constexpr char kEnvironmentSwitch[] = "OPENSHIM_PROFILE_OGRE_ANIMATION";
        constexpr char kIniSection[] = "Diagnostics";
        constexpr char kIniKey[] = "ProfileOgreAnimation";
        constexpr DWORD kPollSleepMs = 25;
        constexpr ULONGLONG kReportIntervalMs = 1000;
        constexpr size_t kBloomWords = 1024; // 65536 bits; low collision rate for BZR-scale scenes.
        constexpr size_t kMaxVtableEntriesToProbe = 128;
        constexpr size_t kMaxSaneVertexCount = 16u * 1024u * 1024u;

        using FnEntityUpdateAnimation = void(__thiscall*)(void*);
        using FnEntityUpdateRenderQueue = void(__thiscall*)(void*, void*);
        using FnSoftwareVertexBlend = void(__cdecl*)(
            const Ogre::VertexData*,
            const Ogre::VertexData*,
            const void* const*,
            size_t,
            bool);

        using FnD3D11CreateDevice = HRESULT(WINAPI*)(
            IDXGIAdapter*, D3D_DRIVER_TYPE, HMODULE, UINT,
            const D3D_FEATURE_LEVEL*, UINT, UINT,
            ID3D11Device**, D3D_FEATURE_LEVEL*, ID3D11DeviceContext**);
        using FnD3D11CreateDeviceAndSwapChain = HRESULT(WINAPI*)(
            IDXGIAdapter*, D3D_DRIVER_TYPE, HMODULE, UINT,
            const D3D_FEATURE_LEVEL*, UINT, UINT,
            const DXGI_SWAP_CHAIN_DESC*, IDXGISwapChain**,
            ID3D11Device**, D3D_FEATURE_LEVEL*, ID3D11DeviceContext**);
        using FnFactoryCreateSwapChain = HRESULT(STDMETHODCALLTYPE*)(
            IDXGIFactory*, IUnknown*, DXGI_SWAP_CHAIN_DESC*, IDXGISwapChain**);
        using FnContextDrawIndexed = void(STDMETHODCALLTYPE*)(
            ID3D11DeviceContext*, UINT, UINT, INT);
        using FnContextDraw = void(STDMETHODCALLTYPE*)(
            ID3D11DeviceContext*, UINT, UINT);
        using FnSwapChainPresent = HRESULT(STDMETHODCALLTYPE*)(
            IDXGISwapChain*, UINT, UINT);

        struct Rel32Patch
        {
            uint8_t* operand = nullptr;
            int32_t original = 0;
        };

        struct PointerPatch
        {
            void** slot = nullptr;
            void* original = nullptr;
        };

        struct ExportMatch
        {
            std::string name;
            void* address = nullptr;
        };

        std::atomic<bool> g_Enabled{ false };
        std::atomic<bool> g_ShutdownRequested{ false };
        std::atomic<bool> g_OgreHooksInstalled{ false };
        std::atomic<bool> g_RenderQueueHookInstalled{ false };
        std::atomic<bool> g_Dx11ImportsPatched{ false };
        std::atomic<bool> g_Dx11ContextObserved{ false };
        std::atomic<bool> g_PresentObserved{ false };
        uintptr_t g_WorkerThread = 0;

        std::mutex g_PatchMutex;
        std::vector<Rel32Patch> g_Rel32Patches;
        std::vector<PointerPatch> g_PointerPatches;

        FnEntityUpdateAnimation g_RealEntityUpdateAnimation = nullptr;
        FnEntityUpdateRenderQueue g_RealEntityUpdateRenderQueue = nullptr;
        FnSoftwareVertexBlend g_RealSoftwareVertexBlend = nullptr;

        FnD3D11CreateDevice g_RealD3D11CreateDevice = nullptr;
        FnD3D11CreateDeviceAndSwapChain g_RealD3D11CreateDeviceAndSwapChain = nullptr;
        FnFactoryCreateSwapChain g_RealFactoryCreateSwapChain = nullptr;
        FnContextDrawIndexed g_RealDrawIndexed = nullptr;
        FnContextDraw g_RealDraw = nullptr;
        FnSwapChainPresent g_RealPresent = nullptr;

        std::atomic<uint64_t> g_AnimationCalls{ 0 };
        std::atomic<uint64_t> g_AnimationTicks{ 0 };
        std::atomic<uint64_t> g_SoftwareBlendCalls{ 0 };
        std::atomic<uint64_t> g_SoftwareBlendVertices{ 0 };
        std::atomic<uint64_t> g_SoftwareBlendTicks{ 0 };
        std::atomic<uint64_t> g_RenderQueueCalls{ 0 };
        std::atomic<uint64_t> g_DrawCalls{ 0 };
        std::atomic<uint64_t> g_DrawVertices{ 0 };
        std::atomic<uint64_t> g_DrawIndexedCalls{ 0 };
        std::atomic<uint64_t> g_DrawIndexedIndices{ 0 };
        std::atomic<uint64_t> g_Presents{ 0 };

        std::array<std::atomic<uint64_t>, kBloomWords> g_AnimationEntityBloom{};
        std::array<std::atomic<uint64_t>, kBloomWords> g_SkinnedEntityBloom{};
        std::array<std::atomic<uint64_t>, kBloomWords> g_RenderEntityBloom{};

        LARGE_INTEGER g_QpcFrequency{};
        thread_local void* t_CurrentAnimationEntity = nullptr;

        bool StringIsTruthy(const char* value)
        {
            if (!value || !*value)
                return false;

            std::string v(value);
            for (char& ch : v)
                ch = static_cast<char>(std::tolower(static_cast<unsigned char>(ch)));
            return v != "0" && v != "false" && v != "no" && v != "off";
        }

        std::string GetOpenShimIniPath()
        {
            char path[MAX_PATH] = {};
            const DWORD length = GetModuleFileNameA(nullptr, path, MAX_PATH);
            if (length == 0 || length >= MAX_PATH)
                return "openshim.ini";

            char* slash = std::strrchr(path, '\\');
            if (slash)
                *(slash + 1) = '\0';
            else
                path[0] = '\0';
            return std::string(path) + "openshim.ini";
        }

        bool ProfilerRequested()
        {
            char envValue[64] = {};
            const DWORD envLength = GetEnvironmentVariableA(
                kEnvironmentSwitch,
                envValue,
                static_cast<DWORD>(sizeof(envValue)));
            if (envLength > 0 && envLength < sizeof(envValue))
                return StringIsTruthy(envValue);

            const std::string iniPath = GetOpenShimIniPath();
            return GetPrivateProfileIntA(kIniSection, kIniKey, 0, iniPath.c_str()) != 0;
        }

        uint32_t HashPointer(const void* pointer)
        {
            uintptr_t value = reinterpret_cast<uintptr_t>(pointer);
            value >>= 4;
            uint32_t x = static_cast<uint32_t>(value);
            x ^= x >> 16;
            x *= 0x7feb352du;
            x ^= x >> 15;
            x *= 0x846ca68bu;
            x ^= x >> 16;
            return x;
        }

        void BloomAdd(std::array<std::atomic<uint64_t>, kBloomWords>& bloom, const void* pointer)
        {
            if (!pointer)
                return;
            constexpr uint32_t kBitCount = static_cast<uint32_t>(kBloomWords * 64u);
            const uint32_t bitIndex = HashPointer(pointer) & (kBitCount - 1u);
            const size_t wordIndex = bitIndex >> 6;
            const uint64_t bit = 1ull << (bitIndex & 63u);
            bloom[wordIndex].fetch_or(bit, std::memory_order_relaxed);
        }

        uint64_t ReadQpc()
        {
            LARGE_INTEGER value{};
            QueryPerformanceCounter(&value);
            return static_cast<uint64_t>(value.QuadPart);
        }

        double TicksToMs(uint64_t ticks)
        {
            if (g_QpcFrequency.QuadPart <= 0)
                return 0.0;
            return static_cast<double>(ticks) * 1000.0 /
                static_cast<double>(g_QpcFrequency.QuadPart);
        }

        size_t ReadVertexCount(const Ogre::VertexData* data)
        {
            if (!data)
                return 0;

            size_t value = 0;
            __try
            {
                value = data->vertexCount;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return 0;
            }

            return value <= kMaxSaneVertexCount ? value : 0;
        }

        bool WriteRel32(uint8_t* operand, int32_t value)
        {
            if (!operand)
                return false;
            DWORD oldProtect = 0;
            if (!VirtualProtect(operand, sizeof(value), PAGE_EXECUTE_READWRITE, &oldProtect))
                return false;
            std::memcpy(operand, &value, sizeof(value));
            DWORD ignored = 0;
            VirtualProtect(operand, sizeof(value), oldProtect, &ignored);
            FlushInstructionCache(GetCurrentProcess(), operand - 1, 5);
            return true;
        }

        bool WritePointer(void** slot, void* value)
        {
            if (!slot)
                return false;
            DWORD oldProtect = 0;
            if (!VirtualProtect(slot, sizeof(void*), PAGE_EXECUTE_READWRITE, &oldProtect))
                return false;
            *slot = value;
            DWORD ignored = 0;
            VirtualProtect(slot, sizeof(void*), oldProtect, &ignored);
            FlushInstructionCache(GetCurrentProcess(), slot, sizeof(void*));
            return true;
        }

        std::vector<ExportMatch> FindExportsContaining(const char* token)
        {
            std::vector<ExportMatch> matches;
            if (!token || !*token)
                return matches;

            HMODULE module = GetModuleHandleA("OgreMain.dll");
            if (!module)
                return matches;

            auto* base = reinterpret_cast<uint8_t*>(module);
            auto* dos = reinterpret_cast<IMAGE_DOS_HEADER*>(base);
            if (dos->e_magic != IMAGE_DOS_SIGNATURE)
                return matches;
            auto* nt = reinterpret_cast<IMAGE_NT_HEADERS*>(base + dos->e_lfanew);
            if (nt->Signature != IMAGE_NT_SIGNATURE)
                return matches;

            const IMAGE_DATA_DIRECTORY& directory =
                nt->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT];
            if (!directory.VirtualAddress || !directory.Size)
                return matches;

            auto* exports = reinterpret_cast<IMAGE_EXPORT_DIRECTORY*>(base + directory.VirtualAddress);
            auto* names = reinterpret_cast<DWORD*>(base + exports->AddressOfNames);
            auto* ordinals = reinterpret_cast<WORD*>(base + exports->AddressOfNameOrdinals);
            auto* functions = reinterpret_cast<DWORD*>(base + exports->AddressOfFunctions);

            for (DWORD i = 0; i < exports->NumberOfNames; ++i)
            {
                const char* name = reinterpret_cast<const char*>(base + names[i]);
                if (!name || std::strstr(name, token) == nullptr)
                    continue;

                const WORD ordinal = ordinals[i];
                if (ordinal >= exports->NumberOfFunctions)
                    continue;
                const DWORD functionRva = functions[ordinal];

                // Ignore forwarded exports.
                if (functionRva >= directory.VirtualAddress &&
                    functionRva < directory.VirtualAddress + directory.Size)
                {
                    continue;
                }

                void* address = base + functionRva;
                if (OgreRuntime::ContainsAddress(address))
                    matches.push_back({ name, address });
            }
            return matches;
        }

        void* FindUniqueFunctionExport(const char* token, const char* label)
        {
            const auto matches = FindExportsContaining(token);
            if (matches.size() != 1)
            {
                LogShimA(
                    LogLevel::Warn,
                    kComponent,
                    "[OgreProfile] %s export match count=%u token=%s; observer disabled",
                    label,
                    static_cast<unsigned>(matches.size()),
                    token);
                return nullptr;
            }

            LogShimA(
                LogLevel::Info,
                kComponent,
                "[OgreProfile] resolved %s export=%s address=0x%p",
                label,
                matches[0].name.c_str(),
                matches[0].address);
            return matches[0].address;
        }

        size_t PatchDirectCallsInModule(
            HMODULE module,
            void* target,
            void* replacement,
            const char* label)
        {
            if (!module || !target || !replacement)
                return 0;

            auto* base = reinterpret_cast<uint8_t*>(module);
            auto* dos = reinterpret_cast<IMAGE_DOS_HEADER*>(base);
            if (dos->e_magic != IMAGE_DOS_SIGNATURE)
                return 0;
            auto* nt = reinterpret_cast<IMAGE_NT_HEADERS*>(base + dos->e_lfanew);
            if (nt->Signature != IMAGE_NT_SIGNATURE)
                return 0;

            const size_t imageSize = nt->OptionalHeader.SizeOfImage;
            auto* section = IMAGE_FIRST_SECTION(nt);
            size_t patched = 0;

            std::lock_guard<std::mutex> lock(g_PatchMutex);
            for (WORD sectionIndex = 0; sectionIndex < nt->FileHeader.NumberOfSections; ++sectionIndex, ++section)
            {
                if ((section->Characteristics & IMAGE_SCN_MEM_EXECUTE) == 0)
                    continue;

                size_t sectionSize = static_cast<size_t>(section->Misc.VirtualSize);
                if (sectionSize == 0)
                    sectionSize = static_cast<size_t>(section->SizeOfRawData);
                if (section->VirtualAddress >= imageSize)
                    continue;
                sectionSize = (std::min)(
                    sectionSize,
                    imageSize - static_cast<size_t>(section->VirtualAddress));
                if (sectionSize < 5)
                    continue;

                uint8_t* code = base + section->VirtualAddress;
                for (size_t i = 0; i + 5 <= sectionSize; ++i)
                {
                    if (code[i] != 0xE8)
                        continue;

                    int32_t relative = 0;
                    std::memcpy(&relative, code + i + 1, sizeof(relative));
                    uint8_t* destination = code + i + 5 + relative;
                    if (destination != target)
                        continue;

                    const intptr_t delta =
                        reinterpret_cast<uint8_t*>(replacement) - (code + i + 5);
                    const int32_t newRelative = static_cast<int32_t>(delta);
                    if (!WriteRel32(code + i + 1, newRelative))
                        continue;

                    g_Rel32Patches.push_back({ code + i + 1, relative });
                    ++patched;
                    i += 4;
                }
            }

            LogShimA(
                patched ? LogLevel::Info : LogLevel::Warn,
                kComponent,
                "[OgreProfile] %s direct-call observers installed=%u module=0x%p",
                label,
                static_cast<unsigned>(patched),
                module);
            return patched;
        }

        size_t PatchIatEntriesByTarget(
            HMODULE module,
            void* target,
            void* replacement,
            const char* label)
        {
            if (!module || !target || !replacement)
                return 0;

            auto* base = reinterpret_cast<uint8_t*>(module);
            auto* dos = reinterpret_cast<IMAGE_DOS_HEADER*>(base);
            if (dos->e_magic != IMAGE_DOS_SIGNATURE)
                return 0;
            auto* nt = reinterpret_cast<IMAGE_NT_HEADERS*>(base + dos->e_lfanew);
            if (nt->Signature != IMAGE_NT_SIGNATURE)
                return 0;

            const IMAGE_DATA_DIRECTORY& imports =
                nt->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT];
            if (!imports.VirtualAddress)
                return 0;

            size_t patched = 0;
            auto* descriptor = reinterpret_cast<IMAGE_IMPORT_DESCRIPTOR*>(base + imports.VirtualAddress);
            std::lock_guard<std::mutex> lock(g_PatchMutex);
            for (; descriptor->Name; ++descriptor)
            {
                auto* thunk = reinterpret_cast<IMAGE_THUNK_DATA*>(base + descriptor->FirstThunk);
                for (; thunk->u1.Function; ++thunk)
                {
                    void** slot = reinterpret_cast<void**>(&thunk->u1.Function);
                    if (*slot != target)
                        continue;
                    if (!WritePointer(slot, replacement))
                        continue;
                    g_PointerPatches.push_back({ slot, target });
                    ++patched;
                }
            }

            if (patched)
            {
                LogShimA(
                    LogLevel::Info,
                    kComponent,
                    "[OgreProfile] %s IAT observers installed=%u module=0x%p",
                    label,
                    static_cast<unsigned>(patched),
                    module);
            }
            return patched;
        }

        size_t PatchEntityVtables(void* target, void* replacement)
        {
            const auto vtables = FindExportsContaining("??_7Entity@Ogre@@");
            size_t patched = 0;
            std::lock_guard<std::mutex> lock(g_PatchMutex);

            for (const auto& match : vtables)
            {
                auto** vtable = reinterpret_cast<void**>(match.address);
                for (size_t i = 0; i < kMaxVtableEntriesToProbe; ++i)
                {
                    void** slot = &vtable[i];
                    if (!OgreRuntime::ContainsAddress(slot))
                        break;

                    void* entry = *slot;
                    if (entry != target)
                        continue;
                    if (!WritePointer(slot, replacement))
                        continue;

                    g_PointerPatches.push_back({ slot, target });
                    ++patched;
                    LogShimA(
                        LogLevel::Info,
                        kComponent,
                        "[OgreProfile] Entity vtable render-queue observer export=%s slot=%u",
                        match.name.c_str(),
                        static_cast<unsigned>(i));
                }
            }
            return patched;
        }

        bool PatchIatFunctionByName(
            HMODULE module,
            const char* importedDll,
            const char* functionName,
            void* replacement,
            void** original)
        {
            if (!module || !importedDll || !functionName || !replacement || !original)
                return false;

            auto* base = reinterpret_cast<uint8_t*>(module);
            auto* dos = reinterpret_cast<IMAGE_DOS_HEADER*>(base);
            if (dos->e_magic != IMAGE_DOS_SIGNATURE)
                return false;
            auto* nt = reinterpret_cast<IMAGE_NT_HEADERS*>(base + dos->e_lfanew);
            if (nt->Signature != IMAGE_NT_SIGNATURE)
                return false;

            const IMAGE_DATA_DIRECTORY& imports =
                nt->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT];
            if (!imports.VirtualAddress)
                return false;

            auto* descriptor = reinterpret_cast<IMAGE_IMPORT_DESCRIPTOR*>(base + imports.VirtualAddress);
            for (; descriptor->Name; ++descriptor)
            {
                const char* dllName = reinterpret_cast<const char*>(base + descriptor->Name);
                if (_stricmp(dllName, importedDll) != 0)
                    continue;
                if (!descriptor->OriginalFirstThunk)
                    return false;

                auto* names = reinterpret_cast<IMAGE_THUNK_DATA*>(base + descriptor->OriginalFirstThunk);
                auto* thunks = reinterpret_cast<IMAGE_THUNK_DATA*>(base + descriptor->FirstThunk);
                for (; names->u1.AddressOfData && thunks->u1.Function; ++names, ++thunks)
                {
                    if (IMAGE_SNAP_BY_ORDINAL(names->u1.Ordinal))
                        continue;
                    auto* byName = reinterpret_cast<IMAGE_IMPORT_BY_NAME*>(base + names->u1.AddressOfData);
                    if (std::strcmp(reinterpret_cast<const char*>(byName->Name), functionName) != 0)
                        continue;

                    void** slot = reinterpret_cast<void**>(&thunks->u1.Function);
                    std::lock_guard<std::mutex> lock(g_PatchMutex);
                    if (*slot == replacement)
                        return true;
                    if (*original == nullptr)
                        *original = *slot;
                    if (!WritePointer(slot, replacement))
                        return false;
                    g_PointerPatches.push_back({ slot, *original });
                    return true;
                }
            }
            return false;
        }

        template <typename T>
        bool PatchComVtableEntry(
            void* object,
            size_t index,
            T hook,
            T& original,
            const char* label)
        {
            if (!object)
                return false;

            std::lock_guard<std::mutex> lock(g_PatchMutex);
            void*** objectVtable = reinterpret_cast<void***>(object);
            if (!objectVtable || !*objectVtable)
                return false;
            void** vtable = *objectVtable;
            void* current = vtable[index];
            if (current == reinterpret_cast<void*>(hook))
                return true;

            if (original && current != reinterpret_cast<void*>(original))
            {
                LogShimA(
                    LogLevel::Warn,
                    kComponent,
                    "[OgreProfile] %s already wrapped by another observer; leaving it untouched",
                    label);
                return false;
            }

            if (!original)
                original = reinterpret_cast<T>(current);
            if (!WritePointer(&vtable[index], reinterpret_cast<void*>(hook)))
                return false;
            g_PointerPatches.push_back({ &vtable[index], reinterpret_cast<void*>(original) });

            LogShimA(
                LogLevel::Info,
                kComponent,
                "[OgreProfile] installed %s observer vtable[%u]",
                label,
                static_cast<unsigned>(index));
            return true;
        }

        struct CurrentEntityScope
        {
            void* previous;
            explicit CurrentEntityScope(void* current)
                : previous(t_CurrentAnimationEntity)
            {
                t_CurrentAnimationEntity = current;
            }
            ~CurrentEntityScope()
            {
                t_CurrentAnimationEntity = previous;
            }
        };

        void __fastcall HookEntityUpdateAnimation(void* self, void*)
        {
            if (!g_RealEntityUpdateAnimation)
                return;
            if (!g_Enabled.load(std::memory_order_relaxed))
            {
                g_RealEntityUpdateAnimation(self);
                return;
            }

            g_AnimationCalls.fetch_add(1, std::memory_order_relaxed);
            BloomAdd(g_AnimationEntityBloom, self);
            const uint64_t start = ReadQpc();
            CurrentEntityScope scope(self);
            g_RealEntityUpdateAnimation(self);
            g_AnimationTicks.fetch_add(ReadQpc() - start, std::memory_order_relaxed);
        }

        void __cdecl HookSoftwareVertexBlend(
            const Ogre::VertexData* sourceVertexData,
            const Ogre::VertexData* targetVertexData,
            const void* const* blendMatrices,
            size_t numMatrices,
            bool blendNormals)
        {
            if (!g_RealSoftwareVertexBlend)
                return;
            if (!g_Enabled.load(std::memory_order_relaxed))
            {
                g_RealSoftwareVertexBlend(
                    sourceVertexData,
                    targetVertexData,
                    blendMatrices,
                    numMatrices,
                    blendNormals);
                return;
            }

            g_SoftwareBlendCalls.fetch_add(1, std::memory_order_relaxed);
            g_SoftwareBlendVertices.fetch_add(
                static_cast<uint64_t>(ReadVertexCount(sourceVertexData)),
                std::memory_order_relaxed);
            BloomAdd(g_SkinnedEntityBloom, t_CurrentAnimationEntity);

            const uint64_t start = ReadQpc();
            g_RealSoftwareVertexBlend(
                sourceVertexData,
                targetVertexData,
                blendMatrices,
                numMatrices,
                blendNormals);
            g_SoftwareBlendTicks.fetch_add(ReadQpc() - start, std::memory_order_relaxed);
        }

        void __fastcall HookEntityUpdateRenderQueue(void* self, void*, void* renderQueue)
        {
            if (!g_RealEntityUpdateRenderQueue)
                return;
            if (g_Enabled.load(std::memory_order_relaxed))
            {
                g_RenderQueueCalls.fetch_add(1, std::memory_order_relaxed);
                BloomAdd(g_RenderEntityBloom, self);
            }
            g_RealEntityUpdateRenderQueue(self, renderQueue);
        }

        void STDMETHODCALLTYPE HookDrawIndexed(
            ID3D11DeviceContext* self,
            UINT indexCount,
            UINT startIndexLocation,
            INT baseVertexLocation)
        {
            if (g_Enabled.load(std::memory_order_relaxed))
            {
                g_DrawIndexedCalls.fetch_add(1, std::memory_order_relaxed);
                g_DrawIndexedIndices.fetch_add(indexCount, std::memory_order_relaxed);
            }
            g_RealDrawIndexed(self, indexCount, startIndexLocation, baseVertexLocation);
        }

        void STDMETHODCALLTYPE HookDraw(
            ID3D11DeviceContext* self,
            UINT vertexCount,
            UINT startVertexLocation)
        {
            if (g_Enabled.load(std::memory_order_relaxed))
            {
                g_DrawCalls.fetch_add(1, std::memory_order_relaxed);
                g_DrawVertices.fetch_add(vertexCount, std::memory_order_relaxed);
            }
            g_RealDraw(self, vertexCount, startVertexLocation);
        }

        HRESULT STDMETHODCALLTYPE HookPresent(IDXGISwapChain* self, UINT syncInterval, UINT flags)
        {
            if (g_Enabled.load(std::memory_order_relaxed))
                g_Presents.fetch_add(1, std::memory_order_relaxed);
            g_PresentObserved.store(true, std::memory_order_release);
            return g_RealPresent(self, syncInterval, flags);
        }

        void InstallContextHooks(ID3D11DeviceContext* context)
        {
            if (!context)
                return;

            // Public ID3D11DeviceContext ABI ordinals from d3d11.h.
            const bool indexed = PatchComVtableEntry(
                context, 12, &HookDrawIndexed, g_RealDrawIndexed,
                "ID3D11DeviceContext::DrawIndexed");
            const bool draw = PatchComVtableEntry(
                context, 13, &HookDraw, g_RealDraw,
                "ID3D11DeviceContext::Draw");
            if (indexed || draw)
                g_Dx11ContextObserved.store(true, std::memory_order_release);
        }

        void CaptureSwapChain(IDXGISwapChain* swapChain)
        {
            if (!swapChain)
                return;
            // Public IDXGISwapChain ABI ordinal.
            PatchComVtableEntry(
                swapChain, 8, &HookPresent, g_RealPresent,
                "IDXGISwapChain::Present");
        }

        HRESULT STDMETHODCALLTYPE HookFactoryCreateSwapChain(
            IDXGIFactory* self,
            IUnknown* device,
            DXGI_SWAP_CHAIN_DESC* desc,
            IDXGISwapChain** swapChain)
        {
            const HRESULT hr = g_RealFactoryCreateSwapChain(self, device, desc, swapChain);
            if (SUCCEEDED(hr) && swapChain && *swapChain)
                CaptureSwapChain(*swapChain);
            return hr;
        }

        void InstallFactoryFromDevice(ID3D11Device* device)
        {
            if (!device)
                return;

            IDXGIDevice* dxgiDevice = nullptr;
            if (FAILED(device->QueryInterface(
                    __uuidof(IDXGIDevice),
                    reinterpret_cast<void**>(&dxgiDevice))) || !dxgiDevice)
            {
                return;
            }

            IDXGIAdapter* adapter = nullptr;
            if (SUCCEEDED(dxgiDevice->GetAdapter(&adapter)) && adapter)
            {
                IDXGIFactory* factory = nullptr;
                if (SUCCEEDED(adapter->GetParent(
                        __uuidof(IDXGIFactory),
                        reinterpret_cast<void**>(&factory))) && factory)
                {
                    // Public IDXGIFactory ABI ordinal.
                    PatchComVtableEntry(
                        factory, 10, &HookFactoryCreateSwapChain,
                        g_RealFactoryCreateSwapChain,
                        "IDXGIFactory::CreateSwapChain");
                    factory->Release();
                }
                adapter->Release();
            }
            dxgiDevice->Release();
        }

        void InstallDeviceHooks(ID3D11Device* device, ID3D11DeviceContext* suppliedContext)
        {
            if (!device)
                return;

            InstallFactoryFromDevice(device);
            if (suppliedContext)
            {
                InstallContextHooks(suppliedContext);
                return;
            }

            ID3D11DeviceContext* context = nullptr;
            device->GetImmediateContext(&context);
            if (context)
            {
                InstallContextHooks(context);
                context->Release();
            }
        }

        HRESULT WINAPI HookD3D11CreateDevice(
            IDXGIAdapter* adapter,
            D3D_DRIVER_TYPE driverType,
            HMODULE software,
            UINT flags,
            const D3D_FEATURE_LEVEL* featureLevels,
            UINT featureLevelCount,
            UINT sdkVersion,
            ID3D11Device** device,
            D3D_FEATURE_LEVEL* featureLevel,
            ID3D11DeviceContext** immediateContext)
        {
            const HRESULT hr = g_RealD3D11CreateDevice(
                adapter, driverType, software, flags,
                featureLevels, featureLevelCount, sdkVersion,
                device, featureLevel, immediateContext);
            if (SUCCEEDED(hr) && device && *device)
            {
                InstallDeviceHooks(
                    *device,
                    immediateContext ? *immediateContext : nullptr);
            }
            return hr;
        }

        HRESULT WINAPI HookD3D11CreateDeviceAndSwapChain(
            IDXGIAdapter* adapter,
            D3D_DRIVER_TYPE driverType,
            HMODULE software,
            UINT flags,
            const D3D_FEATURE_LEVEL* featureLevels,
            UINT featureLevelCount,
            UINT sdkVersion,
            const DXGI_SWAP_CHAIN_DESC* swapChainDesc,
            IDXGISwapChain** swapChain,
            ID3D11Device** device,
            D3D_FEATURE_LEVEL* featureLevel,
            ID3D11DeviceContext** immediateContext)
        {
            const HRESULT hr = g_RealD3D11CreateDeviceAndSwapChain(
                adapter, driverType, software, flags,
                featureLevels, featureLevelCount, sdkVersion,
                swapChainDesc, swapChain, device, featureLevel, immediateContext);
            if (SUCCEEDED(hr))
            {
                if (device && *device)
                {
                    InstallDeviceHooks(
                        *device,
                        immediateContext ? *immediateContext : nullptr);
                }
                if (swapChain && *swapChain)
                    CaptureSwapChain(*swapChain);
            }
            return hr;
        }

        bool InstallDx11CreationObservers(HMODULE renderer)
        {
            if (!renderer)
                return false;

            unsigned installed = 0;
            installed += PatchIatFunctionByName(
                renderer,
                "d3d11.dll",
                "D3D11CreateDevice",
                reinterpret_cast<void*>(&HookD3D11CreateDevice),
                reinterpret_cast<void**>(&g_RealD3D11CreateDevice)) ? 1u : 0u;
            installed += PatchIatFunctionByName(
                renderer,
                "d3d11.dll",
                "D3D11CreateDeviceAndSwapChain",
                reinterpret_cast<void*>(&HookD3D11CreateDeviceAndSwapChain),
                reinterpret_cast<void**>(&g_RealD3D11CreateDeviceAndSwapChain)) ? 1u : 0u;

            LogShimA(
                installed ? LogLevel::Info : LogLevel::Warn,
                kComponent,
                "[OgreProfile] DX11 creation observers installed=%u renderer=0x%p",
                installed,
                renderer);
            return installed != 0;
        }

        bool InstallOgreObservers()
        {
            if (!OgreRuntime::IsLoaded())
                return false;

            void* updateAnimation = FindUniqueFunctionExport(
                "_updateAnimation@Entity@Ogre@@",
                "Entity::_updateAnimation");
            void* softwareVertexBlend = FindUniqueFunctionExport(
                "softwareVertexBlend@Mesh@Ogre@@",
                "Mesh::softwareVertexBlend");
            void* updateRenderQueue = FindUniqueFunctionExport(
                "_updateRenderQueue@Entity@Ogre@@",
                "Entity::_updateRenderQueue");

            if (!updateAnimation || !softwareVertexBlend)
                return false;

            g_RealEntityUpdateAnimation =
                reinterpret_cast<FnEntityUpdateAnimation>(updateAnimation);
            g_RealSoftwareVertexBlend =
                reinterpret_cast<FnSoftwareVertexBlend>(softwareVertexBlend);

            HMODULE ogre = GetModuleHandleA("OgreMain.dll");
            const size_t animationDirect = PatchDirectCallsInModule(
                ogre,
                updateAnimation,
                reinterpret_cast<void*>(&HookEntityUpdateAnimation),
                "Entity::_updateAnimation");
            const size_t animationIat = PatchIatEntriesByTarget(
                GetModuleHandleA(nullptr),
                updateAnimation,
                reinterpret_cast<void*>(&HookEntityUpdateAnimation),
                "Entity::_updateAnimation");
            const size_t blendDirect = PatchDirectCallsInModule(
                ogre,
                softwareVertexBlend,
                reinterpret_cast<void*>(&HookSoftwareVertexBlend),
                "Mesh::softwareVertexBlend");

            if (updateRenderQueue)
            {
                g_RealEntityUpdateRenderQueue =
                    reinterpret_cast<FnEntityUpdateRenderQueue>(updateRenderQueue);
                const size_t renderVtables = PatchEntityVtables(
                    updateRenderQueue,
                    reinterpret_cast<void*>(&HookEntityUpdateRenderQueue));
                g_RenderQueueHookInstalled.store(renderVtables != 0, std::memory_order_release);
                if (!renderVtables)
                {
                    LogShimA(
                        LogLevel::Warn,
                        kComponent,
                        "[OgreProfile] Entity::_updateRenderQueue export resolved but no matching Entity vtable slot was found; visibility-set comparison unavailable");
                }
            }

            const bool usable =
                (animationDirect + animationIat) != 0 && blendDirect != 0;
            if (!usable)
            {
                LogShimA(
                    LogLevel::Warn,
                    kComponent,
                    "[OgreProfile] required Ogre call sites were not found; leaving profiler fail-closed");
                return false;
            }

            g_OgreHooksInstalled.store(true, std::memory_order_release);
            LogShimA(
                LogLevel::Info,
                kComponent,
                "[OgreProfile] Ogre observers active animationCalls=%u+%u softwareBlendCalls=%u renderQueue=%s",
                static_cast<unsigned>(animationDirect),
                static_cast<unsigned>(animationIat),
                static_cast<unsigned>(blendDirect),
                g_RenderQueueHookInstalled.load(std::memory_order_acquire) ? "yes" : "no");
            return true;
        }

        void ReportAndResetInterval()
        {
            const uint64_t animationCalls = g_AnimationCalls.exchange(0, std::memory_order_acq_rel);
            const uint64_t animationTicks = g_AnimationTicks.exchange(0, std::memory_order_acq_rel);
            const uint64_t blendCalls = g_SoftwareBlendCalls.exchange(0, std::memory_order_acq_rel);
            const uint64_t blendVertices = g_SoftwareBlendVertices.exchange(0, std::memory_order_acq_rel);
            const uint64_t blendTicks = g_SoftwareBlendTicks.exchange(0, std::memory_order_acq_rel);
            const uint64_t renderCalls = g_RenderQueueCalls.exchange(0, std::memory_order_acq_rel);
            const uint64_t drawCalls = g_DrawCalls.exchange(0, std::memory_order_acq_rel);
            const uint64_t drawVertices = g_DrawVertices.exchange(0, std::memory_order_acq_rel);
            const uint64_t drawIndexedCalls = g_DrawIndexedCalls.exchange(0, std::memory_order_acq_rel);
            const uint64_t drawIndexedIndices = g_DrawIndexedIndices.exchange(0, std::memory_order_acq_rel);
            const uint64_t presents = g_Presents.exchange(0, std::memory_order_acq_rel);

            uint64_t animationUnique = 0;
            uint64_t skinnedUnique = 0;
            uint64_t renderUnique = 0;
            uint64_t skinnedNotRendered = 0;
            for (size_t i = 0; i < kBloomWords; ++i)
            {
                const uint64_t animationWord =
                    g_AnimationEntityBloom[i].exchange(0, std::memory_order_acq_rel);
                const uint64_t skinnedWord =
                    g_SkinnedEntityBloom[i].exchange(0, std::memory_order_acq_rel);
                const uint64_t renderWord =
                    g_RenderEntityBloom[i].exchange(0, std::memory_order_acq_rel);
                animationUnique += static_cast<uint64_t>(std::popcount(animationWord));
                skinnedUnique += static_cast<uint64_t>(std::popcount(skinnedWord));
                renderUnique += static_cast<uint64_t>(std::popcount(renderWord));
                skinnedNotRendered += static_cast<uint64_t>(std::popcount(skinnedWord & ~renderWord));
            }

            const double frameDivisor = presents ? static_cast<double>(presents) : 1.0;
            const double animationMs = TicksToMs(animationTicks);
            const double blendMs = TicksToMs(blendTicks);
            const double unnecessaryPct = skinnedUnique
                ? (100.0 * static_cast<double>(skinnedNotRendered) /
                    static_cast<double>(skinnedUnique))
                : 0.0;

            if (presents)
            {
                LogShimA(
                    LogLevel::Info,
                    kComponent,
                    "[OgreProfile] frames=%llu animCalls=%llu (%.1f/f) animUnique~=%llu animCPU=%.3fms/f | swBlend=%llu (%.1f/f) verts=%llu (%.0f/f) swCPU=%.3fms/f skinnedUnique~=%llu | renderQueue=%llu (%.1f/f) renderUnique~=%llu skinnedNotRendered~=%llu (%.1f%%) | DX11 Draw=%llu DrawIndexed=%llu submittedVerts=%llu submittedIndices=%llu",
                    static_cast<unsigned long long>(presents),
                    static_cast<unsigned long long>(animationCalls),
                    static_cast<double>(animationCalls) / frameDivisor,
                    static_cast<unsigned long long>(animationUnique),
                    animationMs / frameDivisor,
                    static_cast<unsigned long long>(blendCalls),
                    static_cast<double>(blendCalls) / frameDivisor,
                    static_cast<unsigned long long>(blendVertices),
                    static_cast<double>(blendVertices) / frameDivisor,
                    blendMs / frameDivisor,
                    static_cast<unsigned long long>(skinnedUnique),
                    static_cast<unsigned long long>(renderCalls),
                    static_cast<double>(renderCalls) / frameDivisor,
                    static_cast<unsigned long long>(renderUnique),
                    static_cast<unsigned long long>(skinnedNotRendered),
                    unnecessaryPct,
                    static_cast<unsigned long long>(drawCalls),
                    static_cast<unsigned long long>(drawIndexedCalls),
                    static_cast<unsigned long long>(drawVertices),
                    static_cast<unsigned long long>(drawIndexedIndices));
            }
            else
            {
                LogShimA(
                    LogLevel::Info,
                    kComponent,
                    "[OgreProfile] interval~1s frames=<not observed> animCalls=%llu animUnique~=%llu animCPU=%.3fms | swBlend=%llu verts=%llu swCPU=%.3fms skinnedUnique~=%llu | renderQueue=%llu renderUnique~=%llu skinnedNotRendered~=%llu (%.1f%%) | DX11 context=%s",
                    static_cast<unsigned long long>(animationCalls),
                    static_cast<unsigned long long>(animationUnique),
                    animationMs,
                    static_cast<unsigned long long>(blendCalls),
                    static_cast<unsigned long long>(blendVertices),
                    blendMs,
                    static_cast<unsigned long long>(skinnedUnique),
                    static_cast<unsigned long long>(renderCalls),
                    static_cast<unsigned long long>(renderUnique),
                    static_cast<unsigned long long>(skinnedNotRendered),
                    unnecessaryPct,
                    g_Dx11ContextObserved.load(std::memory_order_acquire) ? "yes" : "no");
            }
        }

        unsigned __stdcall ProfilerThreadProc(void*)
        {
            QueryPerformanceFrequency(&g_QpcFrequency);
            LogShimA(
                LogLevel::Info,
                kComponent,
                "[OgreProfile] enabled; observers are read-only and fail closed when retail Ogre exports/call sites do not match");

            bool ogreAttempted = false;
            bool dx11Attempted = false;
            ULONGLONG nextReport = GetTickCount64() + kReportIntervalMs;

            while (!g_ShutdownRequested.load(std::memory_order_acquire))
            {
                if (!ogreAttempted && OgreRuntime::IsLoaded())
                {
                    ogreAttempted = true;
                    InstallOgreObservers();
                }

                if (!dx11Attempted)
                {
                    HMODULE renderer = GetModuleHandleA("RenderSystem_Direct3D11.dll");
                    if (renderer)
                    {
                        dx11Attempted = true;
                        g_Dx11ImportsPatched.store(
                            InstallDx11CreationObservers(renderer),
                            std::memory_order_release);
                    }
                }

                const ULONGLONG now = GetTickCount64();
                if (now >= nextReport)
                {
                    if (g_OgreHooksInstalled.load(std::memory_order_acquire))
                        ReportAndResetInterval();
                    nextReport = now + kReportIntervalMs;
                }
                Sleep(kPollSleepMs);
            }

            LogShimA(
                LogLevel::Info,
                kComponent,
                "[OgreProfile] reporter stopped (hooks now pass-through until process exit)");
            return 0;
        }
    }

    bool IsOgreAnimationProfilerRequested()
    {
        return ProfilerRequested();
    }

    void InitializeOgreAnimationProfiler()
    {
        if (!ProfilerRequested())
            return;
        if (g_WorkerThread)
            return;

        g_ShutdownRequested.store(false, std::memory_order_release);
        g_Enabled.store(true, std::memory_order_release);
        g_WorkerThread = _beginthreadex(
            nullptr,
            0,
            ProfilerThreadProc,
            nullptr,
            0,
            nullptr);

        if (!g_WorkerThread)
        {
            g_Enabled.store(false, std::memory_order_release);
            LogShimA(
                LogLevel::Warn,
                kComponent,
                "[OgreProfile] failed to start profiler worker (err=%lu)",
                GetLastError());
        }
    }

    void ShutdownOgreAnimationProfiler()
    {
        g_Enabled.store(false, std::memory_order_release);
        g_ShutdownRequested.store(true, std::memory_order_release);

        if (g_WorkerThread)
        {
            WaitForSingleObject(reinterpret_cast<HANDLE>(g_WorkerThread), 2000);
            CloseHandle(reinterpret_cast<HANDLE>(g_WorkerThread));
            g_WorkerThread = 0;
        }
    }
}
