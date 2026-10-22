// gpu_instancing.cpp
// BZR Open Shim - experimental hardware instancing for GPU-skinned craft (DX11).
//
// Ogre renders every craft sub-entity as its own draw. With GpuSkinning on,
// sub-entities of the same mesh share vertex/index data and a skinned clone
// pass whose vertex program no longer reads per-object constants, so they
// differ only in their bone palettes. gpu_skinning.cpp builds an instanced
// twin of each such pass: a palette four times wider, offset per instance by
// a float read from a per-instance TEXCOORD15 stream. This file batches at
// draw time:
//
//  - SceneMgrQueuedRenderableVisitor::visit(Renderable*) defers sub-entities
//    whose pass has a twin; visit(Pass*), visit(RenderablePass*) and the exit
//    of QueuedRenderableCollection::acceptVisitor flush them, so a batch
//    never spans a pass change;
//  - a flush groups members by mesh data, palette size, lights, shadow role
//    and handedness, draws singletons through the stock path with the
//    source pass still bound, then binds the twin once and draws each group
//    as one instanced draw through the stock renderSingleObject, with the
//    leader's vtable swapped so its render operation carries an instance
//    count, a cloned declaration with the instance element and a binding
//    with the instance stream, and its world transforms are the
//    concatenated palettes of the whole group.
//
// The leader is rendered by Ogre's own code, so lights, scissoring, culling,
// shadow caster derivation and auto constants follow the stock path. Nothing
// here depends on game addresses; every hook is in OgreMain and is checked
// against its export before it is patched. Any fault latches the feature
// off for the process and the members of the failed flush render singly.
#include "gpu_instancing.h"

#include "bzr_hooks_internal.h"
#include "bzr_options_ui.h"
#include "gpu_skinning.h"
#include "shim_log.h"

#include <Windows.h>

#include <algorithm>
#include <atomic>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <string>
#include <unordered_map>
#include <vector>

namespace BZROpenShim
{
    namespace
    {
        using Hooks::ResolveOgreProc;

        constexpr const char* kComponent = "gpu-instancing";
        // Palette capacity of every instanced twin (gpu_skinning.cpp's
        // kInstancedMaxBones); also the size of Ogre's world matrix arrays.
        constexpr uint32_t kPaletteBones = 256;
        // SubEntity has about thirty virtual slots in Ogre 1.10.
        constexpr size_t kVtableCopySlots = 64;
        // D3D11 input slots.
        constexpr uint16_t kMaxVertexSource = 15;

        // Ogre enums (1.10).
        // A dynamic buffer: a static one filled through lock() kept reading
        // zero in the shader on this build (see the design doc).
        constexpr int kHbuDynamicWriteOnly = 6;
        constexpr int kHblDiscard = 1;
        constexpr int kVetFloat1 = 0;
        constexpr int kVesTextureCoordinates = 7;
        // Matches gpu_skinning_hlsl.h's kInstanceBaseSemantic.
        constexpr uint16_t kInstanceTexcoord = 15;

        // Ogre::VertexElement (no vptr).
        struct VertexElement
        {
            uint16_t source;
            size_t offset;
            int type;
            int semantic;
            uint16_t index;
        };
        static_assert(sizeof(VertexElement) == 20, "VertexElement layout");

        struct SharedPtr
        {
            void* rep = nullptr;
            void* info = nullptr;
        };

        // Ogre::RenderOperation (28 bytes on x86).
        struct RenderOperation
        {
            void* vertexData;
            int operationType;
            bool useIndexes;
            void* indexData;
            const void* srcRenderable;
            size_t numberOfInstances;
            bool renderToVertexBuffer;
            bool useGlobalInstancingVertexBufferIsAvailable;
        };
        static_assert(sizeof(RenderOperation) == 28, "RenderOperation layout");
        static_assert(offsetof(RenderOperation, numberOfInstances) == 20, "RenderOperation layout");

        // Ogre::VertexData: mMgr, vertexDeclaration, vertexBufferBinding,
        // mDeleteDclBinding, vertexStart, vertexCount, animation data. No vptr.
        constexpr size_t kVertexDataSize = 48;
        constexpr size_t kVertexDataDecl = 4;
        constexpr size_t kVertexDataBinding = 8;

        struct Matrix4
        {
            float m[4][4];
        };

        // Ogre::HashedVector<Light*>: its std::vector comes first.
        struct LightList
        {
            void* const* first;
            void* const* last;
        };

        // SceneManager::SceneMgrQueuedRenderableVisitor members after the vptr.
        struct Visitor
        {
            void* vptr;
            const void* usedPass;
            void* sceneManager;
        };

