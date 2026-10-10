// ogre_script_import_cache.cpp
// BZR Open Shim - cache of imported Ogre script parses within one parse wave
//
// Copyright (C) 2026 BZR Open Shim contributors
// SPDX-License-Identifier: MIT
//
// Why: Ogre 1.10's ScriptCompiler::compile() clears its import cache
// (mImports) at the end of every script file. Redux re-parses the whole
// "Modable" group on every mod-set change, and ~970 mod materials begin with
// `import * from "BZBase.material"` (or CR_BZBase / sprites), so the same base
// files are opened, lexed, parsed and converted once per importing file.
// Sampled 2026-10-03 (Docs/OGRE_LOAD_HITCH_MEASUREMENT_20261003.md):
// loadImportPath was 30-34% of the Modable parse phase.
//
// What is cached: the *concrete* node list ScriptParser::parse returns for an
// imported file. loadImportPath turns it into a fresh abstract tree with
// convertToAST on every call, and AbstractTreeBuilder only reads the concrete
// nodes, so one concrete list can feed any number of compiles. The abstract
// tree must NOT be cached: processImports/processObjects mutate it in place
// (base overlays and override insertion are not idempotent).
//
// How: two inline detours on OgreMain.dll exports.
//  - ScriptCompiler::loadImportPath(name): on a hit, return
//    convertToAST(cached); on a miss, run the original with a thread-local
//    capture slot armed.
//  - ScriptParser::parse(tokens): when the slot is armed (only inside the
//    original loadImportPath, whose single parse is the import itself), keep a
//    reference to the result.
// A cache entry is keyed by resource group + import name. Entries live for one
// parse wave: when no import was requested for kWaveGapMs the next request
// drops everything first, so a script edited between mission loads is read
// fresh.
//
// ABI (verified against the shipped OgreMain.dll, not the 1.10 headers):
//  - SharedPtr<T> is {T* pRep; SharedPtrInfo* pInfo} (8 bytes).
//  - SharedPtrInfo::useCount is at +0x14, NOT +4 as the public header implies:
//    every retail copy is `lea eax,[esi+14h]; lock xadd [eax],1` and every
//    release `add eax,14h; lock xadd [eax],-1`. Release at zero is
//    vtbl[0](info, 0) then StdAllocPolicy::deallocateBytes(info).
//  - loadImportPath/parse/convertToAST are __thiscall returning the SharedPtr
//    through a hidden pointer (`ret 8`).
//  - The first captured list must read useCount == 1 at +0x14 or the cache
//    disables itself before it ever holds a reference.

#include "ogre_script_import_cache.h"
#include "bzr_options_ui.h"
#include "shim_log.h"

#include <Windows.h>

#include <cstdint>
#include <cstring>
#include <mutex>
#include <string>
#include <unordered_map>

namespace BZROpenShim
{
    namespace
    {
        constexpr char kComponent[] = "script-import-cache";
        constexpr char kDisableSwitch[] = "OPENSHIM_DISABLE_SCRIPT_IMPORT_CACHE";
        constexpr ULONGLONG kWaveGapMs = 1500;
        constexpr uint32_t kUseCountOffset = 0x14;

        struct OgreSharedPtrPod
        {
            void* rep = nullptr;
            void* info = nullptr;
        };
        static_assert(sizeof(OgreSharedPtrPod) == 8, "Ogre 1.10 SharedPtr is two pointers");

        using FnLoadImportPath = OgreSharedPtrPod*(__thiscall*)(void*, OgreSharedPtrPod*, const std::string&);
        using FnParse = OgreSharedPtrPod*(__thiscall*)(void*, OgreSharedPtrPod*, const OgreSharedPtrPod&);
        using FnConvertToAst = OgreSharedPtrPod*(__thiscall*)(void*, OgreSharedPtrPod*, const OgreSharedPtrPod&);
        using FnGetResourceGroup = const std::string&(__thiscall*)(const void*);
        using FnDeallocateBytes = void(__cdecl*)(void*);
        using FnSharedPtrInfoDtor = void(__thiscall*)(void*, unsigned);

