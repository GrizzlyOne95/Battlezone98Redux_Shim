// lua_handle_sync.cpp -- carry map-authored objects through Lua Send/Receive.
//
// ============================================================================
// THE DEFECT (Redux 2.2.301, exact GOG image)
// ============================================================================
//
// A Lua Handle crosses the network as one dword, the object's
// DistributedObject::dwLocalID:
//
//   pack   FUN_00505410  cdecl(buf**, limit, L, idx)
//     0x0050541E  call 0x4FF750              ; Lua value -> handle
//     0x0050542D  call 0x4DA060              ; GameObjectHandle::GetObj
//     0x00505463  mov ecx,[ebp-4] / add ecx,0x18   ; GameObject -> its
//                                            ; DistributedObject subobject
//     0x00505469  call 0x4B9A90              ; DistributedObject::GetLocalID
//                                            ;   mov eax,[ecx+0x64]
//     0x00505479  mov [edx],eax              ; written verbatim, 4 bytes
//
//   unpack FUN_00505490  cdecl(buf**, L)
//     0x005054C5  push eax                   ; the 4 bytes read from the wire
//     0x005054C6  call 0x4B9AB0              ; DistributedObject::GetGameObject
//                                            ;   local map, then remote map
//     0x005054CF  call 0x477590              ; object -> handle (0 for null)
//     0x005054E2  call 0x4FF770              ; push handle, or nil on 0
//
// dwLocalID is assigned only by DistributedObject::SetLocal
// (owner << 16 | counter). Objects the .bzn created and nobody networked
// (geysers, beacons, scenery) keep id 0, which GetGameObject cannot find, so
// the receiver pushes nil. Labels, by contrast, resolve identically on every
// peer. Observed live: Campaign Reimagined misn06's SetObjectiveOff(geyser)
// reached guests with args [].
//
// ============================================================================
// THE FIX
// ============================================================================
//
// Only these two call sites are rewritten, so GetID and every other consumer
// of GetLocalID/GetGameObject stay stock.
//
//   pack:   id from the stock accessor; when it is 0 and the object has a
//           label that is unambiguous among live objects, send the reserved
//           id 0x80000000 | fnv1a31(label). The payload stays four bytes, so
//           packet sizes and limits are unchanged.
//   unpack: stock lookup first (a real object always wins); when that finds
//           nothing and the id is reserved, find the one live object whose
//           label hashes to it. Anything unknown, ambiguous or colliding is
//           nil, exactly as today.
//
// A stock peer receiving a reserved id looks it up, finds nothing, and pushes
// nil -- the same outcome as the id 0 it received before -- so a mixed lobby
// is no worse off. Objects with a real id are byte-for-byte unchanged.
//
// Labels come from the engine's own GameObject::GetLabel (0x004623E0) and the
// live set from the engine's own object vector (the GetHandle(label) walk at
// 0x005C7E90), so no struct offset is hardcoded here beyond the 0x18 the pack
// pattern itself carries.
//
// Collisions: the index is rebuilt on use and flags any hash shared by two
// different labels, or by two objects with one label. Those are neither sent
// nor resolved (fail closed, logged).

#include "lua_handle_sync.h"
#include "lua_handle_sync_install.h"

#include "bool_token.h"
#include "hook_engine.h"
#include "shim_log.h"

#include <Windows.h>
#include <atomic>
#include <cstdint>
#include <cstring>

namespace BZROpenShim
{
    namespace LuaHandleSync
    {
        namespace
        {
            constexpr const char* kComponent = "LUAHANDLE";
            // `add ecx, 0x18` immediately before the pack site's call: the
            // GameObject -> DistributedObject subobject adjustment. It is part
            // of the "Lua::PackHandle id load call" signature, so a build that
            // changes it no longer resolves.
            constexpr uintptr_t kDistributedObjectOffset = 0x18;
            // Same bound the engine pool has (0x1000 slots).
            constexpr size_t kMaxObjects = 0x1000;
            // Pack-side index is reused briefly; the unpack side always
            // rebuilds because it hands back an object pointer.
            constexpr ULONGLONG kPackIndexMaxAgeMs = 100;
            constexpr long kLogBudget = 24;