        using FnVisitRenderable = void(__thiscall*)(void*, void*);
        using FnVisitPass = bool(__thiscall*)(void*, const void*);
        using FnVisitRenderablePass = void(__thiscall*)(void*, void*);
        using FnAcceptVisitor = void(__thiscall*)(const void*, void*, int);
        using FnSetPass = const void* (__thiscall*)(void*, const void*, bool, bool);
        using FnSceneBool = bool(__thiscall*)(const void*);
        using FnGetRenderOperation = void(__thiscall*)(void*, RenderOperation&);
        using FnGetWorldTransforms = void(__thiscall*)(const void*, Matrix4*);
        using FnGetNumWorldTransforms = uint16_t(__thiscall*)(const void*);
        using FnGetLights = const LightList* (__thiscall*)(const void*);
        using FnSingleton = void* (__cdecl*)();
        using FnCreateVertexBuffer = SharedPtr* (__thiscall*)(void*, SharedPtr*, size_t, size_t, int, bool);
        using FnCreateBinding = void* (__thiscall*)(void*);
        using FnDestroyObject = void(__thiscall*)(void*, void*);
        using FnU16 = uint16_t(__thiscall*)(const void*);
        using FnSetBinding = void(__thiscall*)(void*, uint16_t, const SharedPtr&);
        using FnVoid = void(__thiscall*)(void*);
        using FnIsBound = bool(__thiscall*)(const void*, uint16_t);
        using FnGetBuffer = const SharedPtr* (__thiscall*)(const void*, uint16_t);
        using FnSetBool = void(__thiscall*)(void*, bool);
        using FnSetSize = void(__thiscall*)(void*, size_t);
        using FnCloneDecl = void* (__thiscall*)(const void*, void*);
        using FnElementCount = size_t(__thiscall*)(const void*);
        using FnGetElement = const VertexElement* (__thiscall*)(const void*, uint16_t);
        using FnAddElement = const void* (__thiscall*)(void*, uint16_t, size_t, int, int, uint16_t);
        using FnLock = void* (__thiscall*)(void*, int, int);

        struct OgreApi
        {
            void** visitorVtable = nullptr;
            FnVisitRenderable visitRenderable = nullptr;
            FnVisitPass visitPass = nullptr;
            FnVisitRenderablePass visitRenderablePass = nullptr;
            uintptr_t acceptVisitor = 0;
            FnSetPass setPass = nullptr;
            FnSceneBool stateChangesSuppressed = nullptr;
            void** subEntityVtable = nullptr;
            FnGetRenderOperation getRenderOperation = nullptr;
            FnGetWorldTransforms getWorldTransforms = nullptr;
            FnGetNumWorldTransforms getNumWorldTransforms = nullptr;
            FnGetLights getLights = nullptr;
            FnSceneBool getCastsShadows = nullptr;
            FnSingleton bufferManager = nullptr;
            FnCreateVertexBuffer createVertexBuffer = nullptr;
            FnCreateBinding createBinding = nullptr;
            FnU16 maxSource = nullptr;
            FnSetBinding setBinding = nullptr;
            FnVoid unsetAllBindings = nullptr;
            FnIsBound isBufferBound = nullptr;
            FnGetBuffer getBuffer = nullptr;
            FnU16 lastBoundIndex = nullptr;
            FnSetBool setIsInstanceData = nullptr;
            FnSetSize setInstanceDataStepRate = nullptr;
            FnDestroyObject destroyDeclaration = nullptr;
            FnCloneDecl cloneDeclaration = nullptr;
            FnElementCount elementCount = nullptr;
            FnGetElement getElement = nullptr;
            FnLock lock = nullptr;
            FnVoid unlock = nullptr;
            void** hardwareBufferVtable = nullptr;
        };

        OgreApi g_ogre;
        int g_slotGetRenderOperation = -1;
        int g_slotGetWorldTransforms = -1;
        int g_slotGetNumWorldTransforms = -1;
        // D3D11HardwareVertexBuffer overrides unlock to forward to its inner
        // buffer; the exported HardwareBuffer::unlock called directly never
        // unmaps it, and the GPU copy stays zero. So unlock goes through here.
        int g_slotUnlock = -1;
        // The leader's vtable during an instanced draw: SubEntity's with three
        // overrides. Slot -1 keeps the RTTI locator.
        void* g_leaderVtableStorage[kVtableCopySlots + 1] = {};
        void** const g_leaderVtable = g_leaderVtableStorage + 1;

        InlineDetour32 g_acceptDetour;
        void* volatile g_acceptTrampoline = nullptr;

        bool g_installAttempted = false;
        bool g_installed = false;
        std::atomic<bool> g_failed{ false };
        int g_depth = 0;
        uint32_t g_generation = 0;

        struct Stats
        {
            uint32_t deferred = 0;
            uint32_t batches = 0;
            uint32_t batchedMembers = 0;
            uint32_t singles = 0;
            uint32_t ineligible = 0;
            uint32_t declRefused = 0;
            uint32_t renderOpMismatch = 0;
            uint32_t maxBatch = 0;
        };
        Stats g_stats;

        // Members deferred for the pass bound by the last visit(Pass*).
        struct Pending
        {
            void* visitor = nullptr;
            const void* sourcePass = nullptr;
            void* twin = nullptr;
            GpuSkinningTwinLights lights;
            std::vector<void*> members;
        };
        Pending g_pending;

        struct Member
        {
            void* renderable;
            RenderOperation op;
            const LightList* lights;
            uint32_t firstMatrix;
            uint16_t bones;
            bool castsShadows;
            bool negativeScale;
            bool eligible;
            bool drawn;
        };
        std::vector<Member> g_members;
        std::vector<Matrix4> g_matrices;
        std::vector<uint32_t> g_groupOf;

        // The instanced draw in flight, read by the leader's overrides.
        struct Draw
        {
            void* leader = nullptr;
            void* leaderVptr = nullptr;
            const void* expectedVertexData = nullptr;
            uint8_t vertexData[kVertexDataSize] = {};
            uint32_t instances = 0;
            uint16_t bones = 0;
            bool mismatch = false;
            Matrix4 palette[kPaletteBones];
        };
        // Ogre reads the copied VertexData as words.
        static_assert(offsetof(Draw, vertexData) % sizeof(void*) == 0, "VertexData copy alignment");
        Draw g_draw;

