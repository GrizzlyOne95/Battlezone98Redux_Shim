#include "fog_wake_renderer.h"
#include "ogre_runtime.h"
#include "shim_log.h"
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <Windows.h>
#include <bcrypt.h>
#include <algorithm>
#include <cmath>
#include <cstdint>
#include <string>
#include <type_traits>
#include <vector>

// sizeof/alignof only: all engine operations use verified shipped exports.
// The pinned headers require this TU's stdcpp14 project override.
#define register
#include "OgreScriptCompiler.h"
#undef register

#pragma comment(lib, "bcrypt.lib")

namespace BZROpenShim { namespace FogWake { namespace {
    struct Colour { float r, g, b, a; };
    struct Shared { void* rep = nullptr; void* info = nullptr; };
    static_assert(sizeof(Shared) == 8, "Retail Ogre ABI requires Win32");
    template<class T> T Resolve(const char* name)
    { return reinterpret_cast<T>(OgreRuntime::ResolveExport(name)); }
    using Singleton = void* (__cdecl*)();
    using GetObject = void* (__thiscall*)(void*);
    using ObjectOp = void (__thiscall*)(void*, void*);
    using BoolOp = void (__thiscall*)(void*, bool);
    using CreateSet = void* (__thiscall*)(void*, unsigned);
    using Dimensions = void (__thiscall*)(void*, float, float);
    using CreateBillboard = void* (__thiscall*)(void*, float, float, float, const Colour&);
    using SetColour = void (__thiscall*)(void*, const Colour&);
    using SetPosition = void (__thiscall*)(void*, float, float, float);
    using MaterialName = void (__thiscall*)(void*, const std::string&, const std::string&);
    using GetResource = Shared* (__thiscall*)(void*, Shared*, const std::string&, const std::string&);
    using CreateProgram = Shared* (__thiscall*)(void*, Shared*, const std::string&,
        const std::string&, const std::string&, int);
    using StringOp = void (__thiscall*)(void*, const std::string&);
    using Parameter = bool (__thiscall*)(void*, const std::string&, const std::string&);
    using Load = void (__thiscall*)(void*, bool);
    using Supported = bool (__thiscall*)(void*);
    using Construct = void (__thiscall*)(void*);
    using Compile = bool (__thiscall*)(void*, const std::string&, const std::string&, const std::string&);
    using Destruct = void* (__thiscall*)(void*, unsigned);
    using Queue = void (__thiscall*)(void*, unsigned char);
    struct Api
    {
        Singleton root, materials, programs;
        GetObject renderSystem, rootNode;
        ObjectOp attach, detach, destroy;
        BoolOp worldSpace, shadows;
        CreateSet createSet;
        Dimensions dimensions;
        CreateBillboard billboard;
        SetColour colour;
        SetPosition position;
        MaterialName material;
        GetResource getMaterial;
        CreateProgram createProgram;
        StringOp source, remove;
        Parameter parameter;
        Load load;
        Supported supported;
        Construct construct;
        Compile compile;
        Queue queue;
    } api{};
    void* owner = nullptr;
    void* node = nullptr;
    void* set = nullptr;
    std::vector<void*> billboards;
    std::string materialName, vertexName, fragmentName;
    unsigned serial = 0;
    bool failed = false, qualified = false;