            using FnGetLocalId = uint32_t(__fastcall*)(void* distributedObject, void* edx);
            using FnGetGameObject = void*(__cdecl*)(uint32_t id);
            using FnGetLabel = const char*(__fastcall*)(void* gameObject, void* edx);

            FnGetLocalId g_GetLocalId = nullptr;
            FnGetGameObject g_GetGameObject = nullptr;
            FnGetLabel g_GetLabel = nullptr;
            uintptr_t g_ObjectListGlobal = 0;

            std::atomic<bool> g_Installed{ false };
            std::atomic<bool> g_FailureLogged{ false };
            volatile long g_RemapLogBudget = kLogBudget;
            volatile long g_RefuseLogBudget = kLogBudget;
            volatile long g_ResolveLogBudget = kLogBudget;

            LabelIndex g_PackIndex;
            ULONGLONG g_PackIndexTick = 0;
            void* g_ObjectScratch[kMaxObjects];

            bool ReadShimBool(const char* name, bool defaultValue)
            {
                // openshim_env_config.h is force-included, so this reads
                // openshim.ini first and falls back to the real environment.
                char raw[64] = {};
                const DWORD len = GetEnvironmentVariableA(name, raw, sizeof(raw));
                if (len == 0 || len >= sizeof(raw))
                    return defaultValue;
                bool value = defaultValue;
                return BoolToken::TryParse(raw, len, value) ? value : defaultValue;
            }

            bool IsEnabled()
            {
                return ReadShimBool("OPENSHIM_LUA_MAPOBJECT_HANDLES", true);
            }

            // Snapshot of the engine's object vector (a std::vector<GameObject*>
            // reached through the global at objectList: _Myfirst at +0, _Mylast
            // at +4, exactly what 0x0041FBD0/0x0041FC30 return). Plain data only.
            size_t SnapshotObjects(void** out, size_t capacity)
            {
                if (!g_ObjectListGlobal)
                    return 0;
                size_t count = 0;
                __try
                {
                    const uint8_t* vec = *reinterpret_cast<uint8_t* const*>(g_ObjectListGlobal);
                    if (!vec)
                        return 0;
                    void* const* first = *reinterpret_cast<void* const* const*>(vec);
                    void* const* last = *reinterpret_cast<void* const* const*>(vec + 4);
                    if (!first || last < first)
                        return 0;
                    const size_t available = static_cast<size_t>(last - first);
                    if (available > kMaxObjects)
                        return 0; // not the vector we think it is
                    for (size_t i = 0; i < available && count < capacity; ++i)
                    {
                        if (first[i])
                            out[count++] = first[i];
                    }
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    return 0;
                }
                return count;
            }

            // Copies the object's label into `buffer`. False when it has none,
            // is too long, or cannot be read.
            bool ReadLabel(void* object, char (&buffer)[kMaxLabelLength + 1])
            {
                buffer[0] = '\0';
                if (!object || !g_GetLabel)
                    return false;
                __try
                {
                    const char* label = g_GetLabel(object, nullptr);
                    if (!label)
                        return false;
                    size_t length = 0;
                    while (label[length])
                    {
                        if (length >= kMaxLabelLength)
                        {
                            buffer[0] = '\0';
                            return false;
                        }
                        buffer[length] = label[length];
                        ++length;
                    }
                    buffer[length] = '\0';
                    return length != 0;
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    buffer[0] = '\0';
                    return false;
                }
            }

            void RebuildIndex(LabelIndex& index)
            {
                index.Clear();
                const size_t count = SnapshotObjects(g_ObjectScratch, kMaxObjects);
                char label[kMaxLabelLength + 1];
                for (size_t i = 0; i < count; ++i)
                {
                    if (ReadLabel(g_ObjectScratch[i], label))
                        index.Add(label, reinterpret_cast<uintptr_t>(g_ObjectScratch[i]));
                }
            }