        constexpr char kLoadImportPathExport[] =
            "?loadImportPath@ScriptCompiler@Ogre@@AAE?AV?$SharedPtr@V?$list@V?$SharedPtr@"
            "VAbstractNode@Ogre@@@Ogre@@V?$STLAllocator@V?$SharedPtr@VAbstractNode@Ogre@@@Ogre@@"
            "V?$CategorisedAllocPolicy@$0A@@2@@2@@std@@@2@ABV?$basic_string@DU?$char_traits@D@std@@"
            "V?$allocator@D@2@@std@@@Z";
        constexpr char kParseExport[] =
            "?parse@ScriptParser@Ogre@@QAE?AV?$SharedPtr@V?$list@V?$SharedPtr@UConcreteNode@Ogre@@@Ogre@@"
            "V?$STLAllocator@V?$SharedPtr@UConcreteNode@Ogre@@@Ogre@@V?$CategorisedAllocPolicy@$0A@@2@@2@@std@@@2@"
            "ABV?$SharedPtr@V?$vector@V?$SharedPtr@UScriptToken@Ogre@@@Ogre@@V?$STLAllocator@V?$SharedPtr@"
            "UScriptToken@Ogre@@@Ogre@@V?$CategorisedAllocPolicy@$0A@@2@@2@@std@@@2@@Z";
        constexpr char kConvertToAstExport[] =
            "?convertToAST@ScriptCompiler@Ogre@@AAE?AV?$SharedPtr@V?$list@V?$SharedPtr@VAbstractNode@Ogre@@@Ogre@@"
            "V?$STLAllocator@V?$SharedPtr@VAbstractNode@Ogre@@@Ogre@@V?$CategorisedAllocPolicy@$0A@@2@@2@@std@@@2@"
            "ABV?$SharedPtr@V?$list@V?$SharedPtr@UConcreteNode@Ogre@@@Ogre@@V?$STLAllocator@V?$SharedPtr@"
            "UConcreteNode@Ogre@@@Ogre@@V?$CategorisedAllocPolicy@$0A@@2@@2@@std@@@2@@Z";
        constexpr char kGetResourceGroupExport[] =
            "?getResourceGroup@ScriptCompiler@Ogre@@QBEABV?$basic_string@DU?$char_traits@D@std@@"
            "V?$allocator@D@2@@std@@XZ";
        constexpr char kDeallocateBytesExport[] = "?deallocateBytes@StdAllocPolicy@Ogre@@SAXPAX@Z";

        // push ebp; mov ebp,esp; push -1 -- both bodies, then `push imm32` (SEH frame).
        constexpr uint8_t kExpectedPrologue[] = { 0x55, 0x8B, 0xEC, 0x6A, 0xFF };

        InlineDetour32 g_LoadImportPathDetour = {};
        InlineDetour32 g_ParseDetour = {};
        FnLoadImportPath g_LoadImportPathOriginal = nullptr;
        FnParse g_ParseOriginal = nullptr;
        FnConvertToAst g_ConvertToAst = nullptr;
        FnGetResourceGroup g_GetResourceGroup = nullptr;
        FnDeallocateBytes g_DeallocateBytes = nullptr;

        bool g_Installed = false;
        bool g_FailureLogged = false;
        bool g_DisabledLogged = false;
        // Set once at runtime if the layout check fails; hooks then pass through.
        volatile LONG g_LayoutRejected = 0;

        std::mutex g_Mutex;
        std::unordered_map<std::string, OgreSharedPtrPod> g_Cache;
        ULONGLONG g_LastRequestTick = 0;
        uint32_t g_WaveHits = 0;
        uint32_t g_WaveMisses = 0;
        uint32_t g_Waves = 0;

        thread_local OgreSharedPtrPod* t_CaptureSlot = nullptr;

        volatile LONG* UseCount(void* info)
        {
            return reinterpret_cast<volatile LONG*>(static_cast<uint8_t*>(info) + kUseCountOffset);
        }

        void AddRef(const OgreSharedPtrPod& p)
        {
            if (p.rep && p.info)
                InterlockedIncrement(UseCount(p.info));
        }

        // SharedPtr::release(): useCount at zero runs the info's destructor
        // (which frees the list) and returns the info block to Ogre's allocator.
        void Release(OgreSharedPtrPod& p)
        {
            if (p.rep && p.info && InterlockedDecrement(UseCount(p.info)) == 0)
            {
                void** vtbl = *static_cast<void***>(p.info);
                reinterpret_cast<FnSharedPtrInfoDtor>(vtbl[0])(p.info, 0);
                g_DeallocateBytes(p.info);
            }
            p = {};
        }