    // Match the same retail Ogre build pinned by terrain_proxy.cpp. This ABI
    // boundary includes STL string/ScriptCompiler layout, so exports alone do
    // not qualify a different DLL. No DLL is loaded by the feature.
    bool QualifyDll()
    {
        wchar_t path[MAX_PATH]{};
        HMODULE module = reinterpret_cast<HMODULE>(OgreRuntime::GetModuleBase());
        if (!module || !GetModuleFileNameW(module, path, MAX_PATH)) return false;
        HANDLE file = CreateFileW(path, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
            nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
        if (file == INVALID_HANDLE_VALUE) return false;
        BCRYPT_ALG_HANDLE algorithm = nullptr;
        BCRYPT_HASH_HANDLE hash = nullptr;
        unsigned char digest[32]{};
        bool ok = BCryptOpenAlgorithmProvider(&algorithm, BCRYPT_SHA256_ALGORITHM, nullptr, 0) >= 0;
        if (ok) ok = BCryptCreateHash(algorithm, &hash, nullptr, 0, nullptr, 0, 0) >= 0;
        unsigned char buffer[16384];
        DWORD read = 0;
        while (ok)
        {
            if (!ReadFile(file, buffer, sizeof(buffer), &read, nullptr)) { ok = false; break; }
            if (!read) break;
            ok = BCryptHashData(hash, buffer, read, 0) >= 0;
        }
        if (ok) ok = BCryptFinishHash(hash, digest, sizeof(digest), 0) >= 0;
        if (hash) BCryptDestroyHash(hash);
        if (algorithm) BCryptCloseAlgorithmProvider(algorithm, 0);
        CloseHandle(file);
        const unsigned char expected[32] = {0xE5,0xE6,0x93,0x96,0x0B,0x95,0xAD,0x0D,
            0x60,0x73,0x3A,0x3B,0x68,0x84,0x64,0xA6,0xC6,0xCB,0xA2,0x34,0xE8,0x69,
            0x50,0x69,0x8F,0x9C,0x2B,0xEA,0x4A,0xCF,0xEB,0x45};
        return ok && std::equal(digest, digest + 32, expected);
    }

    bool ResolveApi()
    {
#define BIND(member, type, symbol) api.member = Resolve<type>(symbol); if (!api.member) return false
        BIND(root, Singleton, "?getSingletonPtr@Root@Ogre@@SAPAV12@XZ");
        BIND(materials, Singleton, "?getSingletonPtr@MaterialManager@Ogre@@SAPAV12@XZ");
        BIND(programs, Singleton, "?getSingletonPtr@HighLevelGpuProgramManager@Ogre@@SAPAV12@XZ");
        BIND(renderSystem, GetObject, "?getRenderSystem@Root@Ogre@@QAEPAVRenderSystem@2@XZ");
        BIND(rootNode, GetObject, "?getRootSceneNode@SceneManager@Ogre@@UAEPAVSceneNode@2@XZ");
        BIND(attach, ObjectOp, "?attachObject@SceneNode@Ogre@@UAEXPAVMovableObject@2@@Z");
        BIND(detach, ObjectOp, "?detachObject@SceneNode@Ogre@@UAEXPAVMovableObject@2@@Z");
        BIND(destroy, ObjectOp, "?destroyBillboardSet@SceneManager@Ogre@@UAEXPAVBillboardSet@2@@Z");
        BIND(worldSpace, BoolOp, "?setBillboardsInWorldSpace@BillboardSet@Ogre@@UAEX_N@Z");
        BIND(shadows, BoolOp, "?setCastShadows@MovableObject@Ogre@@UAEX_N@Z");
        BIND(createSet, CreateSet, "?createBillboardSet@SceneManager@Ogre@@UAEPAVBillboardSet@2@I@Z");
        BIND(dimensions, Dimensions, "?setDefaultDimensions@BillboardSet@Ogre@@UAEXMM@Z");
        BIND(billboard, CreateBillboard, "?createBillboard@BillboardSet@Ogre@@QAEPAVBillboard@2@MMMABVColourValue@2@@Z");
        BIND(colour, SetColour, "?setColour@Billboard@Ogre@@QAEXABVColourValue@2@@Z");
        BIND(position, SetPosition, "?setPosition@Billboard@Ogre@@QAEXMMM@Z");
        BIND(material, MaterialName, "?setMaterialName@BillboardSet@Ogre@@UAEXABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@0@Z");
        BIND(getMaterial, GetResource, "?getByName@MaterialManager@Ogre@@QAE?AV?$SharedPtr@VMaterial@Ogre@@@2@ABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@0@Z");
        BIND(createProgram, CreateProgram, "?createProgram@HighLevelGpuProgramManager@Ogre@@QAE?AV?$SharedPtr@VHighLevelGpuProgram@Ogre@@@2@ABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@00W4GpuProgramType@2@@Z");
        BIND(source, StringOp, "?setSource@GpuProgram@Ogre@@UAEXABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
        BIND(remove, StringOp, "?remove@ResourceManager@Ogre@@UAEXABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
        BIND(parameter, Parameter, "?setParameter@StringInterface@Ogre@@UAE_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@0@Z");
        BIND(load, Load, "?load@Resource@Ogre@@UAEX_N@Z");
        BIND(supported, Supported, "?isSupported@GpuProgram@Ogre@@UBE_NXZ");
        BIND(construct, Construct, "??0ScriptCompiler@Ogre@@QAE@XZ");
        BIND(compile, Compile, "?compile@ScriptCompiler@Ogre@@QAE_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@00@Z");
        BIND(queue, Queue, "?setRenderQueueGroup@MovableObject@Ogre@@UAEXE@Z");
#undef BIND
        return true;
    }

    // A manager retains one reference to all resources acquired here. Release
    // only our returned handoff, as in terrain_proxy; never run an Ogre allocator
    // or delete an Ogre SharedPtr control block through the shim CRT.
    void Release(Shared& value)
    {
        if (value.rep && value.info)
        {
            auto* count = reinterpret_cast<volatile LONG*>(static_cast<char*>(value.info) + sizeof(void*));
            if (InterlockedCompareExchange(count, 0, 0) > 1) InterlockedDecrement(count);
        }
        value = {};
    }
    struct Handoff { Shared value; ~Handoff() { Release(value); } };

    const char* vertexSource = R"(
float4x4 worldViewProj;
struct Out { float4 position : SV_POSITION; float2 uv : TEXCOORD0; float4 colour : COLOR0; };
Out main(float4 position : POSITION, float4 colour : COLOR0, float2 uv : TEXCOORD0)
{
    Out o; o.position = mul(worldViewProj, position); o.uv = uv; o.colour = colour; return o;
})";
    // Analytic texture, evaluated in UV space. The radial envelope reaches zero
    // before each quad edge; no asset file, sampler, depth SRV, or MSAA resolve.
    const char* fragmentSource = R"(
float4 main(float2 uv : TEXCOORD0, float4 colour : COLOR0) : SV_TARGET
{
    float2 p = uv * 2 - 1;
    float envelope = saturate(1 - dot(p, p));
    envelope = envelope * envelope * (3 - 2 * envelope);
    float noise = .72 + .16 * sin(uv.x * 18 + sin(uv.y * 13))
                      + .12 * sin(uv.y * 27 - uv.x * 11);
    return float4(colour.rgb, colour.a * envelope * noise);
})";

    bool MakeProgram(const std::string& name, int type, const char* source)
    {
        Handoff program;
        api.createProgram(api.programs(), &program.value, name, "General", "hlsl", type);
        if (!program.value.rep) return false;
        api.source(program.value.rep, source);
        // StringInterface is a secondary base. Retail exported member calls
        // expect its adjusted this, supplied by the pinned class layout.
        auto* high = static_cast<Ogre::HighLevelGpuProgram*>(program.value.rep);
        void* stringInterface = static_cast<Ogre::StringInterface*>(high);
        if (!api.parameter(stringInterface, "entry_point", "main") ||
            !api.parameter(stringInterface, "target", type == 0 ? "vs_4_0" : "ps_4_0")) return false;
        api.load(program.value.rep, false);
        return api.supported(program.value.rep);
    }

    bool MakeMaterial()
    {
        if (!MakeProgram(vertexName, 0, vertexSource) || !MakeProgram(fragmentName, 1, fragmentSource)) return false;
        const std::string script = "material " + materialName + R"(
{
 technique
 {
  pass
  {
   lighting off
   depth_check on
   depth_write off
   scene_blend alpha_blend
   cull_hardware none
   cull_software none
   fog_override true none
   vertex_program_ref )" + vertexName + R"(
   {
    param_named_auto worldViewProj worldviewproj_matrix
   }
   fragment_program_ref )" + fragmentName + R"(
   {
   }
  }
 }
}
)";
        std::aligned_storage<sizeof(Ogre::ScriptCompiler), alignof(Ogre::ScriptCompiler)>::type storage;
        api.construct(&storage);
        struct CompilerGuard
        {
            void* object;
            ~CompilerGuard()
            {
                auto vtable = *static_cast<void***>(object);
                reinterpret_cast<Destruct>(vtable[0])(object, 0);
            }
        } guard{&storage};
        if (!api.compile(&storage, script, "OpenShimFogWake.generated.material", "General")) return false;
        Handoff material;
        api.getMaterial(api.materials(), &material.value, materialName, "General");
        if (!material.value.rep) return false;
        api.load(material.value.rep, false);
        return true;
    }

