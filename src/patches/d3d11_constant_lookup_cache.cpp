// Direct3D 11 constant lookup cache: stop D3D11HLSLProgram::getConstantBuffer
// from walking a string map for every shader constant on every draw.
//
// Why: getConstantBuffer copies each of a program's shader variables into its
// constant buffer, and finds where each one lives in the parameters by name:
// GpuProgramParameters::getConstantDefinition(var.name), a std::map<String>
// lookup with string compares down the tree. On misn17 co-op that lookup is
// about half of getConstantBuffer's ~7% of the main thread.
//
// What: the one call to getConstantDefinition inside getConstantBuffer (the
// loop over mShaderVars) is redirected to CachedGetConstantDefinition. The
// caller reads only the definition's constType and physicalIndex, and picks
// the float, int or uint list of the parameters from constType. A cache slot
// keyed by the shader variable's address, the parameters' named-constant set
// and a generation counter keeps those two values; on a hit the hook returns
// the slot itself as the definition. A hit is used only when physicalIndex
// plus the variable's size still lies inside the list it reads, so a stale
// slot can at worst feed a draw the wrong constant, never read outside a
// buffer.
//
// The generation counter moves on every D3D11HLSLProgram::unloadHighLevelImpl
// (which frees the shader variables a slot is keyed by) and
// buildConstantDefinitions (which replaces the named-constant set). Both are
// virtual, reached only through their incremental-link jump thunks (vtable
// slots 0x158 and 0x160 of the program vtable, and the device-lost path
// calls unloadHighLevelImpl through that slot). The unload thunk is
// retargeted; the build thunk straddles a cache line, so its one reference,
// the vtable slot, is repointed instead. The program destructor reaches unloadHighLevelImpl
// through unload().
//
// Only the thread that first calls the hook uses the cache; any other thread
// gets the stock lookup. Exceptions from the stock lookup (an unknown name)
// pass through untouched: the hook has nothing to unwind.
//
// How: the sites are module_addresses rows in scripts/patches.json, bound only
// on RenderSystem_Direct3D11.dll TimeDateStamp 0x586F03D3 / SizeOfImage
// 0xF3000 with guard bytes. The call is `call dword ptr [IAT]` (FF 15, six
// bytes); it becomes `nop; call rel32` so the return address is unchanged,
// written in one locked 8-byte exchange, as is the unload thunk.
//
// Config: on by default; OPENSHIM_DISABLE_D3D11_CONSTANT_CACHE=1 leaves the
// renderer stock.
#include "bool_token.h"
#include "d3d11_constant_lookup_cache.h"
#include "hook_engine.h"
#include "shim_log.h"

#include <Windows.h>
#include <intrin.h>

#include <atomic>
#include <cstdint>
#include <cstring>

namespace BZROpenShim
{
    namespace
    {
        constexpr char kComponent[] = "dx11-constcache";

        // GpuProgramParameters (Ogre 1.10.0, OgreMain TimeDateStamp
        // 0x5866BF6A): mNamedConstants' pointer, and each constant list as a
        // std::vector {begin, end, capacity}.
        constexpr uint32_t kNamedConstantsOffset = 0x88;
        constexpr uint32_t kFloatListOffset = 0x20;
        constexpr uint32_t kIntListOffset = 0x40;
        constexpr uint32_t kUintListOffset = 0x50;
        // ShaderVarWithPosInBuf: the String name at +0 (what the call passes),
        // the byte count copied out of the list at +0x18.
        constexpr uint32_t kShaderVarSizeOffset = 0x18;

        using FnGetConstantDefinition = const uint32_t*(__fastcall*)(const uint8_t* params, void*, const uint8_t* name);
        using FnIsFloat = bool(__cdecl*)(uint32_t constType);
        using FnVoidMember = void(__fastcall*)(void* self, void*);

        FnGetConstantDefinition g_RealGetConstantDefinition = nullptr;
        FnIsFloat g_IsFloat = nullptr;
        FnVoidMember g_RealUnloadHighLevelImpl = nullptr;
        FnVoidMember g_RealBuildConstantDefinitions = nullptr;

        std::atomic<uint32_t> g_Generation{1};
        volatile LONG g_OwnerThread = 0;

        // The first two fields after the key are what the caller reads as a
        // GpuConstantDefinition: constType, then physicalIndex.
        struct Slot
        {
            const uint8_t* var;
            const void* namedConstants;
            uint32_t generation;
            uint32_t constType;
            uint32_t physicalIndex;
            uint32_t listOffset;
            uint32_t pad[2];
        };
        static_assert(sizeof(Slot) == 32, "slots are half a cache line");

