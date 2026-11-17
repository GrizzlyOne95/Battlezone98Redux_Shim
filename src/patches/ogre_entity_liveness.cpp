// ogre_entity_liveness.cpp
// See include/ogre_entity_liveness.h. The bodies are gpu_skinning.cpp's,
// moved without behavioural change (commits a138b279e, 0edb0d5fe).
#include "ogre_entity_liveness.h"

#include "bzr_hooks_internal.h"
#include "live_object_gate.h"
#include "memory_access.h"

#include <Windows.h>

#include <cstring>
#include <string>

namespace BZROpenShim::OgreEntityLiveness
{
    namespace
    {
        using FnStringRef = const std::string* (__thiscall*)(void*);
        using FnHasEntity = bool(__thiscall*)(void*, const std::string&);
        using FnGetEntity = void* (__thiscall*)(void*, const std::string&);

        FnStringRef g_movableName = nullptr;
        FnHasEntity g_sceneHasEntity = nullptr;
        FnGetEntity g_sceneGetEntity = nullptr;
        bool g_resolved = false;

        bool IsPointerShaped(const void* candidate)
        {
            return LiveObjectGate::IsCandidatePointer(reinterpret_cast<uintptr_t>(candidate));
        }

        // The Entity's name, copied out without trusting the pointer: the
        // memory may be a freed Entity's. Reads only, bounded, under SEH.
        bool ReadEntityNameSeh(const void* entity, char* out, size_t outSize, size_t& length, bool& shaped)
        {
            length = 0;
            shaped = false;
            __try
            {
                const std::string* const name = g_movableName(const_cast<void*>(entity));
                if (!name)
                    return false;
                const size_t size = name->size();
                shaped = LiveObjectGate::IsEntityNameShaped(size, name->capacity()) && size < outSize;
                if (!shaped)
                    return true;
                std::memcpy(out, name->data(), size);
                out[size] = '\0';
                length = size;
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        // The queries only see the local copy of the name, never the Entity.
        bool QuerySceneOwnsCxx(void* sceneManager, const void* entity, const char* name, size_t length,
                               bool& hasEntity, bool& sameObject)
        {
            try
            {
                const std::string key(name, length);
                hasEntity = g_sceneHasEntity(sceneManager, key);
                sameObject = hasEntity && g_sceneGetEntity(sceneManager, key) == entity;
                return true;
            }
            catch (...)
            {
                return false;
            }
        }

        bool QuerySceneOwnsSeh(void* sceneManager, const void* entity, const char* name, size_t length,
                               bool& hasEntity, bool& sameObject)
        {
            __try
            {
                return QuerySceneOwnsCxx(sceneManager, entity, name, length, hasEntity, sameObject);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        bool ReadRootEntity(const void* root, void*& entity)
        {
            __try
            {
                entity = *reinterpret_cast<void* const*>(static_cast<const uint8_t*>(root) + 0x94);
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                entity = nullptr;
                return false;
            }
        }

        bool ReadVtable(const void* object, uintptr_t& vtable)
        {
            __try
            {
                vtable = *static_cast<const uintptr_t*>(object);
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                vtable = 0;
                return false;
            }
        }

        // The RTTI hops an Entity's walk takes: CompleteObjectLocator at
        // vtable[-1], TypeDescriptor at col+12. The caller has put the vtable
        // inside OgreMain, so the first read cannot leave the image.
        bool ReadRttiHops(uintptr_t vtable, uintptr_t& col, uintptr_t& descriptor)
        {
            __try
            {
                col = reinterpret_cast<const uintptr_t*>(vtable)[-1];
                descriptor = 0;
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                col = 0;
                return false;
            }
        }

        bool ReadDescriptor(uintptr_t col, uintptr_t& descriptor)
        {
            __try
            {
                descriptor = *reinterpret_cast<const uintptr_t*>(col + 12);
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                descriptor = 0;
                return false;
            }
        }

        constexpr const char* kEntityRtti = ".?AVEntity@Ogre@@";
    }

    bool Available()
    {
        if (!g_resolved)
        {
            g_resolved = true;
#define OS_STR "?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@"
            g_movableName = Hooks::ResolveOgreProc<FnStringRef>("?getName@MovableObject@Ogre@@UBEABV" OS_STR "XZ");
            g_sceneHasEntity = Hooks::ResolveOgreProc<FnHasEntity>("?hasEntity@SceneManager@Ogre@@UBE_NABV" OS_STR "@Z");
            g_sceneGetEntity = Hooks::ResolveOgreProc<FnGetEntity>(
                "?getEntity@SceneManager@Ogre@@UBEPAVEntity@2@ABV" OS_STR "@Z");
#undef OS_STR
        }
        return g_movableName && g_sceneHasEntity && g_sceneGetEntity;
    }

    bool EntityProvenLive(void* sceneManager, void* entity)
    {
        if (!Available())
            return false;
        LiveObjectGate::EntityProbe probe;
        char name[LiveObjectGate::kMaxEntityNameLength + 1];
        size_t length = 0;
        probe.nameRead = ReadEntityNameSeh(entity, name, sizeof(name), length, probe.nameShaped);
        if (probe.nameRead && probe.nameShaped)
            probe.queryOk = QuerySceneOwnsSeh(sceneManager, entity, name, length, probe.hasEntity, probe.sameObject);
        return LiveObjectGate::IsEntityProvenLive(probe);
    }

    // The same OBJ76 reads as Hooks::CaptureChunkBridgeSnapshot: the
    // direct bridge root at +0xF0, and the legacy owner (+0x8C)'s +0xF0.
    void ReadBridgeRoots(const uint8_t* obj76, void*& directRoot, void*& ownerRoot)
    {
        directRoot = nullptr;
        ownerRoot = nullptr;
        __try
        {
            void* const root = *reinterpret_cast<void* const*>(obj76 + 0xF0);
            if (IsPointerShaped(root))
                directRoot = root;
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
        }
        __try
        {
            void* const owner = *reinterpret_cast<void* const*>(obj76 + 0x8C);
            if (IsPointerShaped(owner))
            {
                void* const root = *reinterpret_cast<void* const*>(static_cast<const uint8_t*>(owner) + 0xF0);
                if (IsPointerShaped(root))
                    ownerRoot = root;
            }
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
        }
    }

    // Whether a pointer read out of engine memory is an Ogre::Entity, checked
    // so that junk raises no fault: the object's first word must be readable,
    // and its vtable, CompleteObjectLocator and TypeDescriptor must each lie
    // in OgreMain.dll (where an Entity's are), so every RTTI read stays
    // inside that image. The RTTI name test is the one the scan always used,
    // so the same Entities pass.
    bool IsOgreEntityObject(const void* entity)
    {
        if (!IsPointerShaped(entity) || !MemoryAccess::IsReadable(entity, sizeof(void*)))
            return false;
        uintptr_t vtable = 0;
        uintptr_t ogreBase = 0;
        uintptr_t ogreEnd = 0;
        if (!ReadVtable(entity, vtable) || !Hooks::TryGetOgreModuleRange(ogreBase, ogreEnd) ||
            !LiveObjectGate::IsVtableInModule(vtable, ogreBase, ogreEnd))
            return false;
        uintptr_t col = 0;
        uintptr_t descriptor = 0;
        if (!ReadRttiHops(vtable, col, descriptor) ||
            !LiveObjectGate::IsRttiHopInModule(col, 12u, ogreBase, ogreEnd) ||
            !ReadDescriptor(col, descriptor) ||
            !LiveObjectGate::IsRttiHopInModule(descriptor, 8u, ogreBase, ogreEnd))
            return false;
        char rtti[64];
        const char* className = Hooks::TryGetRttiClassName(entity, rtti, sizeof(rtti));
        return className && std::strcmp(className, kEntityRtti) == 0;
    }

    // The roots are candidate layout reads: on many object kinds OBJ76+0xF0
    // or the owner's +0xF0 holds a float or other data, which can land in
    // mapped memory for a while and then fault once that page goes. Only a
    // root proven to lead to an Entity is trusted frame to frame.
    void* RootEntityCache::Resolve(void* root, uint32_t frame, bool provePass)
    {
        if (!root)
            return nullptr;
        auto [it, inserted] = m_probes.try_emplace(root);
        RootProbe& probe = it->second;
        probe.seenFrame = frame;
        void* entity = nullptr;
        switch (LiveObjectGate::BridgeRootAction(probe.proven, inserted, provePass))
        {
        case LiveObjectGate::RootAction::Skip:
            return nullptr;
        case LiveObjectGate::RootAction::Prove:
            if (!MemoryAccess::IsReadable(root, 0xA8 + sizeof(void*)) || !ReadRootEntity(root, entity) ||
                !IsOgreEntityObject(entity))
                return nullptr;
            probe.proven = true;
            return entity;
        case LiveObjectGate::RootAction::Read:
            if (!ReadRootEntity(root, entity))
            {
                probe.proven = false;
                return nullptr;
            }
            // A proven root's +0x94 may since hold something else; the
            // caller checks it with IsOgreEntityObject before use.
            return IsPointerShaped(entity) ? entity : nullptr;
        }
        return nullptr;
    }

    void RootEntityCache::PruneUnseen(uint32_t frame)
    {
        for (auto it = m_probes.begin(); it != m_probes.end();)
            it = it->second.seenFrame == frame ? std::next(it) : m_probes.erase(it);
    }
}