    bool IsDX11()
    {
        void* root = api.root();
        void* renderer = root ? api.renderSystem(root) : nullptr;
        if (!renderer) return false;
        MEMORY_BASIC_INFORMATION memory{};
        // The active render-system object's vtable belongs to its plugin. Merely
        // finding Direct3D11.dll loaded would also pass with DX9 selected.
        void* vtable = *static_cast<void**>(renderer);
        return VirtualQuery(vtable, &memory, sizeof(memory)) &&
            memory.AllocationBase == GetModuleHandleW(L"RenderSystem_Direct3D11.dll");
    }

    void Reset(void* live)
    {
        if (qualified && OgreRuntime::IsLoaded())
        {
            if (set && owner == live)
            {
                if (node) api.detach(node, set);
                api.destroy(owner, set);
            }
            // Scene-owned objects are never dereferenced on a stale scene.
            // Ogre scene teardown owns them; our named resources are detached
            // from the managers while any surviving object keeps its references.
            if (api.materials && api.materials() && !materialName.empty())
                api.remove(api.materials(), materialName);
            if (api.programs && api.programs())
            {
                if (!vertexName.empty()) api.remove(api.programs(), vertexName);
                if (!fragmentName.empty()) api.remove(api.programs(), fragmentName);
            }
        }
        set = node = owner = nullptr;
        billboards.clear();
        materialName.clear(); vertexName.clear(); fragmentName.clear();
        failed = false;
    }