        constexpr size_t kSlotCount = 8192;
        alignas(64) Slot g_Slots[kSlotCount];

        uint32_t g_Hits = 0;
        uint32_t g_Misses = 0;
        uint32_t g_Uncached = 0;
        bool g_Reported = false;

        uint32_t ListOffsetFor(uint32_t constType)
        {
            // The same split getConstantBuffer makes after the lookup.
            if (g_IsFloat(constType))
                return kFloatListOffset;
            if (constType - 0x16u <= 3u)
                return kIntListOffset;
            if (constType - 0x28u <= 3u)
                return kUintListOffset;
            return 0;
        }

        bool ListHolds(const uint8_t* params, uint32_t listOffset, uint32_t physicalIndex, uint32_t size)
        {
            const auto begin = *reinterpret_cast<const uintptr_t*>(params + listOffset);
            const auto end = *reinterpret_cast<const uintptr_t*>(params + listOffset + 4);
            if (!begin || end < begin)
                return false;
            return static_cast<uint64_t>(physicalIndex) * 4u + size <= end - begin;
        }

        void ReportOnce()
        {
            if (g_Reported || g_Hits + g_Misses < (1u << 22))
                return;
            g_Reported = true;
            const double total = static_cast<double>(g_Hits) + g_Misses;
            LogShimA(LogLevel::Info, kComponent,
                     "[DX11 ConstCache] %u hits, %u misses (%.2f%% hit), %u uncacheable, generation %u",
                     g_Hits, g_Misses, 100.0 * g_Hits / total, g_Uncached, g_Generation.load());
        }

        const void* __fastcall CachedGetConstantDefinition(const uint8_t* params, void*, const uint8_t* var)
        {
            const LONG thread = static_cast<LONG>(__readfsdword(0x24));
            if (thread != g_OwnerThread &&
                (g_OwnerThread != 0 || InterlockedCompareExchange(&g_OwnerThread, thread, 0) != 0))
            {
                return g_RealGetConstantDefinition(params, nullptr, var);
            }

            const void* namedConstants = *reinterpret_cast<const void* const*>(params + kNamedConstantsOffset);
            const uint32_t generation = g_Generation.load(std::memory_order_acquire);
            const uint32_t size = *reinterpret_cast<const uint32_t*>(var + kShaderVarSizeOffset);
            const uintptr_t key = reinterpret_cast<uintptr_t>(var);
            Slot& slot = g_Slots[((key >> 5) ^ (key >> 18)) & (kSlotCount - 1)];

            if (slot.var == var && slot.namedConstants == namedConstants && slot.generation == generation &&
                namedConstants && ListHolds(params, slot.listOffset, slot.physicalIndex, size))
            {
                ++g_Hits;
                return &slot.constType;
            }

            const uint32_t* definition = g_RealGetConstantDefinition(params, nullptr, var);
            ++g_Misses;
            const uint32_t listOffset = ListOffsetFor(definition[0]);
            if (listOffset && namedConstants && ListHolds(params, listOffset, definition[1], size))
            {
                slot.var = var;
                slot.namedConstants = namedConstants;
                slot.generation = generation;
                slot.constType = definition[0];
                slot.physicalIndex = definition[1];
                slot.listOffset = listOffset;
            }
            else
            {
                ++g_Uncached;
            }
            ReportOnce();
            return definition;
        }

        // Bumped before and after, so a slot filled while the stock code runs
        // is stale too, and so is every slot if the stock code throws.
        void __fastcall HookUnloadHighLevelImpl(void* program, void*)
        {
            g_Generation.fetch_add(1, std::memory_order_acq_rel);
            g_RealUnloadHighLevelImpl(program, nullptr);
            g_Generation.fetch_add(1, std::memory_order_acq_rel);
        }

        void __fastcall HookBuildConstantDefinitions(void* program, void*)
        {
            g_Generation.fetch_add(1, std::memory_order_acq_rel);
            g_RealBuildConstantDefinitions(program, nullptr);
            g_Generation.fetch_add(1, std::memory_order_acq_rel);
        }

        // Replaces `len` (<= 8) bytes at `address` (expected to be `from`) with
        // `to` in one locked compare-exchange of the eight bytes there. The
        // eight bytes must not cross a cache line.
        bool SwapCode(uint32_t address, const uint8_t* from, const uint8_t* to, size_t len)
        {
            if (len > 8 || (address & 63u) > 56u)
                return false;
            auto* target = reinterpret_cast<volatile LONG64*>(address);
            DWORD oldProtect = 0;
            if (!VirtualProtect(reinterpret_cast<void*>(address), 8, PAGE_EXECUTE_READWRITE, &oldProtect))
                return false;
            LONG64 current = 0;
            std::memcpy(&current, reinterpret_cast<const void*>(address), sizeof(current));
            bool swapped = false;
            if (std::memcmp(&current, from, len) == 0)
            {
                LONG64 replacement = current;
                std::memcpy(&replacement, to, len);
                swapped = InterlockedCompareExchange64(target, replacement, current) == current;
            }
            DWORD ignored = 0;
            VirtualProtect(reinterpret_cast<void*>(address), 8, oldProtect, &ignored);
            FlushInstructionCache(GetCurrentProcess(), reinterpret_cast<void*>(address), 8);
            return swapped;
        }