        // Per-flush state the fault path needs.
        Visitor* g_flushVisitor = nullptr;
        const void* g_flushUsedPass = nullptr;
        bool g_twinBound = false;

        // Cloned declarations keyed by source declaration and instance slot;
        // the snapshot catches a freed address reused by another declaration.
        struct DeclEntry
        {
            std::vector<VertexElement> snapshot;
            void* declaration = nullptr;
            bool refused = false;
        };
        std::unordered_map<uint64_t, DeclEntry> g_declarations;
        // Instance base streams keyed by palette size.
        std::unordered_map<uint16_t, SharedPtr> g_instanceBuffers;
        void* g_binding = nullptr;

        uint8_t* ResolveExportBody(void* proc)
        {
            auto* body = static_cast<uint8_t*>(proc);
            if (body && body[0] == 0xE9)   // incremental-link thunk
            {
                int32_t rel = 0;
                std::memcpy(&rel, body + 1, sizeof(rel));
                body = body + 5 + rel;
            }
            return body;
        }

        // Compares addresses only: a scan can run past the vtable's end into
        // data, so a slot is never dereferenced.
        bool SameFunction(void* slot, void* proc)
        {
            return slot && proc && (slot == proc || slot == ResolveExportBody(proc));
        }

        bool Readable(const void* address, size_t bytes)
        {
            MEMORY_BASIC_INFORMATION info = {};
            if (!VirtualQuery(address, &info, sizeof(info)) || info.State != MEM_COMMIT)
                return false;
            if (info.Protect & (PAGE_GUARD | PAGE_NOACCESS))
                return false;
            const auto end = reinterpret_cast<uintptr_t>(info.BaseAddress) + info.RegionSize;
            return reinterpret_cast<uintptr_t>(address) + bytes <= end;
        }

        int FindSlot(void** vtable, void* proc)
        {
            int found = -1;
            for (size_t i = 0; i < kVtableCopySlots; ++i)
            {
                if (!SameFunction(vtable[i], proc))
                    continue;
                if (found >= 0)
                    return -1;
                found = static_cast<int>(i);
            }
            return found;
        }

        template <typename T>
        bool Bind(T& out, const char* name)
        {
            out = ResolveOgreProc<T>(name);
            return out != nullptr;
        }

        bool ResolveApi(const char*& missing)
        {
            OgreApi& o = g_ogre;
#define OS_BIND(field, name) if (!Bind(o.field, name)) { missing = name; return false; }
            OS_BIND(visitorVtable, "??_7SceneMgrQueuedRenderableVisitor@SceneManager@Ogre@@6B@");
            OS_BIND(visitRenderable, "?visit@SceneMgrQueuedRenderableVisitor@SceneManager@Ogre@@UAEXPAVRenderable@3@@Z");
            OS_BIND(visitPass, "?visit@SceneMgrQueuedRenderableVisitor@SceneManager@Ogre@@UAE_NPBVPass@3@@Z");
            OS_BIND(visitRenderablePass, "?visit@SceneMgrQueuedRenderableVisitor@SceneManager@Ogre@@UAEXPAURenderablePass@3@@Z");
            void* accept = nullptr;
            OS_BIND(setPass, "?_setPass@SceneManager@Ogre@@UAEPBVPass@2@PBV32@_N1@Z");
            OS_BIND(stateChangesSuppressed, "?_areRenderStateChangesSuppressed@SceneManager@Ogre@@UBE_NXZ");
            OS_BIND(subEntityVtable, "??_7SubEntity@Ogre@@6B@");
            OS_BIND(getRenderOperation, "?getRenderOperation@SubEntity@Ogre@@UAEXAAVRenderOperation@2@@Z");
            OS_BIND(getWorldTransforms, "?getWorldTransforms@SubEntity@Ogre@@UBEXPAVMatrix4@2@@Z");
            OS_BIND(getNumWorldTransforms, "?getNumWorldTransforms@SubEntity@Ogre@@UBEGXZ");
            OS_BIND(getLights, "?getLights@SubEntity@Ogre@@UBEABV?$HashedVector@PAVLight@Ogre@@@2@XZ");
            OS_BIND(getCastsShadows, "?getCastsShadows@SubEntity@Ogre@@UBE_NXZ");
            OS_BIND(bufferManager, "?getSingletonPtr@HardwareBufferManager@Ogre@@SAPAV12@XZ");
            OS_BIND(createVertexBuffer, "?createVertexBuffer@HardwareBufferManager@Ogre@@UAE?AVHardwareVertexBufferSharedPtr@2@IIW4Usage@HardwareBuffer@2@_N@Z");
            OS_BIND(createBinding, "?createVertexBufferBinding@HardwareBufferManager@Ogre@@UAEPAVVertexBufferBinding@2@XZ");
            OS_BIND(maxSource, "?getMaxSource@VertexDeclaration@Ogre@@QBEGXZ");
            OS_BIND(setBinding, "?setBinding@VertexBufferBinding@Ogre@@UAEXGABVHardwareVertexBufferSharedPtr@2@@Z");
            OS_BIND(unsetAllBindings, "?unsetAllBindings@VertexBufferBinding@Ogre@@UAEXXZ");
            OS_BIND(isBufferBound, "?isBufferBound@VertexBufferBinding@Ogre@@UBE_NG@Z");
            OS_BIND(getBuffer, "?getBuffer@VertexBufferBinding@Ogre@@UBEABVHardwareVertexBufferSharedPtr@2@G@Z");
            OS_BIND(lastBoundIndex, "?getLastBoundIndex@VertexBufferBinding@Ogre@@UBEGXZ");
            OS_BIND(setIsInstanceData, "?setIsInstanceData@HardwareVertexBuffer@Ogre@@QAEX_N@Z");
            OS_BIND(setInstanceDataStepRate, "?setInstanceDataStepRate@HardwareVertexBuffer@Ogre@@QAEXI@Z");
            OS_BIND(destroyDeclaration, "?destroyVertexDeclaration@HardwareBufferManager@Ogre@@UAEXPAVVertexDeclaration@2@@Z");
            OS_BIND(cloneDeclaration, "?clone@VertexDeclaration@Ogre@@UBEPAV12@PAVHardwareBufferManagerBase@2@@Z");
            OS_BIND(elementCount, "?getElementCount@VertexDeclaration@Ogre@@QBEIXZ");
            OS_BIND(getElement, "?getElement@VertexDeclaration@Ogre@@QBEPBVVertexElement@2@G@Z");
            OS_BIND(lock, "?lock@HardwareBuffer@Ogre@@QAEPAXW4LockOptions@12@W4UploadOptions@12@@Z");
            OS_BIND(unlock, "?unlock@HardwareBuffer@Ogre@@UAEXXZ");
            OS_BIND(hardwareBufferVtable, "??_7HardwareBuffer@Ogre@@6B@");
            if (!Bind(accept, "?acceptVisitor@QueuedRenderableCollection@Ogre@@QBEXPAVQueuedRenderableVisitor@2@W4OrganisationMode@12@@Z"))
            {
                missing = "QueuedRenderableCollection::acceptVisitor";
                return false;
            }
#undef OS_BIND
            o.acceptVisitor = reinterpret_cast<uintptr_t>(ResolveExportBody(accept));
            return true;
        }

