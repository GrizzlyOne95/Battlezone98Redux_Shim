#include "planet_environment.h"
#include "planet_environment_core.h"

#include "openshim_assets.h"
#include "render_profile_runtime.h"
#include "shim_log.h"

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <Windows.h>
#include <d3d11.h>
#include <wrl/client.h>

#include <atomic>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <mutex>
#include <string>
#include <vector>

namespace BZROpenShim
{
    namespace
    {
        using Microsoft::WRL::ComPtr;

        constexpr char kComponent[] = "planet-env";
        constexpr std::uintmax_t kMaxEnvFileBytes = 4u * 1024u * 1024u;

        std::mutex g_codeMutex;
        std::string g_worldCode;

        // A recorded world or a mission start bumps the request; the render
        // tick applies it once the neutral cubemaps exist. A session that
        // boots straight into a mission never sees a RUN_STARTED transition,
        // and the materials may load their textures after it, so the swap
        // cannot rely on the mission seam alone.
        std::atomic<std::uint32_t> g_requestGeneration{ 0 };
        std::uint32_t g_appliedGeneration = 0;
        std::uint32_t g_pendingGeneration = 0;
        std::uint32_t g_pendingFrames = 0;
        std::uint32_t g_pendingAttempts = 0;
        constexpr std::uint32_t kFramesBetweenAttempts = 30;
        constexpr std::uint32_t kMaxAttempts = 40;

        // The neutral cubemaps are Ogre textures created by the CR/Enhanced
        // materials; only the lookup and the native D3D11 handle are needed.
        // Terrain proxy resolves its own larger Ogre table behind an opt-in
        // gate, so this module carries just these four exports.
        struct OgreSharedPtr
        {
            void* rep = nullptr;
            void* info = nullptr;
        };
        using FnGetSingleton = void* (__cdecl*)();
        using FnGetByName = OgreSharedPtr* (__thiscall*)(
            void*, OgreSharedPtr*, const std::string&, const std::string&);
        using FnSharedPtrRelease = void(__thiscall*)(OgreSharedPtr*);
        using FnGetD3D11Texture2D = ID3D11Texture2D* (__thiscall*)(void*);

        struct OgreApi
        {
            bool attempted = false;
            FnGetSingleton getTextureManager = nullptr;
            FnGetByName getByName = nullptr;
            FnSharedPtrRelease release = nullptr;
            FnGetD3D11Texture2D getTex2D = nullptr;
        };
        OgreApi g_ogre;

        enum class Status
        {
            Neutral,      // nothing to apply and nothing to restore
            Applied,
            Restored,
            Unavailable,  // texture or D3D11 resource not reachable
            Rejected,     // file or destination failed validation
            Failed,       // D3D11 call failed
        };

        const char* StatusName(Status status)
        {
            switch (status)
            {
            case Status::Neutral:     return "neutral";
            case Status::Applied:     return "applied";
            case Status::Restored:    return "restored";
            case Status::Unavailable: return "unavailable";
            case Status::Rejected:    return "rejected";
            default:                  return "failed";
            }
        }

        struct KindState
        {
            const char* kind = "";
            ID3D11Texture2D* dst = nullptr;   // identity only, not owned
            ComPtr<ID3D11Texture2D> backup;   // neutral contents
            bool unavailableLogged = false;
        };
        KindState g_kinds[2] = { { "prefilter" }, { "irradiance" } };

        template <typename T>
        T Resolve(HMODULE module, const char* name)
        {
            return reinterpret_cast<T>(GetProcAddress(module, name));
        }

        bool ResolveOgreApi()
        {
            if (g_ogre.attempted)
                return g_ogre.getTex2D != nullptr;
            g_ogre.attempted = true;
            HMODULE ogre = GetModuleHandleW(L"OgreMain.dll");
            HMODULE renderer = GetModuleHandleW(L"RenderSystem_Direct3D11.dll");
            if (!ogre || !renderer)
                return false;
            g_ogre.getTextureManager = Resolve<FnGetSingleton>(ogre,
                "?getSingletonPtr@TextureManager@Ogre@@SAPAV12@XZ");
            g_ogre.getByName = Resolve<FnGetByName>(ogre,
                "?getByName@TextureManager@Ogre@@QAE?AV?$SharedPtr@VTexture@Ogre@@@2@ABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@0@Z");
            // Same representation-only release terrain_proxy uses for every
            // SharedPtr<T>: it touches the pointer pair and its control block.
            g_ogre.release = Resolve<FnSharedPtrRelease>(ogre,
                "?setNull@?$SharedPtr@VHardwareVertexBuffer@Ogre@@@Ogre@@QAEXXZ");
            g_ogre.getTex2D = Resolve<FnGetD3D11Texture2D>(renderer,
                "?GetTex2D@D3D11Texture@Ogre@@QAEPAUID3D11Texture2D@@XZ");
            if (!g_ogre.getTextureManager || !g_ogre.getByName ||
                !g_ogre.release || !g_ogre.getTex2D)
            {
                g_ogre.getTex2D = nullptr;
                return false;
            }
            return true;
        }