        // Caller holds g_Mutex.
        void BeginWaveIfIdleLocked()
        {
            const ULONGLONG now = GetTickCount64();
            if (g_LastRequestTick != 0 && now - g_LastRequestTick > kWaveGapMs)
            {
                LogShimA(LogLevel::Info, kComponent,
                         "[SCRIPTIMPORT] wave %u done: %u hits, %u parsed imports cached",
                         g_Waves, g_WaveHits, g_WaveMisses);
                for (auto& entry : g_Cache)
                    Release(entry.second);
                g_Cache.clear();
                g_WaveHits = g_WaveMisses = 0;
            }
            if (g_LastRequestTick == 0 || now - g_LastRequestTick > kWaveGapMs)
                ++g_Waves;
            g_LastRequestTick = now;
        }

        std::string CacheKey(void* compiler, const std::string& name)
        {
            std::string key = g_GetResourceGroup(compiler);
            key.push_back('\x1f');
            key += name;
            return key;
        }

        OgreSharedPtrPod* __fastcall ParseHook(void* parser, void* /*edx*/,
                                               OgreSharedPtrPod* ret,
                                               const OgreSharedPtrPod& tokens)
        {
            OgreSharedPtrPod* result = g_ParseOriginal(parser, ret, tokens);
            OgreSharedPtrPod* slot = t_CaptureSlot;
            if (slot && !slot->rep && result && result->rep && result->info)
            {
                t_CaptureSlot = nullptr;   // only the import's own parse
                // A fresh list is referenced by `ret` alone. Anything else
                // means the useCount offset is not what the retail code uses.
                if (*UseCount(result->info) != 1)
                {
                    if (InterlockedExchange(&g_LayoutRejected, 1) == 0)
                        LogShimA(LogLevel::Error, kComponent,
                                 "[SCRIPTIMPORT] SharedPtr layout check failed (useCount@+0x%X=%ld); "
                                 "cache disabled, Ogre unchanged",
                                 kUseCountOffset, static_cast<long>(*UseCount(result->info)));
                    return result;
                }
                *slot = *result;
                AddRef(*slot);
            }
            return result;
        }

        OgreSharedPtrPod* __fastcall LoadImportPathHook(void* compiler, void* /*edx*/,
                                                        OgreSharedPtrPod* ret,
                                                        const std::string& name)
        {
            if (g_LayoutRejected)
                return g_LoadImportPathOriginal(compiler, ret, name);

            const std::string key = CacheKey(compiler, name);
            OgreSharedPtrPod cached;
            {
                std::lock_guard<std::mutex> lock(g_Mutex);
                BeginWaveIfIdleLocked();
                auto it = g_Cache.find(key);
                if (it != g_Cache.end())
                {
                    cached = it->second;
                    AddRef(cached);          // keep it alive across the unlocked convert
                    ++g_WaveHits;
                }
            }

            if (cached.rep)
            {
                struct Hold
                {
                    OgreSharedPtrPod& p;
                    ~Hold() { Release(p); }
                } hold{ cached };
                return g_ConvertToAst(compiler, ret, cached);
            }

            OgreSharedPtrPod captured;
            struct Arm
            {
                OgreSharedPtrPod* previous;
                explicit Arm(OgreSharedPtrPod* slot) : previous(t_CaptureSlot) { t_CaptureSlot = slot; }
                ~Arm() { t_CaptureSlot = previous; }
            };
            OgreSharedPtrPod* result = nullptr;
            {
                Arm arm(&captured);   // disarmed even if Ogre throws (missing import)
                result = g_LoadImportPathOriginal(compiler, ret, name);
            }

            if (captured.rep)
            {
                std::lock_guard<std::mutex> lock(g_Mutex);
                auto inserted = g_Cache.emplace(key, captured);
                if (inserted.second)
                    ++g_WaveMisses;
                else
                    Release(captured);   // another thread got there first
            }
            return result;
        }

        bool DisabledByEnvironment()
        {
            char value[16] = {};
            const DWORD len = GetEnvironmentVariableA(kDisableSwitch, value, sizeof(value));
            if (len == 0 || len >= sizeof(value))
                return false;
            return !(value[0] == '0' && value[1] == '\0');
        }