        void Disable(const char* why)
        {
            if (g_failed.exchange(true))
                return;
            LogShimA(LogLevel::Error, kComponent,
                "[GPUINST] disabled for this session: %s (batches=%u members=%u)",
                why, g_stats.batches, g_stats.batchedMembers);
        }

        bool Enabled()
        {
            return g_installed && !g_failed.load(std::memory_order_acquire) && GpuSkinningInstancingActive();
        }

        // --- leader overrides -------------------------------------------------

        void __fastcall LeaderGetRenderOperation(void* self, void*, RenderOperation* op)
        {
            g_ogre.getRenderOperation(self, *op);
            if (self == g_draw.leader && op->numberOfInstances == 1 && op->vertexData == g_draw.expectedVertexData)
            {
                op->vertexData = g_draw.vertexData;
                op->numberOfInstances = g_draw.instances;
                return;
            }
            // Draws nothing (D3D11 _render returns on null vertex data); the
            // members render singly afterwards.
            op->vertexData = nullptr;
            g_draw.mismatch = true;
        }

        void __fastcall LeaderGetWorldTransforms(const void*, void*, Matrix4* out)
        {
            std::memcpy(out, g_draw.palette, sizeof(Matrix4) * g_draw.instances * g_draw.bones);
        }

        uint16_t __fastcall LeaderGetNumWorldTransforms(const void*, void*)
        {
            return static_cast<uint16_t>(g_draw.instances * g_draw.bones);
        }

        // --- vertex streams ----------------------------------------------------

        bool NegativeScale(const Matrix4& m)
        {
            const float det =
                m.m[0][0] * (m.m[1][1] * m.m[2][2] - m.m[1][2] * m.m[2][1]) -
                m.m[0][1] * (m.m[1][0] * m.m[2][2] - m.m[1][2] * m.m[2][0]) +
                m.m[0][2] * (m.m[1][0] * m.m[2][1] - m.m[1][1] * m.m[2][0]);
            return det < 0.0f;
        }

        // Equal as far as the twin pass's programs read the lists: the first
        // `use.depth` entries, and the lengths when `use.count`. Beyond that
        // Ogre pads with blank lights, so a shorter list must match there too.
        bool SameLights(const LightList* a, const LightList* b, const GpuSkinningTwinLights& use)
        {
            if (a == b)
                return true;
            const size_t countA = a ? static_cast<size_t>(a->last - a->first) : 0;
            const size_t countB = b ? static_cast<size_t>(b->last - b->first) : 0;
            if (use.count && countA != countB)
                return false;
            const size_t depth = (std::min)(static_cast<size_t>(use.depth), (std::max)(countA, countB));
            if (countA < depth || countB < depth)
                return false;
            return depth == 0 || std::memcmp(a->first, b->first, depth * sizeof(void*)) == 0;
        }

        // Instance n reads n * bones: the first palette bone of its palette.
        const SharedPtr* InstanceBuffer(uint16_t bones)
        {
            auto found = g_instanceBuffers.find(bones);
            if (found != g_instanceBuffers.end())
                return &found->second;
            void* manager = g_ogre.bufferManager();
            if (!manager)
                return nullptr;
            SharedPtr buffer;
            g_ogre.createVertexBuffer(manager, &buffer, sizeof(float), kPaletteBones, kHbuDynamicWriteOnly, false);
            if (!buffer.rep)
                return nullptr;
            g_ogre.setIsInstanceData(buffer.rep, true);
            g_ogre.setInstanceDataStepRate(buffer.rep, 1);
            auto* bases = static_cast<float*>(g_ogre.lock(buffer.rep, kHblDiscard, 0));
            if (!bases)
                return nullptr;
            for (uint32_t i = 0; i < kPaletteBones; ++i)
                bases[i] = static_cast<float>(i * bones);
            auto unlock = reinterpret_cast<FnVoid>((*static_cast<void***>(buffer.rep))[g_slotUnlock]);
            unlock(buffer.rep);
            // Kept for the process: a kilobyte per palette size.
            return &g_instanceBuffers.emplace(bones, buffer).first->second;
        }