            const char* StatusName(LabelIndex::Status status)
            {
                switch (status)
                {
                case LabelIndex::Status::Unique: return "unique";
                case LabelIndex::Status::Ambiguous: return "ambiguous";
                case LabelIndex::Status::Collision: return "hash-collision";
                default: return "unknown";
                }
            }

            // Replaces `call 0x4B9A90` in the pack routine. thiscall: ECX is
            // the DistributedObject subobject, EAX the id.
            uint32_t __fastcall PackIdHook(void* distributedObject, void* edx)
            {
                const uint32_t id = g_GetLocalId(distributedObject, edx);
                if (id != 0 || !distributedObject)
                    return id;

                void* const gameObject = reinterpret_cast<uint8_t*>(distributedObject) - kDistributedObjectOffset;
                char label[kMaxLabelLength + 1];
                if (!ReadLabel(gameObject, label))
                    return 0; // unlabelled: unchanged (nil on the receiver)

                const ULONGLONG now = GetTickCount64();
                LabelIndex::Result result = g_PackIndex.LookupLabel(label);
                const bool fresh = g_PackIndexTick != 0 && now - g_PackIndexTick <= kPackIndexMaxAgeMs;
                if (!fresh || result.status != LabelIndex::Status::Unique ||
                    result.tag != reinterpret_cast<uintptr_t>(gameObject))
                {
                    RebuildIndex(g_PackIndex);
                    g_PackIndexTick = now;
                    result = g_PackIndex.LookupLabel(label);
                }

                if (result.status != LabelIndex::Status::Unique ||
                    result.tag != reinterpret_cast<uintptr_t>(gameObject))
                {
                    if (InterlockedDecrement(&g_RefuseLogBudget) >= 0)
                        LogShimA(LogLevel::Warn, kComponent,
                                 "not sending label \"%s\" (%s); receivers will see nil as before",
                                 label, StatusName(result.status));
                    return 0;
                }

                const uint32_t reserved = MakeReservedId(label);
                if (InterlockedDecrement(&g_RemapLogBudget) >= 0)
                    LogShimA(LogLevel::Info, kComponent,
                             "sending map object \"%s\" as reserved id 0x%08X", label, reserved);
                return reserved;
            }

            // Replaces `call 0x4B9AB0` in the unpack routine. cdecl(id) ->
            // GameObject* (or null); the caller pops the argument.
            void* __cdecl UnpackLookupHook(uint32_t id)
            {
                void* const stock = g_GetGameObject(id);
                if (stock || !IsReservedId(id))
                    return stock;

                LabelIndex index;
                RebuildIndex(index);
                const LabelIndex::Result result = index.Lookup(id);
                if (result.status == LabelIndex::Status::Unique)
                {
                    if (InterlockedDecrement(&g_ResolveLogBudget) >= 0)
                        LogShimA(LogLevel::Info, kComponent,
                                 "reserved id 0x%08X -> map object \"%s\"", id, result.label.c_str());
                    return reinterpret_cast<void*>(result.tag);
                }

                if (InterlockedDecrement(&g_ResolveLogBudget) >= 0)
                    LogShimA(LogLevel::Warn, kComponent,
                             "reserved id 0x%08X did not resolve (%s, %u labelled objects); nil",
                             id, StatusName(result.status), static_cast<unsigned>(index.Size()));
                return nullptr;
            }

            bool PatchCallSite(uint32_t site, void* replacement, const uint8_t (&original)[5])
            {
                HookEngine::PatchDef def;
                def.address = site;
                def.type = HookEngine::PatchType::REL32;
                def.name = "LuaHandleSync::CallSite";
                def.verified = true;
                def.expected_original.assign(original, original + sizeof(original));

                const int32_t rel =
                    static_cast<int32_t>(reinterpret_cast<uintptr_t>(replacement)) -
                    static_cast<int32_t>(site + 5);
                def.payload.assign(5, 0);
                def.payload[0] = 0xE8;
                std::memcpy(def.payload.data() + 1, &rel, sizeof(rel));
                return HookEngine::ApplyPatch(def);
            }