        uint8_t* ResolveExportBody(HMODULE module, const char* name)
        {
            auto* proc = reinterpret_cast<uint8_t*>(GetProcAddress(module, name));
            if (proc && proc[0] == 0xE9)   // incremental-link thunk
            {
                int32_t rel = 0;
                std::memcpy(&rel, proc + 1, sizeof(rel));
                proc = proc + 5 + rel;
            }
            return proc;
        }

        void LogFailureOnce(const char* what)
        {
            if (g_FailureLogged)
                return;
            g_FailureLogged = true;
            LogShimA(LogLevel::Warn, kComponent, "[SCRIPTIMPORT] not installed: %s", what);
        }
    }

    void InstallOgreScriptImportCacheIfPossible()
    {
        if (g_Installed)
            return;
        if (DisabledByEnvironment())
        {
            if (!g_DisabledLogged)
            {
                g_DisabledLogged = true;
                LogShimA(LogLevel::Info, kComponent, "[SCRIPTIMPORT] disabled by %s", kDisableSwitch);
            }
            return;
        }

        HMODULE ogreMain = GetModuleHandleA("OgreMain.dll");
        if (!ogreMain)
            return;   // a later retry installs it

        uint8_t* loadImportPath = ResolveExportBody(ogreMain, kLoadImportPathExport);
        uint8_t* parse = ResolveExportBody(ogreMain, kParseExport);
        g_ConvertToAst = reinterpret_cast<FnConvertToAst>(ResolveExportBody(ogreMain, kConvertToAstExport));
        g_GetResourceGroup = reinterpret_cast<FnGetResourceGroup>(
            ResolveExportBody(ogreMain, kGetResourceGroupExport));
        g_DeallocateBytes = reinterpret_cast<FnDeallocateBytes>(
            GetProcAddress(ogreMain, kDeallocateBytesExport));
        if (!loadImportPath || !parse || !g_ConvertToAst || !g_GetResourceGroup || !g_DeallocateBytes)
        {
            LogFailureOnce("an OgreMain export did not resolve");
            return;
        }
        if (!ExpectedBytesMatchAt(reinterpret_cast<uintptr_t>(loadImportPath), kExpectedPrologue,
                                  sizeof(kExpectedPrologue)) ||
            !ExpectedBytesMatchAt(reinterpret_cast<uintptr_t>(parse), kExpectedPrologue,
                                  sizeof(kExpectedPrologue)))
        {
            LogFailureOnce("unexpected loadImportPath/parse prologue");
            return;
        }

        // parse first: until loadImportPath is detoured nothing arms the
        // capture slot, so the parse hook alone is a pure pass-through.
        if (!InstallInlineDetour32(g_ParseDetour, reinterpret_cast<uintptr_t>(parse),
                                   reinterpret_cast<void*>(&ParseHook), sizeof(kExpectedPrologue),
                                   kExpectedPrologue, sizeof(kExpectedPrologue)))
        {
            LogFailureOnce("ScriptParser::parse detour failed");
            return;
        }
        g_ParseOriginal = reinterpret_cast<FnParse>(g_ParseDetour.trampoline);

        if (!InstallInlineDetour32(g_LoadImportPathDetour, reinterpret_cast<uintptr_t>(loadImportPath),
                                   reinterpret_cast<void*>(&LoadImportPathHook), sizeof(kExpectedPrologue),
                                   kExpectedPrologue, sizeof(kExpectedPrologue)))
        {
            LogFailureOnce("ScriptCompiler::loadImportPath detour failed (parse hook stays a pass-through)");
            return;
        }
        g_LoadImportPathOriginal = reinterpret_cast<FnLoadImportPath>(g_LoadImportPathDetour.trampoline);
        g_Installed = true;
        LogShimA(LogLevel::Info, kComponent,
                 "[SCRIPTIMPORT] installed loadImportPath=0x%08X parse=0x%08X (wave gap %u ms)",
                 static_cast<uint32_t>(reinterpret_cast<uintptr_t>(loadImportPath)),
                 static_cast<uint32_t>(reinterpret_cast<uintptr_t>(parse)),
                 static_cast<unsigned>(kWaveGapMs));
    }
}