        bool SnapshotMatches(const void* declaration, const std::vector<VertexElement>& snapshot)
        {
            const size_t count = g_ogre.elementCount(declaration);
            if (count != snapshot.size())
                return false;
            for (size_t i = 0; i < count; ++i)
            {
                const VertexElement* e = g_ogre.getElement(declaration, static_cast<uint16_t>(i));
                const VertexElement& s = snapshot[i];
                if (!e || e->source != s.source || e->offset != s.offset || e->type != s.type ||
                    e->semantic != s.semantic || e->index != s.index)
                    return false;
            }
            return true;
        }

        // The source declaration plus one per-instance float at TEXCOORD15.
        // Ogre's D3D11 input layout must find every shader input among the
        // declaration's elements, so the instance index cannot be
        // SV_InstanceID.
        void* InstancedDeclaration(const void* source, uint16_t instanceSource)
        {
            const uint64_t key = (static_cast<uint64_t>(reinterpret_cast<uintptr_t>(source)) << 16) | instanceSource;
            DeclEntry& entry = g_declarations[key];
            if (!entry.snapshot.empty() || entry.refused)
            {
                if (SnapshotMatches(source, entry.snapshot))
                    return entry.refused ? nullptr : entry.declaration;
                // The address now holds another declaration.
                if (entry.declaration)
                    g_ogre.destroyDeclaration(g_ogre.bufferManager(), entry.declaration);
                entry = DeclEntry{};
            }

            const size_t count = g_ogre.elementCount(source);
            for (size_t i = 0; i < count; ++i)
            {
                const VertexElement* e = g_ogre.getElement(source, static_cast<uint16_t>(i));
                if (!e)
                {
                    entry.refused = true;
                    return nullptr;
                }
                entry.snapshot.push_back(*e);
                if (e->semantic == kVesTextureCoordinates && e->index == kInstanceTexcoord)
                    entry.refused = true;
            }
            if (entry.refused || instanceSource > kMaxVertexSource)
            {
                entry.refused = true;
                ++g_stats.declRefused;
                return nullptr;
            }

            void* declaration = g_ogre.cloneDeclaration(source, nullptr);
            if (!declaration)
            {
                entry.refused = true;
                return nullptr;
            }
            // addElement is virtual (slot 1, after the destructor) so the
            // D3D11 declaration marks its input layouts for rebuild.
            auto addElement = reinterpret_cast<FnAddElement>((*static_cast<void***>(declaration))[1]);
            addElement(declaration, instanceSource, 0, kVetFloat1, kVesTextureCoordinates, kInstanceTexcoord);
            entry.declaration = declaration;
            return declaration;
        }

        void ReleaseDeclarations()
        {
            void* manager = g_ogre.bufferManager ? g_ogre.bufferManager() : nullptr;
            for (auto& entry : g_declarations)
            {
                if (entry.second.declaration && manager)
                    g_ogre.destroyDeclaration(manager, entry.second.declaration);
            }
            g_declarations.clear();
        }

        // --- flush -------------------------------------------------------------

        void DrawSingle(Visitor* visitor, Member& member)
        {
            member.drawn = true;
            ++g_stats.singles;
            g_ogre.visitRenderable(visitor, member.renderable);
        }

        void BindSource(Visitor* visitor, const void* sourcePass)
        {
            visitor->usedPass = g_ogre.setPass(visitor->sceneManager, sourcePass, false, true);
            g_twinBound = false;
        }

        // Draws members [first, first + count) of a group as one instanced draw.
        void DrawChunk(Visitor* visitor, const uint32_t* indices, uint32_t count)
        {
            Member& leader = g_members[indices[0]];
            const uint8_t* sourceData = static_cast<const uint8_t*>(leader.op.vertexData);
            const void* sourceDecl = *reinterpret_cast<void* const*>(sourceData + kVertexDataDecl);
            const void* sourceBinding = *reinterpret_cast<void* const*>(sourceData + kVertexDataBinding);

            const uint16_t lastBound = g_ogre.lastBoundIndex(sourceBinding);
            const uint16_t declSources = static_cast<uint16_t>(g_ogre.maxSource(sourceDecl) + 1);
            const uint16_t instanceSource = lastBound > declSources ? lastBound : declSources;
            void* declaration = InstancedDeclaration(sourceDecl, instanceSource);
            const SharedPtr* instances = declaration ? InstanceBuffer(leader.bones) : nullptr;
            if (!instances)
                return;   // members stay undrawn and render singly

            g_ogre.unsetAllBindings(g_binding);
            for (uint16_t i = 0; i < lastBound; ++i)
            {
                if (g_ogre.isBufferBound(sourceBinding, i))
                    g_ogre.setBinding(g_binding, i, *g_ogre.getBuffer(sourceBinding, i));
            }
            g_ogre.setBinding(g_binding, instanceSource, *instances);

            std::memcpy(g_draw.vertexData, sourceData, kVertexDataSize);
            std::memcpy(g_draw.vertexData + kVertexDataDecl, &declaration, sizeof(void*));
            std::memcpy(g_draw.vertexData + kVertexDataBinding, &g_binding, sizeof(void*));
            for (uint32_t i = 0; i < count; ++i)
            {
                const Member& member = g_members[indices[i]];
                std::memcpy(&g_draw.palette[i * leader.bones], &g_matrices[member.firstMatrix],
                    sizeof(Matrix4) * leader.bones);
            }
            g_draw.expectedVertexData = leader.op.vertexData;
            g_draw.instances = count;
            g_draw.bones = leader.bones;
            g_draw.mismatch = false;

            if (!g_twinBound)
            {
                visitor->usedPass = g_ogre.setPass(visitor->sceneManager, g_pending.twin, false, true);
                g_twinBound = true;
            }

            g_draw.leaderVptr = *static_cast<void**>(leader.renderable);
            g_draw.leader = leader.renderable;
            *static_cast<void**>(leader.renderable) = g_leaderVtable;
            g_ogre.visitRenderable(visitor, leader.renderable);
            *static_cast<void**>(leader.renderable) = g_draw.leaderVptr;
            g_draw.leader = nullptr;
            g_ogre.unsetAllBindings(g_binding);

            if (g_draw.mismatch)
            {
                ++g_stats.renderOpMismatch;
                return;
            }
            for (uint32_t i = 0; i < count; ++i)
                g_members[indices[i]].drawn = true;
            ++g_stats.batches;
            g_stats.batchedMembers += count;
            if (count > g_stats.maxBatch)
                g_stats.maxBatch = count;
        }