        // Already-loaded texture by name; never loads. Borrowed result, kept
        // alive by Ogre's texture manager. No destructible locals: SEH.
        ID3D11Texture2D* FindNativeTexture(const std::string& name, const std::string& group)
        {
            ID3D11Texture2D* native = nullptr;
            __try
            {
                void* manager = g_ogre.getTextureManager();
                if (manager)
                {
                    OgreSharedPtr texture;
                    g_ogre.getByName(manager, &texture, name, group);
                    if (texture.rep)
                        native = g_ogre.getTex2D(texture.rep);
                    if (texture.rep || texture.info)
                        g_ogre.release(&texture);
                }
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return nullptr;
            }
            return native;
        }

        bool ReadFileBytes(const std::filesystem::path& path, std::vector<std::uint8_t>& out)
        {
            std::error_code ec;
            const std::uintmax_t size = std::filesystem::file_size(path, ec);
            if (ec || size == 0 || size > kMaxEnvFileBytes)
                return false;
            std::ifstream in(path, std::ios::binary);
            if (!in)
                return false;
            out.resize(static_cast<std::size_t>(size));
            in.read(reinterpret_cast<char*>(out.data()), static_cast<std::streamsize>(size));
            return in.gcount() == static_cast<std::streamsize>(size);
        }