            void FailOnce(const char* message)
            {
                if (!g_FailureLogged.exchange(true))
                    LogShimA(LogLevel::Warn, kComponent, "%s; Lua handle label remap not installed", message);
            }
        }

        void InstallLuaHandleSyncIfPossible()
        {
            if (g_Installed.load())
                return;

            if (!IsEnabled())
            {
                if (!g_FailureLogged.exchange(true))
                    LogShimA(LogLevel::Info, kComponent, "disabled ([Network] LuaMapObjectHandles = 0)");
                return;
            }

            const uint32_t packSite = HookEngine::ResolveNamedAddress("Lua::PackHandle id load call");
            const uint32_t unpackSite = HookEngine::ResolveNamedAddress("Lua::UnpackHandle object lookup call");
            const uint32_t getLocalId = HookEngine::ResolveNamedAddress("DistributedObject::GetLocalID");
            const uint32_t getGameObject = HookEngine::ResolveNamedAddress("DistributedObject::GetGameObject");
            const uint32_t getLabel = HookEngine::ResolveNamedAddress("GameObject::GetLabel");
            const uint32_t objectList = HookEngine::ResolveNamedAddress("GameObject::objectList");
            if (!packSite || !unpackSite || !getLocalId || !getGameObject || !getLabel || !objectList)
            {
                FailOnce("a required resolve is missing");
                return;
            }

            // Signature uniqueness is not identity: each call site must reach
            // the accessor it was written against.
            if (HookEngine::ResolveRelCallTarget(packSite) != reinterpret_cast<void*>(static_cast<uintptr_t>(getLocalId)) ||
                HookEngine::ResolveRelCallTarget(unpackSite) != reinterpret_cast<void*>(static_cast<uintptr_t>(getGameObject)))
            {
                FailOnce("a call site does not reach the expected DistributedObject accessor");
                return;
            }

            uint8_t packOriginal[5] = {};
            uint8_t unpackOriginal[5] = {};
            if (!HookEngine::ReadMemory(packSite, packOriginal, sizeof(packOriginal)) ||
                !HookEngine::ReadMemory(unpackSite, unpackOriginal, sizeof(unpackOriginal)) ||
                packOriginal[0] != 0xE8 || unpackOriginal[0] != 0xE8)
            {
                FailOnce("a call site is not a rel32 call");
                return;
            }

            g_GetLocalId = reinterpret_cast<FnGetLocalId>(static_cast<uintptr_t>(getLocalId));
            g_GetGameObject = reinterpret_cast<FnGetGameObject>(static_cast<uintptr_t>(getGameObject));
            g_GetLabel = reinterpret_cast<FnGetLabel>(static_cast<uintptr_t>(getLabel));
            g_ObjectListGlobal = objectList;

            if (!PatchCallSite(packSite, reinterpret_cast<void*>(&PackIdHook), packOriginal))
            {
                FailOnce("the pack call site could not be rewritten");
                return;
            }
            if (!PatchCallSite(unpackSite, reinterpret_cast<void*>(&UnpackLookupHook), unpackOriginal))
            {
                // Put the pack site back so neither half is live.
                const bool restored = HookEngine::WriteMemory(packSite, packOriginal, sizeof(packOriginal));
                FailOnce(restored ? "the unpack call site could not be rewritten (pack site restored)"
                                  : "the unpack call site could not be rewritten (pack site restore FAILED; hook still delegates)");
                return;
            }

            g_Installed.store(true);
            LogShimA(LogLevel::Info, kComponent,
                     "installed: pack=0x%08X unpack=0x%08X getLocalId=0x%08X getGameObject=0x%08X getLabel=0x%08X objectList=0x%08X",
                     packSite, unpackSite, getLocalId, getGameObject, getLabel, objectList);
        }
    }
}