    bool Update(void* scene, const RendererField& field, const RendererConfig& config)
    {
        if (!scene || !field.clearance || !field.width || !field.height ||
            field.width > 2048 || field.height > 2048 ||
            !std::isfinite(field.cellSize) || field.cellSize <= 0 ||
            !std::isfinite(field.originX) || !std::isfinite(field.originZ) ||
            !std::isfinite(config.groundY) || !std::isfinite(config.height) || config.height <= 0 ||
            !std::isfinite(config.density) || config.density < 0 || config.density > 1 ||
            !std::isfinite(config.red) || !std::isfinite(config.green) || !std::isfinite(config.blue)) return false;
        if (owner && owner != scene) Reset(scene);
        if (failed) return false;
        if (!qualified)
        {
            if (!QualifyDll() || !ResolveApi()) { failed = true; return false; }
            qualified = true;
        }
        if (!IsDX11()) { failed = true; return false; }
        // Bound both CPU work and transparent overdraw; spatial downsampling
        // chooses a uniform stride rather than dropping one side of the bank.
        unsigned budget = std::max(16u, std::min(4096u, config.maxBillboards));
        unsigned stride = 1;
        while (((field.width + stride - 1) / stride) * ((field.height + stride - 1) / stride) * 2 > budget) ++stride;
        unsigned nx = (field.width + stride - 1) / stride;
        unsigned nz = (field.height + stride - 1) / stride;
        unsigned count = nx * nz * 2;
        if (set && billboards.size() != count) Reset(scene);
        if (!set)
        {
            owner = scene;
            const std::string prefix = "OpenShim/FogWake/" + std::to_string(++serial);
            materialName = prefix + "/Material"; vertexName = prefix + "/VS"; fragmentName = prefix + "/PS";
            if (!MakeMaterial()) { Reset(scene); failed = true; return false; }
            node = api.rootNode(scene);
            if (!node) { Reset(scene); failed = true; return false; }
            set = api.createSet(scene, count);
            if (!set) { Reset(scene); failed = true; return false; }
            api.worldSpace(set, true);
            api.shadows(set, false);
            api.queue(set, 60); // Ordinary world geometry, not a fullscreen pass.
            api.material(set, materialName, "General");
            const Colour invisible{0,0,0,0};
            billboards.reserve(count);
            for (unsigned i = 0; i < count; ++i)
            {
                void* billboard = api.billboard(set, 0, 0, 0, invisible);
                if (!billboard) { Reset(scene); failed = true; return false; }
                billboards.push_back(billboard);
            }
            api.attach(node, set);
            LogShimA(LogLevel::Info, "fog-wake", "[FOG-RENDER] Created %u depth-tested mist billboards; DX11 prototype, visual qualification pending", count);
        }
        const float spacing = stride * field.cellSize;
        api.dimensions(set, spacing * 1.6f, config.height * .85f);
        unsigned index = 0;
        for (unsigned z = 0; z < field.height; z += stride)
        for (unsigned x = 0; x < field.width; x += stride)
        {
            // Maximum clearance in this footprint prevents coarse LOD samples
            // from filling a narrow vehicle trail. This deliberately makes
            // coarse wakes wider, rather than hiding the disturbance entirely.
            float clearance = 0;
            for (unsigned dz = z; dz < std::min(z + stride, field.height); ++dz)
            for (unsigned dx = x; dx < std::min(x + stride, field.width); ++dx)
            {
                float sample = field.clearance[dz * field.width + dx];
                if (std::isfinite(sample)) clearance = std::max(clearance, sample);
            }
            float alpha = config.density * (1 - std::max(0.f, std::min(1.f, clearance)));
            Colour colour{std::max(0.f, std::min(1.f, config.red)),
                std::max(0.f, std::min(1.f, config.green)),
                std::max(0.f, std::min(1.f, config.blue)), alpha};
            float cx = field.originX + (x + .5f * std::min(stride, field.width - x)) * field.cellSize;
            float cz = field.originZ + (z + .5f * std::min(stride, field.height - z)) * field.cellSize;
            for (unsigned layer = 0; layer < 2; ++layer)
            {
                void* billboard = billboards[index++];
                api.position(billboard, cx, config.groundY + config.height * (.28f + .42f * layer), cz);
                api.colour(billboard, colour);
            }
        }
        return true;
    }
} // namespace

bool UpdateFogWakeRenderer(void* scene, const RendererField& field, const RendererConfig& config) noexcept
{
    try { return Update(scene, field, config); }
    catch (...)
    {
        try { Reset(scene); } catch (...) {}
        failed = true;
        LogShimA(LogLevel::Warn, "fog-wake", "[FOG-RENDER] Resource/geometry setup failed; disabled until mission reset");
        return false;
    }
}
void ResetFogWakeRenderer(void* liveSceneManager) noexcept
{
    try { Reset(liveSceneManager); }
    catch (...) { set = node = owner = nullptr; billboards.clear(); failed = true; }
}
unsigned FogWakeRendererBillboardCount() noexcept { return static_cast<unsigned>(billboards.size()); }
}}