        Status ApplyKind(KindState& state, const std::string& code,
                         const std::filesystem::path& resourceDir)
        {
            std::error_code ec;
            std::filesystem::path envFile;
            bool haveFile = false;
            if (PlanetEnvironment::IsKnownWorldCode(code))
            {
                envFile = resourceDir /
                    (std::string("openshim_env_") + code + "_" + state.kind + ".dds");
                haveFile = std::filesystem::is_regular_file(envFile, ec) && !ec;
            }
            if (!haveFile && !state.backup)
                return Status::Neutral;

            const std::string neutralName =
                std::string("openshim_ibl_neutral_") + state.kind + ".dds";
            ID3D11Texture2D* dst = FindNativeTexture(neutralName, "Autodetect");
            if (!dst)
            {
                if (!state.unavailableLogged)
                {
                    state.unavailableLogged = true;
                    LogShimA(LogLevel::Info, kComponent,
                        "[PLANET-ENV] %s texture \"%s\" not loaded or has no D3D11 resource; skipped",
                        state.kind, neutralName.c_str());
                }
                return Status::Unavailable;
            }

            D3D11_TEXTURE2D_DESC desc = {};
            dst->GetDesc(&desc);
            const bool isCube = (desc.MiscFlags & D3D11_RESOURCE_MISC_TEXTURECUBE) != 0;
            if (!isCube || desc.ArraySize != 6 ||
                !PlanetEnvironment::IsBc1DxgiFormat(static_cast<std::uint32_t>(desc.Format)))
            {
                LogShimA(LogLevel::Warn, kComponent,
                    "[PLANET-ENV] %s destination is not a BC1 cube (%ux%u mips=%u array=%u fmt=%u misc=0x%x); skipped",
                    state.kind, desc.Width, desc.Height, desc.MipLevels, desc.ArraySize,
                    static_cast<unsigned>(desc.Format), desc.MiscFlags);
                return Status::Rejected;
            }
            if (desc.Usage != D3D11_USAGE_DEFAULT)
            {
                // CopyResource only writes DEFAULT resources.
                LogShimA(LogLevel::Warn, kComponent,
                    "[PLANET-ENV] %s destination usage=%u is not DEFAULT (%s); cannot swap",
                    state.kind, static_cast<unsigned>(desc.Usage),
                    desc.Usage == D3D11_USAGE_IMMUTABLE ? "immutable" : "not copyable");
                return Status::Rejected;
            }

            if (dst != state.dst)
            {
                // Ogre recreated the texture (device reset, unload/reload):
                // the old snapshot belongs to a different resource.
                state.backup.Reset();
                state.dst = dst;
                if (!haveFile)
                    return Status::Neutral;
            }

            ComPtr<ID3D11Device> device;
            dst->GetDevice(device.GetAddressOf());
            ComPtr<ID3D11DeviceContext> context;
            if (device)
                device->GetImmediateContext(context.GetAddressOf());
            if (!device || !context)
                return Status::Failed;

            if (!haveFile)
            {
                context->CopyResource(dst, state.backup.Get());
                return Status::Restored;
            }

            std::vector<std::uint8_t> bytes;
            PlanetEnvironment::DdsCubeInfo info;
            const char* problem = nullptr;
            if (!ReadFileBytes(envFile, bytes) ||
                !PlanetEnvironment::ParseDdsCubeBc1(bytes.data(), bytes.size(), info, problem))
            {
                LogShimA(LogLevel::Warn, kComponent,
                    "[PLANET-ENV] %s \"%s\" rejected: %s", state.kind,
                    envFile.filename().string().c_str(),
                    problem ? problem : "unreadable");
                return Status::Rejected;
            }
            if (!PlanetEnvironment::DdsCubeMatchesTexture(info, desc.Width, desc.Height,
                    desc.MipLevels, desc.ArraySize, static_cast<std::uint32_t>(desc.Format), isCube))
            {
                LogShimA(LogLevel::Warn, kComponent,
                    "[PLANET-ENV] %s \"%s\" is %ux%u mips=%u but destination is %ux%u mips=%u; rejected",
                    state.kind, envFile.filename().string().c_str(), info.width, info.height,
                    info.mipLevels, desc.Width, desc.Height, desc.MipLevels);
                return Status::Rejected;
            }

            const std::uint32_t mips = info.mipLevels;
            std::vector<D3D11_SUBRESOURCE_DATA> subresources(static_cast<std::size_t>(mips) * 6);
            const std::uint8_t* cursor = bytes.data() + info.dataOffset;
            for (std::uint32_t face = 0; face < 6; ++face)
            {
                std::uint32_t w = info.width;
                std::uint32_t h = info.height;
                for (std::uint32_t mip = 0; mip < mips; ++mip)
                {
                    D3D11_SUBRESOURCE_DATA& sub = subresources[face * mips + mip];
                    sub.pSysMem = cursor;
                    sub.SysMemPitch = static_cast<UINT>(PlanetEnvironment::Bc1MipBytes(w, 1));
                    sub.SysMemSlicePitch = 0;
                    cursor += PlanetEnvironment::Bc1MipBytes(w, h);
                    w = w > 1 ? w >> 1 : 1;
                    h = h > 1 ? h >> 1 : 1;
                }
            }

            D3D11_TEXTURE2D_DESC srcDesc = desc;
            srcDesc.MipLevels = mips;
            srcDesc.Usage = D3D11_USAGE_IMMUTABLE;
            srcDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
            srcDesc.CPUAccessFlags = 0;
            srcDesc.MiscFlags = D3D11_RESOURCE_MISC_TEXTURECUBE;
            ComPtr<ID3D11Texture2D> source;
            if (FAILED(device->CreateTexture2D(&srcDesc, subresources.data(), source.GetAddressOf())))
            {
                LogShimA(LogLevel::Warn, kComponent,
                    "[PLANET-ENV] %s source texture creation failed", state.kind);
                return Status::Failed;
            }

            if (!state.backup)
            {
                D3D11_TEXTURE2D_DESC backupDesc = srcDesc;
                backupDesc.MipLevels = desc.MipLevels;
                backupDesc.Usage = D3D11_USAGE_DEFAULT;
                ComPtr<ID3D11Texture2D> backup;
                if (FAILED(device->CreateTexture2D(&backupDesc, nullptr, backup.GetAddressOf())))
                {
                    LogShimA(LogLevel::Warn, kComponent,
                        "[PLANET-ENV] %s neutral backup creation failed; not swapping", state.kind);
                    return Status::Failed;
                }
                context->CopyResource(backup.Get(), dst);
                state.backup = backup;
            }

            for (UINT face = 0; face < 6; ++face)
            {
                for (UINT mip = 0; mip < desc.MipLevels; ++mip)
                {
                    context->CopySubresourceRegion(dst,
                        D3D11CalcSubresource(mip, face, desc.MipLevels), 0, 0, 0,
                        source.Get(), D3D11CalcSubresource(mip, face, mips), nullptr);
                }
            }
            return Status::Applied;
        }