        bool Groupable(const Member& a, const Member& b)
        {
            return a.op.vertexData == b.op.vertexData && a.op.indexData == b.op.indexData &&
                a.op.operationType == b.op.operationType && a.op.useIndexes == b.op.useIndexes &&
                a.bones == b.bones && a.castsShadows == b.castsShadows &&
                a.negativeScale == b.negativeScale && SameLights(a.lights, b.lights, g_pending.lights);
        }

        void FlushCore(Visitor* visitor)
        {
            g_members.clear();
            g_matrices.clear();
            for (void* renderable : g_pending.members)
            {
                Member member = {};
                member.renderable = renderable;
                member.op.operationType = 4;   // OT_TRIANGLE_LIST, as Ogre's constructor
                member.op.useIndexes = true;
                member.op.numberOfInstances = 1;
                member.op.srcRenderable = renderable;
                member.op.useGlobalInstancingVertexBufferIsAvailable = true;
                g_ogre.getRenderOperation(renderable, member.op);
                member.bones = g_ogre.getNumWorldTransforms(renderable);
                member.eligible = member.op.vertexData && member.op.numberOfInstances == 1 &&
                    !member.op.renderToVertexBuffer && member.bones > 0 && member.bones <= kPaletteBones / 2;
                if (member.eligible)
                {
                    member.firstMatrix = static_cast<uint32_t>(g_matrices.size());
                    g_matrices.resize(g_matrices.size() + member.bones);
                    g_ogre.getWorldTransforms(renderable, &g_matrices[member.firstMatrix]);
                    member.negativeScale = NegativeScale(g_matrices[member.firstMatrix]);
                    member.lights = g_ogre.getLights(renderable);
                    member.castsShadows = g_ogre.getCastsShadows(renderable);
                }
                else
                {
                    ++g_stats.ineligible;
                }
                g_members.push_back(member);
            }

            // Group by first matching leader; small n, few groups.
            const uint32_t n = static_cast<uint32_t>(g_members.size());
            g_groupOf.assign(n, UINT32_MAX);
            std::vector<uint32_t> leaders;
            std::vector<uint32_t> sizes;
            for (uint32_t i = 0; i < n; ++i)
            {
                if (!g_members[i].eligible)
                    continue;
                uint32_t group = UINT32_MAX;
                for (uint32_t g = 0; g < leaders.size(); ++g)
                {
                    if (Groupable(g_members[leaders[g]], g_members[i]))
                    {
                        group = g;
                        break;
                    }
                }
                if (group == UINT32_MAX)
                {
                    group = static_cast<uint32_t>(leaders.size());
                    leaders.push_back(i);
                    sizes.push_back(0);
                }
                g_groupOf[i] = group;
                ++sizes[group];
            }

            // Singletons and ineligible members first, with the source pass
            // still bound by the stock visit(Pass*).
            for (uint32_t i = 0; i < n; ++i)
            {
                if (g_groupOf[i] == UINT32_MAX || sizes[g_groupOf[i]] < 2)
                    DrawSingle(visitor, g_members[i]);
            }

            std::vector<uint32_t> chunk;
            for (uint32_t g = 0; g < leaders.size(); ++g)
            {
                if (sizes[g] < 2)
                    continue;
                const uint32_t perDraw = kPaletteBones / g_members[leaders[g]].bones;
                chunk.clear();
                for (uint32_t i = 0; i < n; ++i)
                {
                    if (g_groupOf[i] != g)
                        continue;
                    chunk.push_back(i);
                    if (chunk.size() == perDraw)
                    {
                        DrawChunk(visitor, chunk.data(), static_cast<uint32_t>(chunk.size()));
                        chunk.clear();
                    }
                }
                if (!chunk.empty())
                    DrawChunk(visitor, chunk.data(), static_cast<uint32_t>(chunk.size()));
            }

            // Anything a batch could not take renders singly on the source pass.
            for (uint32_t i = 0; i < n; ++i)
            {
                if (g_members[i].drawn)
                    continue;
                if (g_twinBound)
                    BindSource(visitor, g_pending.sourcePass);
                DrawSingle(visitor, g_members[i]);
            }
        }

