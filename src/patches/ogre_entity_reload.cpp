// Preserve BZR's cached Bone/SkeletonInstance/AnimationState pointers when Ogre
// lazily rebuilds an Entity after D3D11's MeshManager::reloadAll. See the crash
// investigation in reverse_engineering/d3d11_restore_entity_lifetime_20261007.md.
#include "bzr_hooks.h"
#include "bzr_hooks_internal.h"
#include "bzr_options_ui.h"
#include "ogre_entity_reload.h"
#include "openshim_preset_migration.h"
#include "patcher.h"
#include "shim_log.h"
#include <Windows.h>
#include <cstring>
#include <filesystem>
#include <string>

namespace BZROpenShim::Hooks
{
    static_assert(sizeof(void*) == 4, "Entity reload guard requires the shipped Win32 Ogre ABI");
    namespace
    {
        using namespace OgreEntityReload;
        using Initialise = void(__thiscall*)(void*, bool);
        using Destructor = void(__thiscall*)(void*);
        using Deallocate = void(__cdecl*)(void*);
        using NumBones = std::uint16_t(__thiscall*)(const void*);

        InlineDetour32 g_initialiseDetour{};
        Initialise g_initialise = nullptr;
        Destructor g_skeletonDestructor = nullptr;
        Destructor g_animationDestructor = nullptr;
        Deallocate g_deallocate = nullptr;
        Deallocate g_alignedDeallocate = nullptr;
        NumBones g_numBones = nullptr;
        bool g_attempted = false;
        unsigned g_preserved = 0;
        unsigned g_declined = 0;

        // Qualified shipped OgreMain ABI, not upstream-header offsets. The
        // installer requires its exact hash AND live export/body signatures.
        template<class T> T& Field(void* object, std::size_t offset) noexcept
        {
            return *reinterpret_cast<T*>(static_cast<std::uint8_t*>(object) + offset);
        }

        AnimationOwnership ReadOwnership(void* entity) noexcept
        {
            return {Field<void*>(entity, 0x1BC), Field<void*>(entity, 0xEC),
                Field<void*>(entity, 0x15C), Field<void*>(entity, 0x158),
                Field<std::uint32_t*>(entity, 0x168), Field<std::uint16_t>(entity, 0x160)};
        }

        void WriteOwnership(void* entity, const AnimationOwnership& state) noexcept
        {
            Field<void*>(entity, 0x1BC) = state.skeleton;
            Field<void*>(entity, 0xEC) = state.animationStates;
            Field<void*>(entity, 0x15C) = state.boneMatrices;
            Field<void*>(entity, 0x158) = state.boneWorldMatrices;
            Field<std::uint32_t*>(entity, 0x168) = state.frameBonesLastUpdated;
            Field<std::uint16_t>(entity, 0x160) = state.numBoneMatrices;
            Field<std::uint32_t>(entity, 0x164) = UINT32_MAX; // force animation update
        }

        void DestroyOwnership(const AnimationOwnership& state) noexcept
        {
            // Match _deinitialise's allocators, including the non-virtual
            // AnimationStateSet destructor. Never free Ogre objects in our CRT.
            if (state.boneWorldMatrices) g_alignedDeallocate(state.boneWorldMatrices);
            if (state.frameBonesLastUpdated) g_deallocate(state.frameBonesLastUpdated);
            if (state.skeleton)
            {
                g_skeletonDestructor(state.skeleton);
                g_deallocate(state.skeleton);
            }
            if (state.boneMatrices) g_alignedDeallocate(state.boneMatrices);
            if (state.animationStates)
            {
                g_animationDestructor(state.animationStates);
                g_deallocate(state.animationStates);
            }
        }