        // The D3D11 calls run on live driver objects; a fault must not take
        // the mission start down. No destructible locals in the SEH frame.
        Status ApplyKindGuarded(KindState& state, const std::string& code,
                                const std::filesystem::path& resourceDir)
        {
            Status status = Status::Failed;
            __try
            {
                status = ApplyKind(state, code, resourceDir);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return Status::Failed;
            }
            return status;
        }
    }

    void RecordTerrainWorldCodeFromAtlasPath(const std::string& path)
    {
        std::string code;
        if (!PlanetEnvironment::WorldCodeFromAtlasPath(path, code))
            return;
        {
            std::lock_guard<std::mutex> lock(g_codeMutex);
            g_worldCode = code;
        }
        g_requestGeneration.fetch_add(1);
    }

    std::string LastTerrainWorldCode()
    {
        std::lock_guard<std::mutex> lock(g_codeMutex);
        return g_worldCode;
    }

    namespace
    {
        // Returns true once there is nothing left to retry: both kinds
        // reached a final state, or the profile/renderer rules the swap out.
        bool ApplyPlanetEnvironmentNow(const bool finalAttempt)
        {
        if (RenderProfiles::Exports::GetActiveBackend() !=
                static_cast<uint32_t>(RenderProfiles::ActiveBackend::DX11) ||
            RenderProfiles::Exports::GetEffectiveRenderProfile() !=
                RenderProfiles::Abi::kProfileEnhanced ||
            RenderProfiles::IdentifyActiveRenderSystem() != 1)
        {
            return true;
        }

        static std::filesystem::path s_resourceDir;
        if (s_resourceDir.empty())
        {
            wchar_t exe[MAX_PATH] = {};
            const DWORD length = GetModuleFileNameW(nullptr, exe, MAX_PATH);
            if (length == 0 || length >= MAX_PATH)
                return true;
            std::string problem;
            if (!Assets::ProbeEnhancedResourcesAt(
                    std::filesystem::path(exe).parent_path(), problem, &s_resourceDir))
            {
                s_resourceDir.clear();
                return true;
            }
        }

        const std::string code = LastTerrainWorldCode();
        if (!ResolveOgreApi())
        {
            static bool s_logged = false;
            if (!s_logged)
            {
                s_logged = true;
                LogShimA(LogLevel::Info, kComponent,
                    "[PLANET-ENV] Ogre/D3D11 texture exports unresolved; neutral IBL kept");
            }
            return true;
        }

        const Status prefilter = ApplyKindGuarded(g_kinds[0], code, s_resourceDir);
        const Status irradiance = ApplyKindGuarded(g_kinds[1], code, s_resourceDir);
        const bool settled = prefilter != Status::Unavailable &&
                             irradiance != Status::Unavailable;
        if (settled || finalAttempt)
        {
            LogShimA(LogLevel::Info, kComponent,
                "[PLANET-ENV] world=%s prefilter=%s irradiance=%s",
                code.empty() ? "<unknown>" : code.c_str(),
                StatusName(prefilter), StatusName(irradiance));
        }
        return settled;
        }
    }

    void ApplyPlanetEnvironmentForCurrentMission()
    {
        g_requestGeneration.fetch_add(1);
    }

    void PlanetEnvironmentRenderFrameTick()
    {
        const std::uint32_t wanted = g_requestGeneration.load();
        if (wanted == g_appliedGeneration)
            return;
        if (wanted != g_pendingGeneration)
        {
            g_pendingGeneration = wanted;
            g_pendingFrames = 0;
            g_pendingAttempts = 0;
        }
        if (g_pendingFrames++ % kFramesBetweenAttempts != 0)
            return;
        const bool finalAttempt = ++g_pendingAttempts >= kMaxAttempts;
        if (ApplyPlanetEnvironmentNow(finalAttempt) || finalAttempt)
            g_appliedGeneration = wanted;
    }
}