        bool FlushCxx(Visitor* visitor)
        {
            try
            {
                FlushCore(visitor);
                return true;
            }
            catch (...)
            {
                return false;
            }
        }

        // No destructible locals: SEH and C++ unwinding do not mix in one frame.
        void RenderUndrawnGuarded(Visitor* visitor)
        {
            __try
            {
                if (g_twinBound)
                    BindSource(visitor, g_pending.sourcePass);
                Member* members = g_members.data();
                const size_t count = g_members.size();
                for (size_t i = 0; i < count; ++i)
                {
                    if (!members[i].drawn)
                    {
                        members[i].drawn = true;
                        g_ogre.visitRenderable(visitor, members[i].renderable);
                    }
                }
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
            }
        }

        void FlushGuarded(Visitor* visitor)
        {
            bool ok = false;
            __try
            {
                ok = FlushCxx(visitor);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                ok = false;
            }
            if (ok)
                return;
            if (g_draw.leader)
            {
                *static_cast<void**>(g_draw.leader) = g_draw.leaderVptr;
                g_draw.leader = nullptr;
            }
            Disable("fault during instanced flush");
            RenderUndrawnGuarded(visitor);
        }

        // Draws the pending members. With rebindSource the source pass is left
        // bound afterwards, for callers that do not bind a pass next.
        void Flush(bool rebindSource)
        {
            if (g_pending.members.empty())
                return;
            auto* visitor = static_cast<Visitor*>(g_pending.visitor);
            g_twinBound = false;
            if (g_failed.load(std::memory_order_acquire))
            {
                // Latched off with members waiting: draw them the stock way.
                g_members.clear();
                for (void* renderable : g_pending.members)
                {
                    Member member = {};
                    member.renderable = renderable;
                    g_members.push_back(member);
                }
                RenderUndrawnGuarded(visitor);
            }
            else
            {
                FlushGuarded(visitor);
            }
            if (rebindSource && g_twinBound)
                BindSource(visitor, g_pending.sourcePass);
            g_twinBound = false;
            g_pending.members.clear();
        }

        // --- hooks ---------------------------------------------------------------

        void __fastcall VisitRenderableHook(void* visitor, void*, void* renderable)
        {
            if (g_depth > 0 && g_pending.twin && visitor == g_pending.visitor && renderable &&
                *static_cast<void**>(renderable) == g_ogre.subEntityVtable && Enabled())
            {
                g_pending.members.push_back(renderable);
                ++g_stats.deferred;
                return;
            }
            g_ogre.visitRenderable(visitor, renderable);
        }

        bool __fastcall VisitPassHook(void* visitor, void*, const void* pass)
        {
            Flush(false);
            g_pending.twin = nullptr;
            g_pending.visitor = visitor;
            g_pending.sourcePass = pass;
            const bool render = g_ogre.visitPass(visitor, pass);
            if (render && g_depth > 0 && Enabled())
            {
                void* sceneManager = static_cast<Visitor*>(visitor)->sceneManager;
                if (sceneManager && !g_ogre.stateChangesSuppressed(sceneManager))
                    g_pending.twin = GpuSkinningInstancedTwinPass(pass, &g_pending.lights);
            }
            return render;
        }

        void __fastcall VisitRenderablePassHook(void* visitor, void*, void* renderablePass)
        {
            Flush(false);
            g_pending.twin = nullptr;
            g_ogre.visitRenderablePass(visitor, renderablePass);
        }

        struct DepthScope
        {
            DepthScope() { ++g_depth; }
            ~DepthScope()
            {
                --g_depth;
                g_pending.twin = nullptr;
                g_pending.members.clear();
            }
        };

        void __fastcall AcceptVisitorHook(const void* collection, void*, void* visitor, int mode)
        {
            const auto original = reinterpret_cast<FnAcceptVisitor>(g_acceptTrampoline);
            Flush(true);
            g_pending.twin = nullptr;
            DepthScope scope;
            original(collection, visitor, mode);
            Flush(true);
        }

        // --- install -------------------------------------------------------------

        bool PatchSlot(void** slot, void* hook)
        {
            DWORD old = 0;
            if (!VirtualProtect(slot, sizeof(void*), PAGE_READWRITE, &old))
                return false;
            *slot = hook;
            DWORD ignored = 0;
            VirtualProtect(slot, sizeof(void*), old, &ignored);
            FlushInstructionCache(GetCurrentProcess(), slot, sizeof(void*));
            return true;
        }