        void __fastcall EntityInitialiseHook(void* entity, void*, bool force)
        {
            if (!entity || (!force && Field<bool>(entity, 0x1C0)))
            {
                g_initialise(entity, force);
                return;
            }

            const AnimationOwnership state = ReadOwnership(entity);
            void* const mesh = Field<void*>(entity, 0xD4);
            const bool shared = Field<void*>(entity, 0x16C) != nullptr;
            // detachAllObjectsImpl needs mSkeletonInstance to free TagPoints;
            // stealing it is safe only for an empty ChildObjectList.
            const bool attached = Field<std::uint32_t>(entity, 0x20C) != 0;
            void* const master = state.skeleton ? Field<void*>(state.skeleton, 0x138) : nullptr;
            void* const meshMaster = mesh ? Field<void*>(mesh, 0x14C) : nullptr;
            const bool preserve = CanPreserve(force, Field<bool>(entity, 0x1C0), state,
                shared, attached, master, meshMaster,
                state.skeleton ? g_numBones(state.skeleton) : 0,
                master ? g_numBones(master) : 0);
            if (!preserve)
            {
                if (force && state.skeleton && g_declined++ < 4)
                    Log(L"[ENTITY-RELOAD] CPU preservation declined entity=%p shared=%u attached=%u (ownership/topology gate)\n",
                        entity, shared ? 1u : 0u, attached ? 1u : 0u);
                g_initialise(entity, force);
                return;
            }

            RebuildPreservingAnimation(
                [entity]() noexcept { return ReadOwnership(entity); },
                [entity](const AnimationOwnership& value) noexcept { WriteOwnership(entity, value); },
                [entity, force]() { g_initialise(entity, force); },
                DestroyOwnership);
            if (++g_preserved <= 4 || (g_preserved % 256) == 0)
                Log(L"[ENTITY-RELOAD] Preserved CPU animation entity=%p skeleton=%p bones=%u rebuilds=%u\n",
                    entity, state.skeleton, static_cast<unsigned>(state.numBoneMatrices), g_preserved);
        }

        std::uint8_t* ExportBody(HMODULE module, const char* name)
        {
            auto* body = reinterpret_cast<std::uint8_t*>(GetProcAddress(module, name));
            const auto base = reinterpret_cast<std::uintptr_t>(module);
            const auto* dos = reinterpret_cast<const IMAGE_DOS_HEADER*>(module);
            const auto* nt = reinterpret_cast<const IMAGE_NT_HEADERS32*>(base + dos->e_lfanew);
            const std::size_t size = nt->OptionalHeader.SizeOfImage;
            const auto inModule = [base, size](const std::uint8_t* address)
            {
                const auto va = reinterpret_cast<std::uintptr_t>(address);
                return va >= base && va - base <= size && size - (va - base) >= 16;
            };
            // Follow bounded incremental-link thunks so internal calls are
            // intercepted. Decline a pre-existing jump outside this module.
            for (unsigned depth = 0; inModule(body) && body[0] == 0xE9 && depth < 4; ++depth)
            {
                std::int32_t relative = 0;
                std::memcpy(&relative, body + 1, sizeof(relative));
                body += 5 + relative;
            }
            return inModule(body) && body[0] != 0xE9 ? body : nullptr;
        }

        template<std::size_t N>
        bool Matches(const std::uint8_t* body, const std::uint8_t (&bytes)[N])
        {
            return body && ExpectedBytesMatchAt(reinterpret_cast<std::uintptr_t>(body), bytes, N);
        }
    }