        bool SwapPointer(uint32_t address, uint32_t from, uint32_t to)
        {
            if (address & 3u)
                return false;
            DWORD oldProtect = 0;
            if (!VirtualProtect(reinterpret_cast<void*>(address), 4, PAGE_READWRITE, &oldProtect))
                return false;
            const bool swapped = static_cast<uint32_t>(InterlockedCompareExchange(
                reinterpret_cast<volatile LONG*>(address), static_cast<LONG>(to), static_cast<LONG>(from))) == from;
            DWORD ignored = 0;
            VirtualProtect(reinterpret_cast<void*>(address), 4, oldProtect, &ignored);
            return swapped;
        }

        uint32_t JumpTarget(uint32_t thunk)
        {
            int32_t rel = 0;
            std::memcpy(&rel, reinterpret_cast<const void*>(thunk + 1), sizeof(rel));
            return thunk + 5 + rel;
        }

        bool Disabled()
        {
            char value[16] = {};
            const DWORD n = GetEnvironmentVariableA("OPENSHIM_DISABLE_D3D11_CONSTANT_CACHE", value,
                                                    static_cast<DWORD>(sizeof(value)));
            return n > 0 && n < sizeof(value) && BoolToken::IsTruthy(value, n);
        }

        bool Install(HMODULE renderer, HMODULE ogre)
        {
            uint32_t getConstantBuffer = 0, call = 0;
            uint32_t unloadThunk = 0, unloadBody = 0, buildThunk = 0, buildBody = 0, buildSlot = 0;
            const HookEngine::EngineRow rows[] = {
                {"D3D11HLSLGetConstantBuffer", &getConstantBuffer},
                {"D3D11HLSLGetConstantBufferDefinitionCall", &call},
                {"D3D11HLSLUnloadHighLevelImplThunk", &unloadThunk},
                {"D3D11HLSLUnloadHighLevelImpl", &unloadBody},
                {"D3D11HLSLBuildConstantDefinitionsThunk", &buildThunk},
                {"D3D11HLSLBuildConstantDefinitions", &buildBody},
                {"D3D11HLSLBuildConstantDefinitionsVtableSlot", &buildSlot},
            };
            if (!HookEngine::BindModuleRows("D3D11 constant cache", renderer, rows))
                return false;

            // The rows must be the functions the exports name: each export is
            // the thunk, and each thunk jumps to the recorded body.
            const auto exportAt = [](HMODULE module, const char* name) {
                return static_cast<uint32_t>(reinterpret_cast<uintptr_t>(GetProcAddress(module, name)));
            };
            const uint32_t cbExport = exportAt(renderer,
                "?getConstantBuffer@D3D11HLSLProgram@Ogre@@QAEPAUID3D11Buffer@@V?$SharedPtr@VGpuProgramParameters@Ogre@@@2@G@Z");
            if (!cbExport || *reinterpret_cast<const uint8_t*>(cbExport) != 0xE9 ||
                JumpTarget(cbExport) != getConstantBuffer ||
                exportAt(renderer, "?unloadHighLevelImpl@D3D11HLSLProgram@Ogre@@MAEXXZ") != unloadThunk ||
                JumpTarget(unloadThunk) != unloadBody ||
                exportAt(renderer, "?buildConstantDefinitions@D3D11HLSLProgram@Ogre@@UBEXXZ") != buildThunk ||
                JumpTarget(buildThunk) != buildBody ||
                *reinterpret_cast<const uint32_t*>(buildSlot) != buildThunk)
            {
                LogShimA(LogLevel::Warn, kComponent, "[DX11 ConstCache] rows do not match the renderer exports; left stock");
                return false;
            }

            const auto realGetDef = reinterpret_cast<FnGetConstantDefinition>(GetProcAddress(ogre,
                "?getConstantDefinition@GpuProgramParameters@Ogre@@QBEABUGpuConstantDefinition@2@"
                "ABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z"));
            const auto isFloat = reinterpret_cast<FnIsFloat>(GetProcAddress(ogre,
                "?isFloat@GpuConstantDefinition@Ogre@@SA_NW4GpuConstantType@2@@Z"));
            if (!realGetDef || !isFloat)
            {
                LogShimA(LogLevel::Warn, kComponent, "[DX11 ConstCache] OgreMain exports missing; left stock");
                return false;
            }

            // The call (row + 4) and the isFloat call after it go through the
            // renderer's import slots; both slots must still hold the OgreMain
            // exports, or someone else already owns this call.
            const auto* image = reinterpret_cast<const uint8_t*>(renderer);
            const auto* nt = reinterpret_cast<const IMAGE_NT_HEADERS32*>(
                image + reinterpret_cast<const IMAGE_DOS_HEADER*>(image)->e_lfanew);
            const uint32_t imageBase = static_cast<uint32_t>(reinterpret_cast<uintptr_t>(image));
            const uint32_t imageEnd = imageBase + nt->OptionalHeader.SizeOfImage;
            const auto importSlotHolds = [&](uint32_t operandAddress, const void* expected) {
                uint32_t slot = 0;
                std::memcpy(&slot, reinterpret_cast<const void*>(operandAddress), sizeof(slot));
                return slot >= imageBase && slot + 4 <= imageEnd &&
                       *reinterpret_cast<void* const*>(slot) == expected;
            };
            const uint32_t site = call + 4;
            if (!importSlotHolds(site + 2, reinterpret_cast<const void*>(realGetDef)) ||
                !importSlotHolds(call + 0x10, reinterpret_cast<const void*>(isFloat)))
            {
                LogShimA(LogLevel::Warn, kComponent,
                         "[DX11 ConstCache] getConstantDefinition import is not OgreMain's; left stock");
                return false;
            }

            g_RealGetConstantDefinition = realGetDef;
            g_IsFloat = isFloat;
            g_RealUnloadHighLevelImpl = reinterpret_cast<FnVoidMember>(unloadBody);
            g_RealBuildConstantDefinitions = reinterpret_cast<FnVoidMember>(buildBody);

            uint8_t unloadOld[5], callOld[6];
            std::memcpy(unloadOld, reinterpret_cast<const void*>(unloadThunk), 5);
            std::memcpy(callOld, reinterpret_cast<const void*>(site), 6);
            const auto unloadNew = HookEngine::MakeJmp5Payload(unloadThunk,
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(&HookUnloadHighLevelImpl)));
            const auto buildHook = static_cast<uint32_t>(reinterpret_cast<uintptr_t>(&HookBuildConstantDefinitions));
            uint8_t callNew[6] = {0x90, 0xE8};
            const int32_t rel = static_cast<int32_t>(
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(&CachedGetConstantDefinition)) - (site + 6));
            std::memcpy(callNew + 2, &rel, sizeof(rel));