        void Install()
        {
            g_installAttempted = true;
            const char* missing = nullptr;
            if (!ResolveApi(missing))
            {
                LogShimA(LogLevel::Warn, kComponent, "[GPUINST] not installed: missing export %s", missing);
                return;
            }

            void** visitorVtable = g_ogre.visitorVtable;
            void** subEntity = g_ogre.subEntityVtable;
            if (!Readable(visitorVtable, 4 * sizeof(void*)) || !Readable(subEntity - 1, (kVtableCopySlots + 1) * sizeof(void*)))
            {
                LogShimA(LogLevel::Warn, kComponent, "[GPUINST] not installed: vtables unreadable");
                return;
            }
            // Slot 0 is the destructor, then visit(Renderable*), visit(Pass*),
            // visit(RenderablePass*) in declaration order.
            if (!SameFunction(visitorVtable[1], reinterpret_cast<void*>(g_ogre.visitRenderable)) ||
                !SameFunction(visitorVtable[2], reinterpret_cast<void*>(g_ogre.visitPass)) ||
                !SameFunction(visitorVtable[3], reinterpret_cast<void*>(g_ogre.visitRenderablePass)))
            {
                LogShimA(LogLevel::Warn, kComponent, "[GPUINST] not installed: visitor vtable does not match its exports");
                return;
            }
            g_slotGetRenderOperation = FindSlot(subEntity, reinterpret_cast<void*>(g_ogre.getRenderOperation));
            g_slotGetWorldTransforms = FindSlot(subEntity, reinterpret_cast<void*>(g_ogre.getWorldTransforms));
            g_slotGetNumWorldTransforms = FindSlot(subEntity, reinterpret_cast<void*>(g_ogre.getNumWorldTransforms));
            if (g_slotGetRenderOperation < 0 || g_slotGetWorldTransforms < 0 || g_slotGetNumWorldTransforms < 0)
            {
                LogShimA(LogLevel::Warn, kComponent, "[GPUINST] not installed: SubEntity vtable slots not found (%d,%d,%d)",
                    g_slotGetRenderOperation, g_slotGetWorldTransforms, g_slotGetNumWorldTransforms);
                return;
            }
            g_slotUnlock = Readable(g_ogre.hardwareBufferVtable, kVtableCopySlots * sizeof(void*))
                ? FindSlot(g_ogre.hardwareBufferVtable, reinterpret_cast<void*>(g_ogre.unlock)) : -1;
            if (g_slotUnlock < 0)
            {
                LogShimA(LogLevel::Warn, kComponent, "[GPUINST] not installed: HardwareBuffer::unlock slot not found");
                return;
            }
            std::memcpy(g_leaderVtableStorage, subEntity - 1, sizeof(g_leaderVtableStorage));
            g_leaderVtable[g_slotGetRenderOperation] = reinterpret_cast<void*>(&LeaderGetRenderOperation);
            g_leaderVtable[g_slotGetWorldTransforms] = reinterpret_cast<void*>(&LeaderGetWorldTransforms);
            g_leaderVtable[g_slotGetNumWorldTransforms] = reinterpret_cast<void*>(&LeaderGetNumWorldTransforms);

            void* manager = g_ogre.bufferManager();
            g_binding = manager ? g_ogre.createBinding(manager) : nullptr;
            if (!g_binding)
            {
                LogShimA(LogLevel::Warn, kComponent, "[GPUINST] not installed: no vertex buffer binding");
                return;
            }

            // push ebp; mov ebp, esp; push -1
            static const uint8_t kAcceptPrologue[] = { 0x55, 0x8B, 0xEC, 0x6A, 0xFF };
            if (!InstallInlineDetour32(g_acceptDetour, g_ogre.acceptVisitor,
                    reinterpret_cast<void*>(&AcceptVisitorHook), sizeof(kAcceptPrologue),
                    kAcceptPrologue, sizeof(kAcceptPrologue), &g_acceptTrampoline))
            {
                LogShimA(LogLevel::Warn, kComponent, "[GPUINST] not installed: acceptVisitor prologue mismatch");
                return;
            }
            // The detour is live but inert until the vtable slots defer.
            if (!PatchSlot(&visitorVtable[1], reinterpret_cast<void*>(&VisitRenderableHook)) ||
                !PatchSlot(&visitorVtable[2], reinterpret_cast<void*>(&VisitPassHook)) ||
                !PatchSlot(&visitorVtable[3], reinterpret_cast<void*>(&VisitRenderablePassHook)))
            {
                Disable("visitor vtable not writable");
                return;
            }
            g_installed = true;
            LogShimA(LogLevel::Info, kComponent,
                "[GPUINST] draw hooks installed (SubEntity slots renderOp=%d xforms=%d count=%d)",
                g_slotGetRenderOperation, g_slotGetWorldTransforms, g_slotGetNumWorldTransforms);
        }

        void LogMissionSummary()
        {
            LogShimA(LogLevel::Info, kComponent,
                "[GPUINST] mission summary: deferred=%u batches=%u batched=%u max_batch=%u singles=%u "
                "ineligible=%u decl_refused=%u renderop_mismatch=%u declarations=%u",
                g_stats.deferred, g_stats.batches, g_stats.batchedMembers, g_stats.maxBatch, g_stats.singles,
                g_stats.ineligible, g_stats.declRefused, g_stats.renderOpMismatch,
                static_cast<uint32_t>(g_declarations.size()));
        }

        void ReleaseMissionStateGuarded()
        {
            __try
            {
                ReleaseDeclarations();
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                Disable("fault releasing declarations");
            }
        }
    }

    void GpuInstancingNotifyMissionRunStateChanged(bool running)
    {
        if (running || !g_installed)
            return;
        LogMissionSummary();
        g_stats = {};
        ReleaseMissionStateGuarded();
    }

    void GpuInstancingRenderFrameTick()
    {
        if (g_failed.load(std::memory_order_acquire) || !GpuSkinningInstancingActive())
            return;
        const uint32_t generation = GpuSkinningGeneration();
        if (g_installed && generation != g_generation)
        {
            // A mission started without a stop notification: declarations
            // from the last one may name freed sources.
            ReleaseMissionStateGuarded();
            g_stats = {};
        }
        g_generation = generation;
        if (!g_installAttempted)
            Install();
    }
}