    void InstallEntityReloadLifetimeHookIfPossible()
    {
        if (g_attempted) return;
        const HMODULE module = GetModuleHandleW(L"OgreMain.dll");
        if (!module) return; // deferred installer retries after module load
        g_attempted = true;
        if (EnvFlagEnabled("OPENSHIM_DISABLE_ENTITY_RELOAD_FIX"))
        {
            Log(L"[ENTITY-RELOAD] Disabled by environment\n");
            return;
        }

        wchar_t path[MAX_PATH]{};
        const DWORD length = GetModuleFileNameW(module, path, MAX_PATH);
        std::string hash;
        if (length == 0 || length >= MAX_PATH ||
            !TryComputeFileSha256Hex(std::filesystem::path(path), hash) ||
            hash != "e5e693960b95ad0d60733a3b688464a6c6cba234e86950698f9c2bea4acfeb45")
        {
            Log(L"[ENTITY-RELOAD] Ogre build not qualified sha256=%hs; hook skipped\n", hash.c_str());
            return;
        }

        auto* body = ExportBody(module, "?_initialise@Entity@Ogre@@QAEX_N@Z");
        auto* deinit = ExportBody(module, "?_deinitialise@Entity@Ogre@@QAEXXZ");
        const std::uint8_t prologue[] = {0x55, 0x8B, 0xEC, 0x6A, 0xFF};
        const std::uint8_t deinitPrologue[] = {0x55, 0x8B, 0xEC, 0x83, 0xEC, 0x0C, 0x57,
            0x8B, 0xF9, 0x80, 0xBF, 0xC0, 0x01, 0x00, 0x00, 0x00};
        const std::uint8_t skeletonGetter[] = {0x8B, 0x81, 0xBC, 0x01, 0, 0, 0xC3};
        const std::uint8_t animationGetter[] = {0x8B, 0x81, 0xEC, 0, 0, 0, 0xC3};
        const std::uint8_t meshSkeletonGetter[] = {0x8D, 0x81, 0x4C, 0x01, 0, 0, 0xC3};
        const std::uint8_t masterGetter[] = {0x8B, 0x89, 0x38, 0x01, 0, 0, 0x8B, 0x01, 0xFF, 0x60, 0x58};
        const std::uint8_t numBonesGetter[] = {0x8B, 0x81, 0xDC, 0, 0, 0, 0x2B, 0x81, 0xD8, 0, 0, 0,
            0xC1, 0xF8, 0x02, 0xC3};
        auto* numBones = ExportBody(module, "?getNumBones@Skeleton@Ogre@@UBEGXZ");
        if (!Matches(body, prologue) || !Matches(deinit, deinitPrologue) ||
            !Matches(ExportBody(module, "?getSkeleton@Entity@Ogre@@QBEPAVSkeletonInstance@2@XZ"), skeletonGetter) ||
            !Matches(ExportBody(module, "?getAllAnimationStates@Entity@Ogre@@QBEPAVAnimationStateSet@2@XZ"), animationGetter) ||
            !Matches(ExportBody(module, "?getSkeleton@Mesh@Ogre@@QBEABV?$SharedPtr@VSkeleton@Ogre@@@2@XZ"), meshSkeletonGetter) ||
            !Matches(ExportBody(module, "?getName@SkeletonInstance@Ogre@@UBEABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ"), masterGetter) ||
            !Matches(numBones, numBonesGetter))
        {
            Log(L"[ENTITY-RELOAD] Live Ogre ABI/prologue signature mismatch; hook skipped\n");
            return;
        }

        g_skeletonDestructor = reinterpret_cast<Destructor>(GetProcAddress(module, "??1SkeletonInstance@Ogre@@UAE@XZ"));
        g_animationDestructor = reinterpret_cast<Destructor>(GetProcAddress(module, "??1AnimationStateSet@Ogre@@QAE@XZ"));
        g_deallocate = reinterpret_cast<Deallocate>(GetProcAddress(module, "??3?$AllocatedObject@V?$CategorisedAllocPolicy@$00@Ogre@@@Ogre@@SAXPAX@Z"));
        g_alignedDeallocate = reinterpret_cast<Deallocate>(GetProcAddress(module, "?deallocate@AlignedMemory@Ogre@@SAXPAX@Z"));
        g_numBones = reinterpret_cast<NumBones>(numBones);
        if (!g_skeletonDestructor || !g_animationDestructor || !g_deallocate || !g_alignedDeallocate)
        {
            Log(L"[ENTITY-RELOAD] Required Ogre ownership exports missing; hook skipped\n");
            return;
        }
        if (!InstallInlineDetour32(g_initialiseDetour, reinterpret_cast<std::uintptr_t>(body),
            reinterpret_cast<void*>(EntityInitialiseHook), sizeof(prologue), prologue, sizeof(prologue)))
        {
            Log(L"[ENTITY-RELOAD] Entity::_initialise detour failed; hook skipped\n");
            return;
        }
        g_initialise = reinterpret_cast<Initialise>(g_initialiseDetour.trampoline);
        Log(L"[ENTITY-RELOAD] Installed verified Entity::_initialise lifetime guard at %p\n", body);
    }
}