            // The invalidation goes in before anything can fill a slot. The
            // renderer is live here, so every write is one locked exchange of
            // whole instructions: a thread sees the old code or the new.
            HookEngine::CodePatchLock lock;
            if (!SwapCode(unloadThunk, unloadOld, unloadNew.data(), 5))
            {
                LogShimA(LogLevel::Warn, kComponent, "[DX11 ConstCache] could not patch the unload thunk; left stock");
                return false;
            }
            if (!SwapPointer(buildSlot, buildThunk, buildHook))
            {
                SwapCode(unloadThunk, unloadNew.data(), unloadOld, 5);
                LogShimA(LogLevel::Warn, kComponent, "[DX11 ConstCache] could not patch the build vtable slot; left stock");
                return false;
            }
            if (!SwapCode(site, callOld, callNew, 6))
            {
                SwapPointer(buildSlot, buildHook, buildThunk);
                SwapCode(unloadThunk, unloadNew.data(), unloadOld, 5);
                LogShimA(LogLevel::Warn, kComponent, "[DX11 ConstCache] could not patch the lookup call; left stock");
                return false;
            }
            return true;
        }
    }

    void InstallD3D11ConstantLookupCacheIfPossible()
    {
        static bool attempted = false;
        if (attempted)
            return;
        HMODULE renderer = GetModuleHandleA("RenderSystem_Direct3D11.dll");
        HMODULE ogre = GetModuleHandleA("OgreMain.dll");
        if (!renderer || !ogre)
            return;
        attempted = true;

        if (Disabled())
        {
            LogShimA(LogLevel::Info, kComponent, "[DX11 ConstCache] disabled by OPENSHIM_DISABLE_D3D11_CONSTANT_CACHE");
            return;
        }
        if (Install(renderer, ogre))
        {
            LogShimA(LogLevel::Info, kComponent,
                     "[DX11 ConstCache] installed: getConstantBuffer constant lookups are cached per program");
        }
    }
}
