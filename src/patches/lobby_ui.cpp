// lobby_ui.cpp
// BZR Open Shim - multiplayer lobby UI: the flag catalogue and its engine
// upload path, GDI+ flag preview and nickname panel PNGs, the lobby widget
// cache and cUI ABI probe, flag arrows, the nickname panel and route
// readouts with the BZRNet peer route observer behind them, their engine
// callbacks and the host/client injection entry points, split out of
// bzr_hooks.cpp.
#include "bzr_hooks.h"
#include "bzr_object_layout.h"
#include "bzr_hooks_internal.h"
#include "engine_globals.h"
#include "game_state.h"
#include "openshim_ini.h"
#include "openshim_preset_migration.h"
#include "openshim_assets.h"
#include "terrain_proxy.h"
#include "terrain_tile_blend.h"
#include "bzr_options_ui.h"
#include "remembered_mesh_bounds_table.h"
#include "patches.h"
#include "patcher.h"
#include "fog_wake_feature.h"
#include "mp_vehicle_preview_fix.h"
#include "shim_log.h"
#include "x86_length.h"
#include "ogre_shader_cache.h"
#include "ogre_enhanced_light_selection.h"
#include "render_effect_intent.h"
#include "render_profile_runtime.h"
#include "native_ui.h"
#include "../engine/native_ui_validation.h"
#include "ogre_animation_profiler.h"
#include "ogre_profiler_algorithms.h"
#include "weapon_convergence.h"
#include "headlight_falloff.h"
#include "shadow_far_distance.h"
#include "sun_flash.h"
#include "chunk_batch_invalidation.h"
#include "ai_range_policy.h"
#include "lcbench_safety_policy.h"
#include "hook_engine.h"
#include "ui_performance.h"
#include "openshim_events.h"
#include "player_kill_trace.h"
#include "net_optimizer.h"
#include "pond_class_label.h"
#include <Windows.h>
#include <objidl.h>
#include <gdiplus.h>
#include <array>
#include <algorithm>
#include <cctype>
#include <cmath>
#include <intrin.h>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <climits>
#include <exception>
#include <filesystem>
#include <fstream>
#include <mutex>
#include <new>
#include <string>
#include <string_view>
#include <unordered_set>
#include <unordered_map>
#include <vector>

namespace BZROpenShim
{
    void* g_BanParentHost  = nullptr;

    void* g_BanParentClient = nullptr;

    void* g_BanButtonHost  = nullptr;

    void* g_BanButtonClient = nullptr;

    void* g_BanLabelHost   = nullptr;

    void* g_BanLabelClient = nullptr;

    void* g_FlagButtonHost = nullptr;

    void* g_FlagButtonClient = nullptr;

    void* g_FlagLabelHost = nullptr;

    void* g_FlagLabelClient = nullptr;

    // 1.5-style lobby flag preview (FlagList::BltBitmap equivalent): a
    // non-interactive tile next to the "F" button showing the selected flag.
    void* g_FlagPreviewHost = nullptr;

    void* g_FlagPreviewClient = nullptr;

    // 1.5 drove the flag catalogue with a left/right arrow pair
    // (flagLeftButton/flagRightButton, 18x19 at 90,114 and 108,114) rather than
    // one cycling button. g_FlagButton* is the left arrow; these are the right.
    void* g_FlagButtonHostRight = nullptr;

    void* g_FlagButtonClientRight = nullptr;

    // Framed cUI_TextEntry over the /nickname= buffer, and the negotiated-route readout.
    void* g_NicknamePanelHost = nullptr;

    void* g_NicknamePanelClient = nullptr;

    void* g_NicknameEntryHost = nullptr;

    void* g_NicknameEntryClient = nullptr;

    void* g_NicknameEditButtonHost = nullptr;

    void* g_NicknameEditButtonClient = nullptr;

    void* g_NicknameConfirmButtonHost = nullptr;

    void* g_NicknameConfirmButtonClient = nullptr;

    void* g_NetRouteLabelHost = nullptr;

    void* g_NetRouteLabelClient = nullptr;

    void* g_HostUiParent = nullptr;

    void* g_ClientUiParent = nullptr;

    float g_BanX = 0.0f;

    float g_BanY = 0.0f;

    namespace Hooks
    {
        void* g_ActiveNicknameEntry = nullptr;
        void* g_ActiveNicknameParent = nullptr;
        void* g_NicknameEnterDispatchEntry = nullptr;
        void* g_PendingNicknameConfirmationEntry = nullptr;
        BzrNetNicknameResult g_PendingNicknameConfirmationResult =
            BzrNetNicknameResult::StoredForNextConnection;
        bool g_ReplaceNicknameOnNextInput = false;

        // Third nickname/flag context: the multiplayer pre-lobby shell screen.
        // Its parent is the screen's centre panel, and prelobby_screen.cpp owns
        // the screen around these widgets. Nothing here outlives that panel:
        // ResetPreLobbyLobbyWidgets drops every pointer when the screen closes.
        static void* g_PreLobbyUiParent = nullptr;
        static void* g_NicknamePanelPreLobby = nullptr;
        static void* g_NicknameEntryPreLobby = nullptr;
        static void* g_NicknameEditButtonPreLobby = nullptr;
        static void* g_FlagButtonPreLobby = nullptr;
        static void* g_FlagButtonPreLobbyRight = nullptr;
        static void* g_FlagLabelPreLobby = nullptr;
        static void* g_FlagPreviewPreLobby = nullptr;

        constexpr char kFlagsConfigName[] = "flags.cfg";

        constexpr char kFlagsDirectoryName[] = "flags";

        constexpr char kFlagsGeneratedDirectoryName[] = "_generated";

        constexpr char kGeneratedFlagBmpName[] = "openshim_selected_flag.bmp";

        constexpr char kGeneratedFlagPayloadName[] = "openshim_selected_flag.bin";

        constexpr char kEngineFlagResourceRootName[] = "BZ_ASSETS";

        constexpr char kEngineFlagResourceDirectoryName[] = "OpenShimFlags";

        constexpr char kEngineFlagResourcePath[] = "OpenShimFlags/openshim_selected_flag.bmp";

        // Lobby flag preview PNGs are written into the mod-adjacent generated
        // flags dir (flags/_generated), NOT the core BZ_ASSETS_CORE tree — the
        // feature ships via the flags mod, so generated art must stay out of
        // core game folders that the mod does not own. That directory is
        // registered as an Ogre resource location so the UI texture loader can
        // still resolve the bare filename. The name is unique per flag so the
        // engine's by-name texture cache reuses the right image.
        constexpr char kFlagPreviewNamePrefix[] = "openshim_flagprev_";

        constexpr char kNicknamePanelTextureName[] = "openshim_nickname_panel.png";

        constexpr char kFlagPreviewResourceGroup[] = "General";

        constexpr int kFlagPanelFieldWidth = kFlagPreviewWidth * kFlagPreviewFieldScale;   // 192

        constexpr int kFlagPanelFieldHeight = kFlagPreviewHeight * kFlagPreviewFieldScale; // 96

        constexpr int kFlagPanelFieldPadY = 8;

        constexpr int kFlagPanelHeight =
            kFlagPanelHeaderHeight + 2 * kFlagPanelFieldPadY + kFlagPanelFieldHeight + kFlagPanelBorder; // 170

        constexpr int kFlagPanelFieldX =
            kFlagPanelBorder + (kFlagPanelWidth - 2 * kFlagPanelBorder - kFlagPanelFieldWidth) / 2;      // 24

        constexpr int kFlagPanelFieldY = kFlagPanelHeaderHeight + kFlagPanelFieldPadY;                   // 57

        constexpr int kNicknamePanelWidth = 240;

        // Header, then the entry on its own full-width row, then the OK button
        // under it. The entry had to stop sharing its row with OK: a cUI_Text
        // renders only the trailing kNicknameVisibleCharacters of its string,
        // and the width left over beside the button was ten characters.
        constexpr int kNicknamePanelHeight = 144;

        constexpr int kNicknamePanelHeaderHeight = 40;

        // Preferred substitute: a generated "preview unavailable" plate, so a
        // thumbnail that cannot be decoded reads as a deliberate placeholder
        // rather than as stray UI artwork. The stock body treats its name
        // argument as both the material name and the texture name, so this is
        // the bare filename written into the generated-UI resource location.
        static const char kInvalidThumbnailTextureName[] = "openshim_invalid_thumbnail.png";

        // 4:3, matching the shape of the stock map/campaign preview slots. The
        // material is stretched to whatever widget receives it, so this only
        // decides the rendered text's proportions, not its placement.
        constexpr int kInvalidThumbnailWidth = 256;

        constexpr int kInvalidThumbnailHeight = 192;

        constexpr float kFlagButtonSize = 48.0f;

        // Live GOG 2.2.301 flagDisplay global object. Derived on the live exe:
        // the dynamic initializer at 0x00406B80 constructs it via
        // `mov ecx, 0x9B60CC; call 0x4D1C10` (ctor stores vtable 0x00879984,
        // whose slot 8 is the verified Submit 0x004D1C80), and the net
        // player-data dispatcher at 0x00574EE5 calls a FlagDisplay method with
        // the same ecx when data slot 0x0D (the flag payload) changes.
        // FlagDisplay::PreLoad (0x004D1C50) confirms the +0x28 flagIndex /
        // +0x2C makeTexture byte offsets. The previous constant 0x006DDD34 was
        // a stale advisory-PDB address that lands inside .text on the live exe
        // (writes there raised first-chance C0000005 at 0x006DDD60).
        //
        // Both globals are engine_addresses rows (FlagDisplayInstance,
        // FlagFilePathBuffer). The instance is only written while its first
        // dword is still the FlagDisplayVtable row, so a row that drifted onto
        // something else is never written through.
        uint32_t g_FlagDisplayAddr = 0;

        uint32_t g_FlagFilePathBufferAddr = 0;

        uint32_t g_FlagDisplayVtableAddr = 0;

        bool LobbyFlagAddressesBound()
        {
            static const bool bound = [] {
                const HookEngine::EngineRow rows[] = {
                    { "FlagDisplayInstance", &g_FlagDisplayAddr },
                    { "FlagFilePathBuffer", &g_FlagFilePathBufferAddr },
                    { "FlagDisplayVtable", &g_FlagDisplayVtableAddr },
                };
                return HookEngine::BindEngineRows("Lobby flag upload", rows);
            }();
            return bound;
        }

        constexpr size_t kFlagFilePathBufferCapacity = MAX_PATH;

        constexpr size_t kFlagDisplayMakeTextureOffset = 0x2C;

        struct LegacyFlagArtifactPaths
        {
            std::filesystem::path generatedDir;
            std::filesystem::path bmpPath;
            std::filesystem::path payloadPath;
        };

        static bool g_FlagCatalogLoaded = false;

        static std::vector<FlagCatalogEntry> g_FlagCatalog;

        static std::filesystem::path g_ActiveFlagsDirectory;

        static std::filesystem::path g_ConfigRequestedFlagsDirectory;

        static std::string g_SelectedFlagFileName;

        static int g_SelectedFlagIndex = -1;

        static std::string g_SelectedFlagStatus = "Idle.";

        static std::string g_GeneratedFlagFileName;

        static std::string g_EngineStagedFlagFileName;

        static std::array<uint8_t, kLegacyFlagPayloadBytes> g_SelectedFlagPayload = {};

        static ULONG_PTR g_GdiplusToken = 0;

        static bool g_GdiplusInitialized = false;

        static std::filesystem::path GetFlagsConfigPath()
        {
            return GetConfigModuleDirectory() / kFlagsConfigName;
        }

        static std::filesystem::path GetFlagsDirectoryPath()
        {
            return GetConfigModuleDirectory() / kFlagsDirectoryName;
        }

        std::filesystem::path GetGeneratedFlagsDirectoryPath()
        {
            return GetFlagsDirectoryPath() / kFlagsGeneratedDirectoryName;
        }

        static std::filesystem::path GetEngineFlagResourceDirectoryPath()
        {
            return GetConfigModuleDirectory() /
                   kEngineFlagResourceRootName /
                   kEngineFlagResourceDirectoryName;
        }

        static std::filesystem::path GetEngineFlagResourceFilePath()
        {
            return GetEngineFlagResourceDirectoryPath() / kGeneratedFlagBmpName;
        }

        static LegacyFlagArtifactPaths GetLegacyFlagArtifactPaths()
        {
            LegacyFlagArtifactPaths paths = {};
            paths.generatedDir = GetGeneratedFlagsDirectoryPath();
            paths.bmpPath = paths.generatedDir / kGeneratedFlagBmpName;
            paths.payloadPath = paths.generatedDir / kGeneratedFlagPayloadName;
            return paths;
        }

        static bool IsSupportedFlagSourcePath(const std::filesystem::path& path)
        {
            const std::string ext = ToLowerAscii(path.extension().string());
            return ext == ".bmp" || ext == ".png" || ext == ".tga" ||
                   ext == ".jpg" || ext == ".jpeg";
        }

        static std::vector<std::filesystem::path> GetFlagDirectoryCandidates()
        {
            std::vector<std::filesystem::path> candidates;

            const auto configDir = GetConfigModuleDirectory();
            if (configDir.empty())
                return candidates;

            candidates.push_back(configDir / kFlagsDirectoryName);

            for (const auto& root : GetCampaignContentRootCandidates(configDir))
            {
                AppendUniquePath(candidates, root / kFlagsDirectoryName);
                AppendUniquePath(candidates, root / "_Release" / kFlagsDirectoryName);
                AppendUniquePath(candidates, root / "_Source" / kFlagsDirectoryName);
            }
            return candidates;
        }

        static bool DirectoryContainsSupportedFlagSources(const std::filesystem::path& directory)
        {
            if (directory.empty())
                return false;

            std::error_code ec;
            if (!std::filesystem::exists(directory, ec) || ec)
                return false;

            for (std::filesystem::directory_iterator it(directory, ec), end;
                 !ec && it != end;
                 it.increment(ec))
            {
                if (ec)
                    break;

                const auto& entry = *it;
                if (!entry.is_regular_file(ec) || ec)
                    continue;
                if (IsSupportedFlagSourcePath(entry.path()))
                    return true;
            }

            return false;
        }

        static std::filesystem::path ResolveFlagSourceDirectoryPath()
        {
            if (!g_ConfigRequestedFlagsDirectory.empty())
            {
                std::error_code ec;
                if (std::filesystem::exists(g_ConfigRequestedFlagsDirectory, ec) && !ec)
                {
                    if (DirectoryContainsSupportedFlagSources(g_ConfigRequestedFlagsDirectory))
                        return g_ConfigRequestedFlagsDirectory;

                    return g_ConfigRequestedFlagsDirectory;
                }
            }

            const auto candidates = GetFlagDirectoryCandidates();
            for (const auto& candidate : candidates)
            {
                if (DirectoryContainsSupportedFlagSources(candidate))
                    return candidate;
            }

            for (const auto& candidate : candidates)
            {
                std::error_code ec;
                if (std::filesystem::exists(candidate, ec) && !ec)
                    return candidate;
            }

            return GetFlagsDirectoryPath();
        }

        static void InvalidateFlagPayloadCache()
        {
            g_FlagPayloadReady = false;
            g_FlagApplyPending = false;
            g_GeneratedFlagFileName.clear();
            g_EngineStagedFlagFileName.clear();
            g_SelectedFlagPayload.fill(0);
        }

        static bool EnsureEngineFlagResourceStaged(const char* source, std::string& outResourcePath)
        {
            if (g_SelectedFlagIndex < 0 ||
                static_cast<size_t>(g_SelectedFlagIndex) >= g_FlagCatalog.size())
            {
                return false;
            }

            const FlagCatalogEntry& entry = g_FlagCatalog[static_cast<size_t>(g_SelectedFlagIndex)];

            outResourcePath = kEngineFlagResourcePath;
            if (g_EngineStagedFlagFileName == entry.fileName)
                return true;

            const auto generatedBmpPath = GetLegacyFlagArtifactPaths().bmpPath;
            std::error_code ec;
            std::filesystem::create_directories(GetEngineFlagResourceDirectoryPath(), ec);
            if (ec)
            {
                Log(L"[FLAG] %hs failed ensuring staged engine flag directory path=%hs ec=%d\n",
                    source ? source : "flag",
                    GetEngineFlagResourceDirectoryPath().string().c_str(),
                    static_cast<int>(ec.value()));
                return false;
            }

            ec.clear();
            std::filesystem::copy_file(
                generatedBmpPath,
                GetEngineFlagResourceFilePath(),
                std::filesystem::copy_options::overwrite_existing,
                ec);
            if (ec)
            {
                Log(L"[FLAG] %hs failed staging engine flag resource src=%hs dst=%hs ec=%d\n",
                    source ? source : "flag",
                    generatedBmpPath.string().c_str(),
                    GetEngineFlagResourceFilePath().string().c_str(),
                    static_cast<int>(ec.value()));
                return false;
            }

            g_EngineStagedFlagFileName = entry.fileName;
            Log(L"[FLAG] %hs staged engine flag resource src=%hs dst=%hs resource=%hs\n",
                source ? source : "flag",
                generatedBmpPath.string().c_str(),
                GetEngineFlagResourceFilePath().string().c_str(),
                outResourcePath.c_str());
            return true;
        }

        static bool EnsureGdiplusInitialized(std::string& error)
        {
            if (g_GdiplusInitialized)
                return true;

            Gdiplus::GdiplusStartupInput startupInput;
            const Gdiplus::Status status =
                Gdiplus::GdiplusStartup(&g_GdiplusToken, &startupInput, nullptr);
            if (status != Gdiplus::Ok)
            {
                char buffer[128] = {};
                std::snprintf(buffer, sizeof(buffer), "GDI+ startup failed (status=%d)", static_cast<int>(status));
                error = buffer;
                return false;
            }

            g_GdiplusInitialized = true;
            return true;
        }

        static bool TryBuildLegacyFlagPayloadFromSource(
            const std::filesystem::path& sourcePath,
            std::array<uint8_t, kLegacyFlagPayloadBytes>& outPayload,
            std::string& error)
        {
            error.clear();
            outPayload.fill(0);

            std::string gdiplusError;
            if (!EnsureGdiplusInitialized(gdiplusError))
            {
                error = gdiplusError;
                return false;
            }

            const std::wstring widePath = sourcePath.wstring();
            Gdiplus::Bitmap original(widePath.c_str(), FALSE);
            if (original.GetLastStatus() != Gdiplus::Ok)
            {
                char buffer[512] = {};
                std::snprintf(
                    buffer,
                    sizeof(buffer),
                    "failed to load source image '%hs' (status=%d)",
                    sourcePath.string().c_str(),
                    static_cast<int>(original.GetLastStatus()));
                error = buffer;
                return false;
            }

            Gdiplus::Bitmap scaled(kLegacyFlagWidth, kLegacyFlagHeight, PixelFormat32bppARGB);
            if (scaled.GetLastStatus() != Gdiplus::Ok)
            {
                error = "failed to allocate scaled flag surface";
                return false;
            }

            {
                Gdiplus::Graphics graphics(&scaled);
                if (graphics.GetLastStatus() != Gdiplus::Ok)
                {
                    error = "failed to create GDI+ graphics context";
                    return false;
                }

                graphics.SetCompositingMode(Gdiplus::CompositingModeSourceCopy);
                graphics.SetCompositingQuality(Gdiplus::CompositingQualityHighQuality);
                graphics.SetInterpolationMode(Gdiplus::InterpolationModeHighQualityBicubic);
                graphics.SetPixelOffsetMode(Gdiplus::PixelOffsetModeHighQuality);
                graphics.SetSmoothingMode(Gdiplus::SmoothingModeHighQuality);
                graphics.Clear(Gdiplus::Color(0, 0, 0, 0));
                graphics.DrawImage(
                    &original,
                    Gdiplus::Rect(0, 0, kLegacyFlagWidth, kLegacyFlagHeight),
                    0,
                    0,
                    static_cast<INT>(original.GetWidth()),
                    static_cast<INT>(original.GetHeight()),
                    Gdiplus::UnitPixel);
            }

            struct PixelSample
            {
                uint8_t alpha;
                uint8_t luminance;
            };

            PixelSample samples[kLegacyFlagHeight][kLegacyFlagWidth] = {};
            int opaqueCount = 0;
            int darkCount = 0;
            for (int y = 0; y < kLegacyFlagHeight; ++y)
            {
                for (int x = 0; x < kLegacyFlagWidth; ++x)
                {
                    Gdiplus::Color color;
                    if (scaled.GetPixel(x, y, &color) != Gdiplus::Ok)
                    {
                        error = "failed reading scaled flag pixels";
                        return false;
                    }

                    const uint8_t alpha = color.GetA();
                    const uint8_t luminance = static_cast<uint8_t>(
                        ((299u * color.GetR()) + (587u * color.GetG()) + (114u * color.GetB())) / 1000u);
                    samples[y][x] = { alpha, luminance };
                    if (alpha >= 64)
                    {
                        ++opaqueCount;
                        if (luminance < 200)
                            ++darkCount;
                    }
                }
            }

            const bool useAlphaOnly = (opaqueCount > 0) && (darkCount == 0);
            int enabledPixels = 0;
            for (int bmpRow = 0; bmpRow < kLegacyFlagHeight; ++bmpRow)
            {
                const int sourceY = (kLegacyFlagHeight - 1) - bmpRow;
                for (int x = 0; x < kLegacyFlagWidth; ++x)
                {
                    const PixelSample sample = samples[sourceY][x];
                    bool enabled = false;
                    if (useAlphaOnly)
                        enabled = sample.alpha >= 64;
                    else
                        enabled = sample.alpha >= 64 && sample.luminance < 200;

                    if (!enabled)
                        continue;

                    ++enabledPixels;
                    outPayload[static_cast<size_t>(bmpRow) * kLegacyFlagRowBytes + static_cast<size_t>(x / 8)] |=
                        static_cast<uint8_t>(0x80u >> (x & 7));
                }
            }

            if (enabledPixels == 0)
            {
                error = "source image converted to an empty mask";
                return false;
            }

            return true;
        }

        static bool WriteLegacyFlagBitmap(
            const std::filesystem::path& outputPath,
            const std::array<uint8_t, kLegacyFlagPayloadBytes>& payload,
            std::string& error)
        {
            error.clear();

            std::error_code ec;
            std::filesystem::create_directories(outputPath.parent_path(), ec);
            if (ec)
            {
                char buffer[256] = {};
                std::snprintf(buffer, sizeof(buffer), "failed to create output directory (%d)", static_cast<int>(ec.value()));
                error = buffer;
                return false;
            }

            FILE* file = nullptr;
            if (fopen_s(&file, outputPath.string().c_str(), "wb") != 0 || !file)
            {
                error = "failed to create generated BMP";
                return false;
            }

            unsigned char header[62] = {};
            auto write16 = [&header](size_t offset, uint16_t value)
            {
                header[offset + 0] = static_cast<unsigned char>(value & 0xFFu);
                header[offset + 1] = static_cast<unsigned char>((value >> 8) & 0xFFu);
            };
            auto write32 = [&header](size_t offset, uint32_t value)
            {
                header[offset + 0] = static_cast<unsigned char>(value & 0xFFu);
                header[offset + 1] = static_cast<unsigned char>((value >> 8) & 0xFFu);
                header[offset + 2] = static_cast<unsigned char>((value >> 16) & 0xFFu);
                header[offset + 3] = static_cast<unsigned char>((value >> 24) & 0xFFu);
            };

            header[0] = 'B';
            header[1] = 'M';
            write32(2, 62u + static_cast<uint32_t>(payload.size()));
            write32(10, 62u);
            write32(14, 40u);
            write32(18, kLegacyFlagWidth);
            write32(22, kLegacyFlagHeight);
            write16(26, 1u);
            write16(28, 1u);
            write32(34, static_cast<uint32_t>(payload.size()));
            write32(38, 2835u);
            write32(42, 2835u);
            write32(46, 2u);
            write32(50, 2u);

            // Palette: 0 = white, 1 = black. The engine only copies the bits.
            header[54] = 0xFF; header[55] = 0xFF; header[56] = 0xFF; header[57] = 0x00;
            header[58] = 0x00; header[59] = 0x00; header[60] = 0x00; header[61] = 0x00;

            const bool headerWritten = std::fwrite(header, 1, sizeof(header), file) == sizeof(header);
            const bool payloadWritten = std::fwrite(payload.data(), 1, payload.size(), file) == payload.size();
            std::fclose(file);

            if (!headerWritten || !payloadWritten)
            {
                error = "failed while writing generated BMP";
                return false;
            }

            return true;
        }

        static bool WriteLegacyFlagPayloadBin(
            const std::filesystem::path& outputPath,
            const std::array<uint8_t, kLegacyFlagPayloadBytes>& payload,
            std::string& error)
        {
            error.clear();

            FILE* file = nullptr;
            if (fopen_s(&file, outputPath.string().c_str(), "wb") != 0 || !file)
            {
                error = "failed to create generated payload";
                return false;
            }

            const bool written = std::fwrite(payload.data(), 1, payload.size(), file) == payload.size();
            std::fclose(file);
            if (!written)
            {
                error = "failed while writing generated payload";
                return false;
            }

            return true;
        }

        static void MarkFlagDisplayDirty()
        {
            if (!LobbyFlagAddressesBound())
                return;
            auto* flagDisplay = reinterpret_cast<uint8_t*>(g_FlagDisplayAddr);

            __try
            {
                if (*reinterpret_cast<const uint32_t*>(flagDisplay) != g_FlagDisplayVtableAddr)
                    return;
                // Redux never assigns the legacy atlas index, but its own
                // CheckFlags path still uses this byte as the change signal.
                // Our Ogre renderer polls the same network payload directly.
                *(flagDisplay + kFlagDisplayMakeTextureOffset) = 1;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                Log(L"[FLAG] Failed to mark flag display dirty at 0x%08X\n", g_FlagDisplayAddr);
            }
        }

        bool TryGetLocalPlayerForFlags(void*& outPlayer)
        {
            outPlayer = nullptr;
            if (!g_BzrFn_GetLocalPlayerNetId || !g_BzrFn_BanLookup)
                return false;

            __try
            {
                const uint16_t localPlayerId = g_BzrFn_GetLocalPlayerNetId();
                outPlayer = g_BzrFn_BanLookup(localPlayerId);
                return outPlayer != nullptr;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
            }

            outPlayer = nullptr;
            return false;
        }

        static void SortFlagCatalog()
        {
            std::sort(
                g_FlagCatalog.begin(),
                g_FlagCatalog.end(),
                [](const FlagCatalogEntry& a, const FlagCatalogEntry& b)
                {
                    return _stricmp(a.displayName.c_str(), b.displayName.c_str()) < 0;
                });
        }

        static bool SaveSelectedFlagConfig()
        {
            const auto configPath = GetFlagsConfigPath();
            const std::string configPathString = configPath.string();
            FILE* file = nullptr;
            if (fopen_s(&file, configPathString.c_str(), "w") != 0 || !file)
            {
                Log(L"[FLAG] Failed to write flag config path=%hs\n", configPathString.c_str());
                return false;
            }

            std::fprintf(file, "; OpenShim multiplayer vehicle flag selection\n");
            std::fprintf(file, "; Place source images in .\\flags\\ and click the lobby F button to cycle.\n");
            std::fprintf(file, "; Supported source formats: .bmp .png .tga .jpg .jpeg\n");
            std::fprintf(file, "selected=%s\n", g_SelectedFlagFileName.c_str());
            if (!g_ConfigRequestedFlagsDirectory.empty())
                std::fprintf(file, "sourceDir=%s\n", g_ConfigRequestedFlagsDirectory.string().c_str());
            if (!g_ActiveFlagsDirectory.empty())
                std::fprintf(file, "; activeSourceDir=%s\n", g_ActiveFlagsDirectory.string().c_str());
            if (!g_GeneratedFlagFileName.empty())
                std::fprintf(file, "; generatedFor=%s\n", g_GeneratedFlagFileName.c_str());
            std::fclose(file);
            Log(L"[FLAG] Wrote flag config path=%hs selected=%hs sourceDir=%hs activeDir=%hs\n",
                configPathString.c_str(),
                g_SelectedFlagFileName.c_str(),
                g_ConfigRequestedFlagsDirectory.empty() ? "" : g_ConfigRequestedFlagsDirectory.string().c_str(),
                g_ActiveFlagsDirectory.empty() ? "" : g_ActiveFlagsDirectory.string().c_str());
            return true;
        }

        static void SyncSelectedFlagIndex()
        {
            g_SelectedFlagIndex = -1;
            if (g_FlagCatalog.empty())
            {
                g_SelectedFlagFileName.clear();
                return;
            }

            if (!g_SelectedFlagFileName.empty())
            {
                for (size_t i = 0; i < g_FlagCatalog.size(); ++i)
                {
                    if (_stricmp(g_FlagCatalog[i].fileName.c_str(), g_SelectedFlagFileName.c_str()) == 0)
                    {
                        g_SelectedFlagIndex = static_cast<int>(i);
                        return;
                    }
                }
            }

            g_SelectedFlagIndex = 0;
            g_SelectedFlagFileName = g_FlagCatalog.front().fileName;
        }

        static void EnsureFlagCatalogLoaded()
        {
            if (g_FlagCatalogLoaded)
                return;

            g_FlagCatalogLoaded = true;
            g_FlagCatalog.clear();
            g_ActiveFlagsDirectory.clear();
            g_ConfigRequestedFlagsDirectory.clear();
            g_SelectedFlagFileName.clear();
            g_SelectedFlagIndex = -1;
            g_SelectedFlagStatus = "Idle.";
            InvalidateFlagPayloadCache();

            const auto primaryFlagsDir = GetFlagsDirectoryPath();
            std::error_code ec;
            std::filesystem::create_directories(primaryFlagsDir, ec);
            if (ec)
            {
                Log(L"[FLAG] Failed to ensure flags directory path=%hs ec=%d\n",
                    primaryFlagsDir.string().c_str(),
                    static_cast<int>(ec.value()));
            }

            const auto configPath = GetFlagsConfigPath();
            FILE* file = nullptr;
            if (fopen_s(&file, configPath.string().c_str(), "r") == 0 && file)
            {
                char line[512] = {};
                while (std::fgets(line, static_cast<int>(sizeof(line)), file))
                {
                    char* trimmed = TrimAsciiInPlace(line);
                    if (*trimmed == '\0' || *trimmed == '#' || *trimmed == ';')
                        continue;

                    char* equals = std::strchr(trimmed, '=');
                    if (!equals)
                        continue;

                    *equals = '\0';
                    char* key = TrimAsciiInPlace(trimmed);
                    char* value = TrimAsciiInPlace(equals + 1);
                    if (_stricmp(key, "selected") == 0 && value && *value)
                    {
                        g_SelectedFlagFileName = value;
                    }
                    else if ((_stricmp(key, "sourceDir") == 0 ||
                              _stricmp(key, "sourcePath") == 0) &&
                             value && *value)
                    {
                        g_ConfigRequestedFlagsDirectory = value;
                    }
                }

                std::fclose(file);
            }

            if (!g_ConfigRequestedFlagsDirectory.empty())
            {
                std::error_code overrideError;
                if (!std::filesystem::exists(g_ConfigRequestedFlagsDirectory, overrideError) || overrideError)
                {
                    Log(L"[FLAG] Config sourceDir does not exist path=%hs\n",
                        g_ConfigRequestedFlagsDirectory.string().c_str());
                    g_SelectedFlagStatus = "Configured dir missing; using fallback.";
                    g_ConfigRequestedFlagsDirectory.clear();
                }
                else
                {
                    Log(L"[FLAG] Config requested source directory path=%hs\n",
                        g_ConfigRequestedFlagsDirectory.string().c_str());
                }
            }

            const auto flagsDir = ResolveFlagSourceDirectoryPath();
            g_ActiveFlagsDirectory = flagsDir;
            if (!flagsDir.empty() && flagsDir != primaryFlagsDir)
            {
                Log(L"[FLAG] Using fallback flag source directory path=%hs primary=%hs\n",
                    flagsDir.string().c_str(),
                    primaryFlagsDir.string().c_str());
            }
            for (std::filesystem::directory_iterator it(flagsDir, ec), end;
                 !ec && it != end;
                 it.increment(ec))
            {
                if (ec)
                    break;

                const auto& entry = *it;
                if (!entry.is_regular_file(ec) || ec)
                    continue;
                if (!IsSupportedFlagSourcePath(entry.path()))
                    continue;

                FlagCatalogEntry catalogEntry = {};
                catalogEntry.fileName = entry.path().filename().string();
                catalogEntry.displayName = entry.path().stem().string();
                catalogEntry.sourcePath = entry.path();
                g_FlagCatalog.push_back(std::move(catalogEntry));
            }

            SortFlagCatalog();
            SyncSelectedFlagIndex();

            if (g_FlagCatalog.empty())
            {
                if (!g_ConfigRequestedFlagsDirectory.empty())
                    g_SelectedFlagStatus = "No images in flags folder.";
                else
                    g_SelectedFlagStatus = "No images in flags folder.";
                SaveSelectedFlagConfig();
                Log(L"[FLAG] No flag source files found. Checked primary=%hs active=%hs requested=%hs\n",
                    primaryFlagsDir.string().c_str(),
                    flagsDir.string().c_str(),
                    g_ConfigRequestedFlagsDirectory.empty() ? "" : g_ConfigRequestedFlagsDirectory.string().c_str());
                return;
            }

            SaveSelectedFlagConfig();
            Log(L"[FLAG] Loaded flag catalog path=%hs entries=%u selected=%hs requested=%hs\n",
                flagsDir.string().c_str(),
                static_cast<unsigned>(g_FlagCatalog.size()),
                g_SelectedFlagFileName.c_str(),
                g_ConfigRequestedFlagsDirectory.empty() ? "" : g_ConfigRequestedFlagsDirectory.string().c_str());
        }

        static const FlagCatalogEntry* GetSelectedFlagEntry()
        {
            EnsureFlagCatalogLoaded();
            if (g_SelectedFlagIndex < 0 ||
                static_cast<size_t>(g_SelectedFlagIndex) >= g_FlagCatalog.size())
            {
                return nullptr;
            }
            return &g_FlagCatalog[static_cast<size_t>(g_SelectedFlagIndex)];
        }

        static bool TryGenerateSelectedFlagArtifacts(const char* source)
        {
            const FlagCatalogEntry* entry = GetSelectedFlagEntry();
            if (!entry)
            {
                g_SelectedFlagStatus = "No images in flags folder.";
                return false;
            }

            if (g_FlagPayloadReady &&
                _stricmp(g_GeneratedFlagFileName.c_str(), entry->fileName.c_str()) == 0)
            {
                Log(L"[FLAG] %hs reused cached generated artifacts source=%hs\n",
                    source ? source : "flag",
                    entry->sourcePath.string().c_str());
                return true;
            }

            std::array<uint8_t, kLegacyFlagPayloadBytes> payload = {};
            std::string error;
            if (!TryBuildLegacyFlagPayloadFromSource(entry->sourcePath, payload, error))
            {
                g_SelectedFlagStatus = "Conversion failed; see log.";
                Log(L"[FLAG] %hs failed converting source path=%hs error=%hs\n",
                    source ? source : "flag",
                    entry->sourcePath.string().c_str(),
                    error.c_str());
                return false;
            }

            const LegacyFlagArtifactPaths paths = GetLegacyFlagArtifactPaths();
            if (!WriteLegacyFlagBitmap(paths.bmpPath, payload, error))
            {
                g_SelectedFlagStatus = "BMP write failed; see log.";
                Log(L"[FLAG] %hs failed writing BMP path=%hs error=%hs\n",
                    source ? source : "flag",
                    paths.bmpPath.string().c_str(),
                    error.c_str());
                return false;
            }

            if (!WriteLegacyFlagPayloadBin(paths.payloadPath, payload, error))
            {
                g_SelectedFlagStatus = "Payload write failed; see log.";
                Log(L"[FLAG] %hs failed writing payload path=%hs error=%hs\n",
                    source ? source : "flag",
                    paths.payloadPath.string().c_str(),
                    error.c_str());
                return false;
            }

            g_SelectedFlagPayload = payload;
            g_GeneratedFlagFileName = entry->fileName;
            g_FlagPayloadReady = true;
            g_FlagApplyPending = true;
            g_SelectedFlagStatus = "Applies at match start.";
            Log(L"[FLAG] %hs generated legacy artifacts source=%hs bmp=%hs payload=%hs\n",
                source ? source : "flag",
                entry->sourcePath.string().c_str(),
                paths.bmpPath.string().c_str(),
                paths.payloadPath.string().c_str());
            return true;
        }

        static bool TryApplySelectedFlagThroughEnginePath(const char* source, const char* path)
        {
            if (!LobbyFlagAddressesBound())
            {
                g_SelectedFlagStatus = "Flag upload unavailable on this build.";
                return false;
            }
            // The destination is a fixed MAX_PATH engine global, so the length
            // has to be enforced here rather than trusted from the call site.
            // The one current caller does check, but a silent overrun of an
            // engine global would corrupt unrelated state instead of faulting,
            // which the surrounding __try would not catch.
            if (!path)
                return false;

            const size_t pathLength = std::strlen(path);
            if (pathLength >= kFlagFilePathBufferCapacity)
            {
                Log(L"[FLAG] %hs refusing engine upload: path is %zu bytes, buffer holds %zu\n",
                    source ? source : "flag",
                    pathLength,
                    kFlagFilePathBufferCapacity);
                return false;
            }

            __try
            {
                auto* pathBuffer = reinterpret_cast<char*>(g_FlagFilePathBufferAddr);
                std::memset(pathBuffer, 0, kFlagFilePathBufferCapacity);
                std::memcpy(pathBuffer, path, pathLength);
                g_BzrFn_SetMyFlag();
                MarkFlagDisplayDirty();

                void* localPlayer = nullptr;
                const bool haveLocalPlayer = TryGetLocalPlayerForFlags(localPlayer);
                const void* flagBuffer =
                    haveLocalPlayer && localPlayer
                    ? *reinterpret_cast<void**>(reinterpret_cast<uint8_t*>(localPlayer) + 0x1C)
                    : nullptr;
                const int flagIndex =
                    haveLocalPlayer && localPlayer
                    ? *reinterpret_cast<int*>(reinterpret_cast<uint8_t*>(localPlayer) + 0x50)
                    : -1;

                if (flagBuffer)
                {
                    g_SelectedFlagStatus = "Uploaded.";
                    g_FlagApplyPending = false;
                }
                else
                {
                    g_SelectedFlagStatus = "Applies at match start.";
                    g_FlagApplyPending = true;
                }

                Log(L"[FLAG] %hs engine apply path=%hs player=0x%p flagBuf=0x%p flagIndex=%d\n",
                    source ? source : "flag",
                    path,
                    localPlayer,
                    flagBuffer,
                    flagIndex);
                return flagBuffer != nullptr;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                g_SelectedFlagStatus = "Engine apply failed; see log.";
                g_FlagApplyPending = true;
                Log(L"[FLAG] %hs engine apply raised an exception path=%hs\n",
                    source ? source : "flag",
                    path ? path : "");
                return false;
            }
        }

        bool TryApplySelectedFlagThroughEngine(const char* source)
        {
            const FlagCatalogEntry* entry = GetSelectedFlagEntry();
            if (!entry)
            {
                g_SelectedFlagStatus = "No images in flags folder.";
                return false;
            }

            if (!g_BzrFn_SetMyFlag)
            {
                g_SelectedFlagStatus = "Applies at match start.";
                g_FlagApplyPending = true;
                return false;
            }

            if (!TryGenerateSelectedFlagArtifacts(source))
                return false;

            std::string path;
            if (!EnsureEngineFlagResourceStaged(source, path))
                path = entry->sourcePath.string();

            if (path.empty() || path.size() >= kFlagFilePathBufferCapacity)
            {
                g_SelectedFlagStatus = "Flag path too long for engine upload.";
                g_FlagApplyPending = true;
                return false;
            }

            return TryApplySelectedFlagThroughEnginePath(source, path.c_str());
        }

        bool TryApplyCachedFlagPayload(const char* source)
        {
            if (!g_FlagPayloadReady)
                return false;

            if (!g_BzrFn_GetLocalPlayerNetId ||
                !g_BzrFn_BanLookup ||
                !g_BzrFn_NetPlayerSetData ||
                !g_BzrFn_NetPlayerSetFlagBuffer)
            {
                g_SelectedFlagStatus = "Apply helpers unavailable.";
                g_FlagApplyPending = true;
                return false;
            }

            __try
            {
                void* localPlayer = nullptr;
                if (!TryGetLocalPlayerForFlags(localPlayer))
                {
                    g_SelectedFlagStatus = "Applies at match start.";
                    g_FlagApplyPending = true;
                    return false;
                }

                g_BzrFn_NetPlayerSetFlagBuffer(
                    localPlayer,
                    g_SelectedFlagPayload.data(),
                    static_cast<uint32_t>(g_SelectedFlagPayload.size()));
                g_BzrFn_NetPlayerSetData(
                    localPlayer,
                    kLegacyFlagDataSlot,
                    g_SelectedFlagPayload.data(),
                    static_cast<uint32_t>(g_SelectedFlagPayload.size()));
                MarkFlagDisplayDirty();
                g_SelectedFlagStatus = "Uploaded.";
                g_FlagApplyPending = false;
                Log(L"[FLAG] %hs applied legacy fallback payload bytes=%u slot=0x%02X player=0x%p\n",
                    source ? source : "flag",
                    static_cast<unsigned>(g_SelectedFlagPayload.size()),
                    static_cast<unsigned>(kLegacyFlagDataSlot),
                    localPlayer);
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                g_SelectedFlagStatus = "Apply failed; see log.";
                g_FlagApplyPending = true;
                Log(L"[FLAG] %hs apply raised an exception\n", source ? source : "flag");
                return false;
            }
        }

        static void PrimeSelectedFlagForTesting(const char* source)
        {
            if (!TryGenerateSelectedFlagArtifacts(source))
                return;

            // In the lobby (pre-session) there is no local NetPlayer object
            // yet, so both apply paths can only fail: the legacy fallback
            // needs the player object and the engine SetMyFlag path leaves
            // the flag buffer empty. Skip quietly and let the in-game
            // ui_create/ui_update pass upload once the player exists instead
            // of surfacing a scary-looking failure status in the lobby UI.
            void* localPlayer = nullptr;
            if (!TryGetLocalPlayerForFlags(localPlayer))
            {
                g_SelectedFlagStatus = "Applies at match start.";
                g_FlagApplyPending = true;
                return;
            }

            // Redux's SetMyFlag exits when slot 0x0D already exists, which
            // prevents a later lobby selection from replacing the first flag.
            // The shim path deliberately overwrites both the local cache and
            // the replicated data slot on every selection change.
            if (TryApplyCachedFlagPayload(source))
                return;

            TryApplySelectedFlagThroughEngine(source);
        }

        static void SelectFlagEntryByIndex(int index, const char* source)
        {
            EnsureFlagCatalogLoaded();
            if (g_FlagCatalog.empty())
            {
                Log(L"[FLAG] %hs ignored because no flag files are available\n",
                    source ? source : "flag");
                return;
            }

            const int count = static_cast<int>(g_FlagCatalog.size());
            if (index < 0)
                index = (count - 1);
            else if (index >= count)
                index = 0;

            const std::string previousSelection = g_SelectedFlagFileName;
            g_SelectedFlagIndex = index;
            g_SelectedFlagFileName = g_FlagCatalog[static_cast<size_t>(index)].fileName;
            if (_stricmp(previousSelection.c_str(), g_SelectedFlagFileName.c_str()) != 0)
            {
                InvalidateFlagPayloadCache();
                g_SelectedFlagStatus = "Applies at match start.";
            }
            SaveSelectedFlagConfig();
            Log(L"[FLAG] %hs selected index=%d file=%hs path=%hs\n",
                source ? source : "flag",
                index,
                g_SelectedFlagFileName.c_str(),
                g_FlagCatalog[static_cast<size_t>(index)].sourcePath.string().c_str());
        }

        // --- Negotiated peer route readout -------------------------------------
        // Redux chooses each peer's gameplay path itself (LAN UDP -> direct WAN
        // UDP -> BZRNet relay) and announces the outcome, but never surfaces it
        // anywhere the player can see. The peer records are only reachable
        // through opaque STL iteration inside FUN_0075D800, so instead of
        // walking that container we observe the two announcements the engine
        // already makes, at their single call sites.
        //
        // Both sites push their arguments and call the shared BZRNet logger
        // (BzrNetLogger row; cdecl, 272 call sites across the image). Redirecting one
        // `call` rel32 -- rather than detouring the logger itself -- means each
        // hook receives a fixed, known signature instead of varargs, and no
        // other log line in the game is affected. Each format string below has
        // exactly one push site in .text, so there is no ambiguity about which
        // call is being redirected.
        //
        //   0x0075ED1D  logger(fmt, route, name, address)
        //     fmt @ 0x0089BC78 "BZRNet P2P Completed %s Connect For Client %s,
        //                       using address %s\n"
        //     route is the literal "LAN" / "WAN" / "RELAY" the engine selected
        //     from the peer state at peer+0x00 (2 = LAN, 4 = WAN, 7 = RELAY).
        //   0x0075EF99  logger(fmt, name)
        //     fmt @ 0x0089BCBC "BZRNet P2P Fully Resetting Connection Status
        //                       For Client %s\n"
        //
        // The logger and both call sites are rows; RedirectCallTarget still
        // requires each call to target the logger row before it rewrites it.
        uint32_t g_BzrNetLoggerAddr = 0;
        uint32_t g_BzrNetRouteCompletedCallAddr = 0;
        uint32_t g_BzrNetRouteResetCallAddr = 0;

        struct BzrNetPeerRoute
        {
            std::string name;
            std::string route;   // "LAN", "WAN" or "RELAY"
            std::string address;
        };

        // Written from the BZRNet worker thread, read from the UI thread.
        static std::mutex g_BzrNetRouteMutex;
        static std::vector<BzrNetPeerRoute> g_BzrNetPeerRoutes;
        static bool g_BzrNetRouteObserverInstalled = false;

        // The engine hands us raw char* it owns. Copy defensively in a function
        // with no unwindable objects (__try and object unwinding cannot share a
        // function -- C2712).
        static bool CopyEngineCString(const char* src, char* out, size_t outSize)
        {
            if (!out || outSize == 0)
                return false;
            out[0] = '\0';
            if (!src)
                return false;
            __try
            {
                size_t i = 0;
                for (; i + 1 < outSize && src[i] != '\0'; ++i)
                    out[i] = src[i];
                out[i] = '\0';
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                out[0] = '\0';
            }
            return false;
        }

        static void RecordBzrNetPeerRoute(const char* name, const char* route, const char* address)
        {
            char nameBuf[128] = {};
            char routeBuf[16] = {};
            char addressBuf[80] = {};
            if (!CopyEngineCString(name, nameBuf, sizeof(nameBuf)) || nameBuf[0] == '\0')
                return;
            CopyEngineCString(route, routeBuf, sizeof(routeBuf));
            CopyEngineCString(address, addressBuf, sizeof(addressBuf));

            bool changed = false;
            {
                std::lock_guard<std::mutex> lock(g_BzrNetRouteMutex);
                auto it = std::find_if(
                    g_BzrNetPeerRoutes.begin(), g_BzrNetPeerRoutes.end(),
                    [&](const BzrNetPeerRoute& entry) { return entry.name == nameBuf; });
                if (it == g_BzrNetPeerRoutes.end())
                {
                    g_BzrNetPeerRoutes.push_back({ nameBuf, routeBuf, addressBuf });
                    changed = true;
                }
                else
                {
                    changed = (it->route != routeBuf);
                    it->route = routeBuf;
                    it->address = addressBuf;
                }
            }

            if (changed)
            {
                Log(L"[BZRNET] Peer route client=%hs route=%hs address=%hs\n",
                    nameBuf, routeBuf[0] ? routeBuf : "?", addressBuf);
            }
        }

        static void ForgetBzrNetPeerRoute(const char* name)
        {
            char nameBuf[128] = {};
            if (!CopyEngineCString(name, nameBuf, sizeof(nameBuf)) || nameBuf[0] == '\0')
                return;

            std::lock_guard<std::mutex> lock(g_BzrNetRouteMutex);
            g_BzrNetPeerRoutes.erase(
                std::remove_if(g_BzrNetPeerRoutes.begin(), g_BzrNetPeerRoutes.end(),
                               [&](const BzrNetPeerRoute& entry) { return entry.name == nameBuf; }),
                g_BzrNetPeerRoutes.end());
        }

        // Compact route-only status plus the bound UDP port. Peer names made
        // this narrow sidebar caption unreadable as soon as a platform ID or a
        // moderately long nickname appeared.
        static void FormatBzrNetRouteSummary(char* out, size_t outSize)
        {
            if (!out || outSize == 0)
                return;

            std::string summary;
            {
                std::lock_guard<std::mutex> lock(g_BzrNetRouteMutex);
                for (const BzrNetPeerRoute& entry : g_BzrNetPeerRoutes)
                {
                    const std::string route = entry.route.empty() ? "?" : entry.route;
                    const bool alreadyShown =
                        summary == route ||
                        summary.find(route + "/") == 0 ||
                        summary.find("/" + route) != std::string::npos;
                    if (!alreadyShown)
                    {
                        if (!summary.empty())
                            summary.push_back('/');
                        summary += route;
                    }
                }
            }

            const int port = GetBzrNetUdpPort();
            char portText[32] = {};
            if (port > 0)
                std::snprintf(portText, sizeof(portText), " %d", port);

            if (summary.empty())
            {
                std::snprintf(out, outSize, "Net: idle%s%s",
                              IsBzrNetForceRelayActive() ? "/relay" : "",
                              portText);
                return;
            }

            std::snprintf(out, outSize, "Net: %.12s%s",
                          summary.c_str(), portText);
        }

        using FnBzrNetLogger = void(__cdecl*)(const char* fmt, ...);

        // Observe, then forward to the real logger with the identical arguments
        // so the game's own log is unchanged. Both are __cdecl: the engine's
        // call site cleans its own pushes, so these must not.
        static void __cdecl BzrNetRouteCompletedLogHook(const char* fmt,
                                                        const char* route,
                                                        const char* name,
                                                        const char* address)
        {
            RecordBzrNetPeerRoute(name, route, address);
            reinterpret_cast<FnBzrNetLogger>(g_BzrNetLoggerAddr)(fmt, route, name, address);
        }

        static void __cdecl BzrNetRouteResetLogHook(const char* fmt, const char* name)
        {
            ForgetBzrNetPeerRoute(name);
            reinterpret_cast<FnBzrNetLogger>(g_BzrNetLoggerAddr)(fmt, name);
        }

        void InstallBzrNetRouteObserverIfPossible()
        {
            if (g_BzrNetRouteObserverInstalled)
                return;
            static const bool s_bound = [] {
                const HookEngine::EngineRow rows[] = {
                    { "BzrNetLogger", &g_BzrNetLoggerAddr },
                    { "BzrNetRouteCompletedLogCall", &g_BzrNetRouteCompletedCallAddr },
                    { "BzrNetRouteResetLogCall", &g_BzrNetRouteResetCallAddr },
                };
                return HookEngine::BindEngineRows("BZRNet peer route observer", rows);
            }();
            if (!s_bound)
                return;

            const bool completed = RedirectCallTarget(
                g_BzrNetRouteCompletedCallAddr,
                g_BzrNetLoggerAddr,
                reinterpret_cast<uintptr_t>(&BzrNetRouteCompletedLogHook));
            const bool reset = RedirectCallTarget(
                g_BzrNetRouteResetCallAddr,
                g_BzrNetLoggerAddr,
                reinterpret_cast<uintptr_t>(&BzrNetRouteResetLogHook));

            g_BzrNetRouteObserverInstalled = completed && reset;
            Log(L"[BZRNET] Peer route observer: %hs (completed=%hs reset=%hs)\n",
                g_BzrNetRouteObserverInstalled ? "installed" : "unavailable",
                completed ? "ok" : "mismatch",
                reset ? "ok" : "mismatch");
        }
    }

    using namespace Hooks;

    namespace Hooks
    {
        // Widgets built by the cUI_TextEntry / cUI_Selectlist ABI probe below.
        static void* g_ProbeTextEntry = nullptr;
        static void* g_ProbeSelectlist = nullptr;

        static void ResetHostUiCache()
        {
            if (g_ActiveNicknameEntry == g_NicknameEntryHost)
            {
                g_ActiveNicknameEntry = nullptr;
                g_ActiveNicknameParent = nullptr;
                g_ReplaceNicknameOnNextInput = false;
            }
            if (g_NicknameEnterDispatchEntry == g_NicknameEntryHost)
                g_NicknameEnterDispatchEntry = nullptr;
            if (g_PendingNicknameConfirmationEntry == g_NicknameEntryHost)
                g_PendingNicknameConfirmationEntry = nullptr;
            g_BanButtonHost = nullptr;
            g_BanLabelHost = nullptr;
            g_FlagButtonHost = nullptr;
            g_FlagButtonHostRight = nullptr;
            g_FlagLabelHost = nullptr;
            g_FlagPreviewHost = nullptr;
            g_NicknamePanelHost = nullptr;
            g_NicknameEntryHost = nullptr;
            g_NicknameEditButtonHost = nullptr;
            g_NicknameConfirmButtonHost = nullptr;
            g_NetRouteLabelHost = nullptr;
            g_ProbeTextEntry = nullptr;
            g_ProbeSelectlist = nullptr;
        }

        static void ResetClientUiCache()
        {
            if (g_ActiveNicknameEntry == g_NicknameEntryClient)
            {
                g_ActiveNicknameEntry = nullptr;
                g_ActiveNicknameParent = nullptr;
                g_ReplaceNicknameOnNextInput = false;
            }
            if (g_NicknameEnterDispatchEntry == g_NicknameEntryClient)
                g_NicknameEnterDispatchEntry = nullptr;
            if (g_PendingNicknameConfirmationEntry == g_NicknameEntryClient)
                g_PendingNicknameConfirmationEntry = nullptr;
            g_BanButtonClient = nullptr;
            g_BanLabelClient = nullptr;
            g_FlagButtonClient = nullptr;
            g_FlagButtonClientRight = nullptr;
            g_FlagLabelClient = nullptr;
            g_FlagPreviewClient = nullptr;
            g_NicknamePanelClient = nullptr;
            g_NicknameEntryClient = nullptr;
            g_NicknameEditButtonClient = nullptr;
            g_NicknameConfirmButtonClient = nullptr;
            g_NetRouteLabelClient = nullptr;
        }

        static void* CachedLobbyOwner(bool host)
        {
            return host ? g_HostUiParent : g_ClientUiParent;
        }

        static void InvalidateLobbyUiCache(bool host, const char* source)
        {
            void*& cachedParent = host ? g_HostUiParent : g_ClientUiParent;
            void* const oldParent = cachedParent;
            void* const oldRouteLabel = host
                ? g_NetRouteLabelHost
                : g_NetRouteLabelClient;
            if (host)
                ResetHostUiCache();
            else
                ResetClientUiCache();
            cachedParent = nullptr;
            Log(L"[BZRNET] LobbyUiCacheInvalidated side=%hs source=%hs "
                L"owner=0x%08X route-label=0x%08X\n",
                host ? "host" : "client",
                source ? source : "unknown",
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(oldParent)),
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(oldRouteLabel)));
        }

        static void EnsureUiCacheMatchesParent(void* parent, bool host)
        {
            if (!parent)
                return;

            void*& cachedParent = host ? g_HostUiParent : g_ClientUiParent;
            if (cachedParent == parent)
                return;

            cachedParent = parent;
            if (host)
                ResetHostUiCache();
            else
                ResetClientUiCache();
        }

        // Strongest liveness proof available without a per-screen dtor hook: a
        // cached child widget is only trusted if the live parent's child vector
        // (+0x12C begin / +0x130 end, same layout the stock-button finder walks)
        // still contains it. A screen rebuilt at a recycled heap address fills a
        // fresh vector, so a stale cached pointer fails this check and the
        // widget is recreated instead of being updated through freed memory.
        bool IsWidgetLiveChildOfParent(void* parent, void* widget)
        {
            if (!parent || !widget)
                return false;

            __try
            {
                auto* const parentBytes = reinterpret_cast<uint8_t*>(parent);
                void** const begin = *reinterpret_cast<void***>(parentBytes + 0x12C);
                void** const end = *reinterpret_cast<void***>(parentBytes + 0x130);
                if (!begin || !end || begin > end || (end - begin) > 1024)
                    return false;
                for (void** it = begin; it != end; ++it)
                {
                    if (*it == widget)
                        return true;
                }
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
            }
            return false;
        }

        static bool CachedLobbyWidgetIsLive(bool host,
                                            void* widget,
                                            const char* source)
        {
            void* const parent = host ? g_HostUiParent : g_ClientUiParent;
            const bool ownerContainsChild = parent && widget &&
                IsWidgetLiveChildOfParent(parent, widget);
            if (NativeUiValidation::CachedChildAccessAllowed(
                    parent != nullptr, widget != nullptr, ownerContainsChild))
            {
                return true;
            }

            if (parent || widget)
                InvalidateLobbyUiCache(host, source);
            return false;
        }

        // ---- cUI_TextEntry / cUI_Selectlist ABI probe ----
        //
        // Stands up one of each on the lobby through the same allocate + ctor +
        // AddChild sequence the ban and flag buttons use, then reads back the
        // fields the two ctors are known to initialise. Sizes and offsets come
        // from this build's own code rather than the reference PDB (see
        // bzr_options_ui.h), so the read-back is a real test of the binding: if
        // an argument were misplaced, maxLength and mAllowEnter would not
        // survive the trip, and the vtable pointer would not match.
        //
        // Off by default. Set OPENSHIM_UI_WIDGET_PROBE=1 to build the widgets
        // and write the results to the log.
        // The read-back identifies each widget's vtable by RTTI name.
        constexpr const char* kUiTextEntryTypeName = ".?AVcUI_TextEntry@@";
        constexpr const char* kUiSelectlistTypeName = ".?AVcUI_Selectlist@@";

        static bool ShouldRunUiWidgetProbe()
        {
            static int s_cached = -1;
            if (s_cached < 0)
                s_cached = EnvFlagEnabled("OPENSHIM_UI_WIDGET_PROBE") ? 1 : 0;
            return s_cached != 0;
        }

        static bool ReadWidgetDword(const void* widget, size_t offset, uint32_t& out)
        {
            if (!widget)
                return false;
            __try
            {
                out = *reinterpret_cast<const uint32_t*>(
                    static_cast<const uint8_t*>(widget) + offset);
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
            }
            return false;
        }

        // MSVC std::string: 16-byte inline buffer, length at +0x10, capacity at
        // +0x14, and the buffer becomes a pointer once capacity exceeds 15.
        static bool ReadEngineStdString(const void* str, char* out, size_t outSize)
        {
            if (!str || !out || outSize == 0)
                return false;

            out[0] = '\0';
            __try
            {
                const uint8_t* const bytes = static_cast<const uint8_t*>(str);
                const size_t length = *reinterpret_cast<const size_t*>(bytes + 0x10);
                const size_t capacity = *reinterpret_cast<const size_t*>(bytes + 0x14);
                if (length > capacity || capacity > 0x10000)
                    return false;

                const char* const chars = (capacity < 16)
                    ? reinterpret_cast<const char*>(bytes)
                    : *reinterpret_cast<const char* const*>(bytes);
                if (!chars)
                    return false;

                const size_t copy = (length < outSize - 1) ? length : outSize - 1;
                std::memcpy(out, chars, copy);
                out[copy] = '\0';
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
            }
            return false;
        }

        // The Selectlist ctor installs these as the click callbacks of the two
        // arrow buttons it builds for itself; the engine calls them through
        // +0x154 with no arguments.
        static void __cdecl UiWidgetProbePageUp()
        {
        }

        static void __cdecl UiWidgetProbePageDown()
        {
        }

        static void ReportProbeTextEntry(void* widget)
        {
            uint32_t vtable = 0;
            uint32_t maxLength = 0;
            uint32_t allowEnter = 0;
            char text[64] = {};

            const bool haveVtable = ReadWidgetDword(widget, 0, vtable);
            ReadWidgetDword(widget, kUiTextEntryMaxLengthOffset, maxLength);
            ReadWidgetDword(widget, kUiTextEntryAllowEnterOffset, allowEnter);
            const bool haveText = ReadEngineStdString(
                static_cast<uint8_t*>(widget) + kUiTextEntryTextOffset, text, sizeof(text));

            Log(L"[UIPROBE] cUI_TextEntry ptr=%p vtable=0x%08X(want %hs %hs) "
                L"maxLength=%u(want 36 %hs) allowEnter=%u(want 1 %hs) text=\"%hs\"(%hs)\n",
                widget,
                haveVtable ? vtable : 0,
                kUiTextEntryTypeName,
                (haveVtable && VtableTypeNameMatches(vtable, kUiTextEntryTypeName)) ? "ok" : "MISMATCH",
                maxLength,
                maxLength == 0x24 ? "ok" : "MISMATCH",
                allowEnter & 0xFF,
                (allowEnter & 0xFF) == 1 ? "ok" : "MISMATCH",
                text,
                haveText ? "readable" : "UNREADABLE");
        }

        static void ReportProbeSelectlist(void* widget)
        {
            uint32_t vtable = 0;
            uint32_t selected = 0;
            uint32_t scroll = 0;
            uint32_t pageUp = 0;
            uint32_t pageDown = 0;

            const bool haveVtable = ReadWidgetDword(widget, 0, vtable);
            ReadWidgetDword(widget, kUiSelectlistSelectedOffset, selected);
            ReadWidgetDword(widget, kUiSelectlistScrollOffset, scroll);
            ReadWidgetDword(widget, kUiSelectlistPageUpOffset, pageUp);
            ReadWidgetDword(widget, kUiSelectlistPageDownOffset, pageDown);

            Log(L"[UIPROBE] cUI_Selectlist ptr=%p vtable=0x%08X(want %hs %hs) "
                L"selected=%d(want -1 %hs) scroll=%u pageUp=0x%08X pageDown=0x%08X(%hs)\n",
                widget,
                haveVtable ? vtable : 0,
                kUiSelectlistTypeName,
                (haveVtable && VtableTypeNameMatches(vtable, kUiSelectlistTypeName)) ? "ok" : "MISMATCH",
                static_cast<int>(selected),
                static_cast<int>(selected) == -1 ? "ok" : "MISMATCH",
                scroll,
                pageUp,
                pageDown,
                (pageUp && pageDown) ? "arrows built" : "ARROWS MISSING");
        }

        static void CreateUiWidgetProbe(void* parent)
        {
            if (!parent || !g_BzrFn_AddChild || !g_BzrFn_TextEntryCtor || !g_BzrFn_SelectlistCtor)
                return;

            if (!g_ProbeTextEntry || !IsWidgetLiveChildOfParent(parent, g_ProbeTextEntry))
            {
                g_ProbeTextEntry = nullptr;
                void* const mem = ::operator new(kUiTextEntrySize, std::nothrow);
                if (mem)
                {
                    std::memset(mem, 0, kUiTextEntrySize);
                    // Geometry follows the stock "chatEntry" row (520x40 at
                    // y=945), lifted clear of it. 0x8020 is the flag word every
                    // shipped text entry passes; maxLength 0x24 matches chatEntry.
                    g_ProbeTextEntry = g_BzrFn_TextEntryCtor(
                        mem, 0, 1, 0x24, "OpenShimProbeEntry",
                        470.0f, 872.0f, 520.0f, 40.0f, 0x8020, parent);
                    if (g_ProbeTextEntry)
                    {
                        g_BzrFn_AddChild(parent, g_ProbeTextEntry, 0);
                        ReportProbeTextEntry(g_ProbeTextEntry);
                    }
                    else
                    {
                        // A ctor that returned null may still have run far
                        // enough to own resources, so the block is leaked
                        // rather than freed under a half-built engine object.
                        Log(L"[UIPROBE] cUI_TextEntry ctor returned null\n");
                    }
                }
            }

            if (!g_ProbeSelectlist || !IsWidgetLiveChildOfParent(parent, g_ProbeSelectlist))
            {
                g_ProbeSelectlist = nullptr;
                void* const mem = ::operator new(kUiSelectlistSize, std::nothrow);
                if (mem)
                {
                    std::memset(mem, 0, kUiSelectlistSize);
                    // Colour and row scale are the values every stock list
                    // passes. The ctor pre-creates row labels to fill the
                    // height, so it is safe to construct with no items.
                    g_ProbeSelectlist = g_BzrFn_SelectlistCtor(
                        mem, "OpenShimProbeList",
                        60.0f, 560.0f, 380.0f, 240.0f,
                        reinterpret_cast<void*>(UiWidgetProbePageUp),
                        reinterpret_cast<void*>(UiWidgetProbePageDown),
                        0, parent, 0xFF00FF00, 1.0f);
                    if (g_ProbeSelectlist)
                    {
                        g_BzrFn_AddChild(parent, g_ProbeSelectlist, 0);

                        // SetItem appends whenever index == size(), so walking
                        // the index up from zero fills an empty list.
                        if (g_BzrFn_SelectlistSetItem)
                        {
                            static const char* const kRows[] = {
                                "TCP/IP", "IPX", "Modem", "Serial", "Local Area Network"
                            };
                            constexpr int kRowCount = static_cast<int>(sizeof(kRows) / sizeof(kRows[0]));
                            for (int i = 0; i < kRowCount; ++i)
                                g_BzrFn_SelectlistSetItem(g_ProbeSelectlist, kRows[i], i, 100 + i);
                        }

                        ReportProbeSelectlist(g_ProbeSelectlist);
                    }
                    else
                    {
                        Log(L"[UIPROBE] cUI_Selectlist ctor returned null\n");
                    }
                }
            }
        }

        static void UpdateFlagSelectionUiLabel(void* label)
        {
            if (g_FlagApplyPending)
            {
                // Only attempt the upload once a local NetPlayer exists;
                // pre-session lobby attempts always fail and would replace
                // the status text with a failure message.
                void* localPlayer = nullptr;
                if (TryGetLocalPlayerForFlags(localPlayer))
                {
                    if (!TryApplyCachedFlagPayload("ui_update"))
                        TryApplySelectedFlagThroughEngine("ui_update");
                }
                else
                {
                    g_SelectedFlagStatus = "Applies at match start.";
                }
            }

            if (!label || !g_BzrFn_SetTooltip)
                return;

            char summary[32] = {};
            std::snprintf(
                summary,
                sizeof(summary),
                "%d/%u",
                g_SelectedFlagIndex + 1,
                static_cast<unsigned>(g_FlagCatalog.size()));
            g_BzrFn_SetTooltip(label, summary);
        }

        static std::filesystem::path GetFlagPreviewUiDirectory()
        {
            return GetGeneratedFlagsDirectoryPath();
        }

        // Register the generated-flags directory as a FileSystem resource
        // location in the UI texture group once, so SetTextureOff can resolve
        // the preview PNG by bare name from a mod-owned folder instead of the
        // core UI tree. Best-effort: if Ogre is not ready the preview simply
        // will not show (cosmetic), and the write path stays out of core.
        static void EnsureFlagPreviewResourceLocationRegistered()
        {
            static bool s_Registered = false;
            if (s_Registered)
                return;

            auto getResourceGroupManager = ResolveOgreProc<FnOgreGetResourceGroupManager>(
                "?getSingletonPtr@ResourceGroupManager@Ogre@@SAPAV12@XZ");
            auto addResourceLocation = ResolveOgreProc<FnOgreAddResourceLocation>(
                "?addResourceLocation@ResourceGroupManager@Ogre@@QAEXABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@00_N1@Z");
            // Both exports exist in the shipped OgreMain.dll with exactly these
            // mangled names, so a failure here means the module was not loaded
            // yet, not that the symbol is absent.
            if (!getResourceGroupManager || !addResourceLocation)
            {
                static bool s_LoggedResolveFailure = false;
                if (!s_LoggedResolveFailure)
                {
                    s_LoggedResolveFailure = true;
                    Log(L"[FLAG] preview resource location: Ogre exports unresolved "
                        L"(getSingletonPtr=%hs addResourceLocation=%hs)\n",
                        getResourceGroupManager ? "ok" : "null",
                        addResourceLocation ? "ok" : "null");
                }
                return;
            }

            const std::string dir = GetFlagPreviewUiDirectory().string();
            const std::string type = "FileSystem";
            const std::string group = kFlagPreviewResourceGroup;
            std::error_code ec;
            std::filesystem::create_directories(dir, ec);

            try
            {
                void* manager = getResourceGroupManager();
                if (!manager)
                {
                    Log(L"[FLAG] preview resource location: ResourceGroupManager singleton is null\n");
                    return;
                }
                addResourceLocation(manager, dir, type, group, false, false);
            }
            catch (...)
            {
                // Ogre throws on an unknown group or a duplicate location, and
                // the std::string arguments cross a toolset boundary (OgreMain
                // is MSVC120, OpenShim is v143), so swallowing this silently
                // hid the failure entirely.
                Log(L"[FLAG] preview resource location: addResourceLocation threw dir=%hs group=%hs\n",
                    dir.c_str(), group.c_str());
                return;
            }

            s_Registered = true;
            Log(L"[FLAG] registered lobby preview resource location dir=%hs group=%hs\n",
                dir.c_str(), group.c_str());
        }

        static std::string SanitizeForFileName(const std::string& value)
        {
            std::string out;
            out.reserve(value.size());
            for (char ch : value)
            {
                const unsigned char uch = static_cast<unsigned char>(ch);
                out.push_back(std::isalnum(uch) ? static_cast<char>(std::tolower(uch)) : '_');
            }
            if (out.empty())
                out = "flag";
            return out;
        }

        // Bare texture name (no directory) the UI loader resolves from
        // common/ui. Unique per source flag so the engine's texture cache maps
        // each flag to its own preview image.
        static std::string GetSelectedFlagPreviewName()
        {
            const FlagCatalogEntry* entry = GetSelectedFlagEntry();
            if (!entry)
                return std::string();
            std::filesystem::path stem = std::filesystem::path(entry->fileName).stem();
            return std::string(kFlagPreviewNamePrefix) + SanitizeForFileName(stem.string()) + ".png";
        }

        static bool GetPngEncoderClsid(CLSID& outClsid)
        {
            UINT count = 0;
            UINT bytes = 0;
            if (Gdiplus::GetImageEncodersSize(&count, &bytes) != Gdiplus::Ok || bytes == 0)
                return false;
            std::vector<uint8_t> buffer(bytes);
            auto* encoders = reinterpret_cast<Gdiplus::ImageCodecInfo*>(buffer.data());
            if (Gdiplus::GetImageEncoders(count, bytes, encoders) != Gdiplus::Ok)
                return false;
            for (UINT i = 0; i < count; ++i)
            {
                if (encoders[i].MimeType && wcscmp(encoders[i].MimeType, L"image/png") == 0)
                {
                    outClsid = encoders[i].Clsid;
                    return true;
                }
            }
            return false;
        }

        // Draw the "preview unavailable" plate the thumbnail guard substitutes
        // for an image the shipped FreeImage cannot decode. Deliberately looks
        // like a message rather than art: a flat dark field, the same green
        // chrome edge the injected lobby panel uses, and two lines of text.
        static bool WriteInvalidThumbnailPng(const std::filesystem::path& outPath)
        {
            std::string gdiplusError;
            if (!EnsureGdiplusInitialized(gdiplusError))
            {
                Log(L"[BMPFIX] placeholder GDI+ init failed: %hs\n", gdiplusError.c_str());
                return false;
            }

            Gdiplus::Bitmap bitmap(kInvalidThumbnailWidth,
                                   kInvalidThumbnailHeight,
                                   PixelFormat32bppARGB);
            if (bitmap.GetLastStatus() != Gdiplus::Ok)
                return false;

            {
                Gdiplus::Graphics gfx(&bitmap);
                gfx.SetSmoothingMode(Gdiplus::SmoothingModeNone);
                gfx.SetPixelOffsetMode(Gdiplus::PixelOffsetModeHalf);
                gfx.SetTextRenderingHint(Gdiplus::TextRenderingHintSingleBitPerPixelGridFit);

                Gdiplus::SolidBrush edgeDark(Gdiplus::Color(255, 0, 42, 0));
                Gdiplus::SolidBrush edgeMid(Gdiplus::Color(255, 0, 84, 0));
                Gdiplus::SolidBrush field(Gdiplus::Color(255, 8, 10, 8));

                gfx.FillRectangle(&edgeDark, 0, 0, kInvalidThumbnailWidth, kInvalidThumbnailHeight);
                gfx.FillRectangle(&edgeMid, 2, 2,
                                  kInvalidThumbnailWidth - 4, kInvalidThumbnailHeight - 4);
                gfx.FillRectangle(&field, 5, 5,
                                  kInvalidThumbnailWidth - 10, kInvalidThumbnailHeight - 10);

                Gdiplus::StringFormat format;
                format.SetAlignment(Gdiplus::StringAlignmentCenter);
                format.SetLineAlignment(Gdiplus::StringAlignmentCenter);
                format.SetFormatFlags(Gdiplus::StringFormatFlagsNoWrap);

                const auto textWidth = static_cast<float>(kInvalidThumbnailWidth - 20);
                Gdiplus::Font headline(L"Lucida Console", 18.0f,
                                       Gdiplus::FontStyleBold, Gdiplus::UnitPixel);
                Gdiplus::SolidBrush headlineBrush(Gdiplus::Color(255, 64, 220, 64));
                const Gdiplus::RectF headlineBox(
                    10.0f,
                    static_cast<float>(kInvalidThumbnailHeight) * 0.34f,
                    textWidth,
                    26.0f);
                gfx.DrawString(L"PREVIEW", -1, &headline, headlineBox, &format, &headlineBrush);
                const Gdiplus::RectF headlineBox2(
                    10.0f,
                    static_cast<float>(kInvalidThumbnailHeight) * 0.34f + 22.0f,
                    textWidth,
                    26.0f);
                gfx.DrawString(L"UNAVAILABLE", -1, &headline, headlineBox2, &format, &headlineBrush);

                // Says why, so an author who supplied the image knows it is
                // their file and not a missing one.
                Gdiplus::Font detail(L"Lucida Console", 11.0f,
                                     Gdiplus::FontStyleRegular, Gdiplus::UnitPixel);
                Gdiplus::SolidBrush detailBrush(Gdiplus::Color(255, 0, 140, 0));
                const Gdiplus::RectF detailBox(
                    10.0f,
                    static_cast<float>(kInvalidThumbnailHeight) * 0.34f + 52.0f,
                    textWidth,
                    18.0f);
                gfx.DrawString(L"invalid image format", -1, &detail, detailBox, &format, &detailBrush);
            }

            CLSID pngClsid = {};
            if (!GetPngEncoderClsid(pngClsid))
                return false;
            std::error_code ec;
            std::filesystem::create_directories(outPath.parent_path(), ec);
            const Gdiplus::Status saved =
                bitmap.Save(outPath.wstring().c_str(), &pngClsid, nullptr);
            if (saved != Gdiplus::Ok)
            {
                Log(L"[BMPFIX] placeholder PNG save failed path=%hs status=%d\n",
                    outPath.string().c_str(), static_cast<int>(saved));
                return false;
            }
            return true;
        }

        // Forward-declared up beside the thumbnail guard, which is the only
        // caller. Answers with the bare texture name once the plate exists in
        // a resource location the UI texture loader searches.
        //
        // The generated-flags directory is reused as that location: it is the
        // one OpenShim-owned FileSystem location already registered into the
        // UI texture group, and duplicating that registration is the fragile
        // part (it resolves Ogre exports across a toolset boundary), not the
        // directory choice. Nothing here depends on the flags feature being
        // enabled -- the registration helper creates the directory itself.
        //
        // Best-effort by construction: every failure returns nullptr and the
        // guard falls through to its original "UI" substitute, so a missing
        // placeholder is cosmetic and never reintroduces the crash.
        const char* EnsureInvalidThumbnailTextureName()
        {
            static bool s_Attempted = false;
            static bool s_Available = false;

            if (s_Attempted)
                return s_Available ? kInvalidThumbnailTextureName : nullptr;
            s_Attempted = true;

            EnsureFlagPreviewResourceLocationRegistered();

            // Rewritten once per process rather than kept if present, so a
            // plate generated by an older build cannot outlive its art. If the
            // write fails but a readable plate is already there, that one is
            // still better than falling through to the stock UI material.
            const std::filesystem::path outPath =
                GetFlagPreviewUiDirectory() / kInvalidThumbnailTextureName;
            if (!WriteInvalidThumbnailPng(outPath))
            {
                std::error_code ec;
                if (!std::filesystem::exists(outPath, ec))
                    return nullptr;
                Log(L"[BMPFIX] placeholder regeneration failed; reusing existing plate path=%hs\n",
                    outPath.string().c_str());
            }

            s_Available = true;
            Log(L"[BMPFIX] placeholder thumbnail ready name=%hs path=%hs\n",
                kInvalidThumbnailTextureName,
                outPath.string().c_str());
            return kInvalidThumbnailTextureName;
        }

        // Render the packed 64x32 1-bpp flag mask into a PNG the lobby widget
        // can display: black where a bit is set, over the red field used by
        // Battlezone 1.5, inside a titled panel drawn in Redux's own lobby
        // chrome. Row order mirrors the
        // bottom-up legacy payload so the preview is upright like the source.
        // The field is nearest-neighbour tripled here rather than left to the
        // GPU, which would filter the 1-bpp mask into mush.
        static bool WriteFlagPreviewPng(
            const std::array<uint8_t, kLegacyFlagPayloadBytes>& payload,
            const std::string& title,
            const std::filesystem::path& outPath)
        {
            std::string gdiplusError;
            if (!EnsureGdiplusInitialized(gdiplusError))
            {
                Log(L"[FLAG] preview GDI+ init failed: %hs\n", gdiplusError.c_str());
                return false;
            }

            Gdiplus::Bitmap bitmap(kFlagPanelWidth, kFlagPanelHeight, PixelFormat32bppARGB);
            if (bitmap.GetLastStatus() != Gdiplus::Ok)
                return false;

            {
                Gdiplus::Graphics gfx(&bitmap);
                gfx.SetSmoothingMode(Gdiplus::SmoothingModeNone);
                gfx.SetPixelOffsetMode(Gdiplus::PixelOffsetModeHalf);
                gfx.SetTextRenderingHint(Gdiplus::TextRenderingHintSingleBitPerPixelGridFit);

                Gdiplus::SolidBrush edgeDark(Gdiplus::Color(255, 0, 42, 0));
                Gdiplus::SolidBrush edgeBright(Gdiplus::Color(255, 0, 127, 0));
                Gdiplus::SolidBrush edgeMid(Gdiplus::Color(255, 0, 84, 0));
                Gdiplus::SolidBrush field(Gdiplus::Color(255, 0, 0, 0));

                // Border, drawn as nested fills so the profile above reads in
                // source order from outside in.
                gfx.FillRectangle(&edgeDark, 0, 0, kFlagPanelWidth, kFlagPanelHeight);
                gfx.FillRectangle(&edgeBright, 3, 3, kFlagPanelWidth - 6, kFlagPanelHeight - 6);
                gfx.FillRectangle(&edgeMid, 5, 5, kFlagPanelWidth - 10, kFlagPanelHeight - 10);
                gfx.FillRectangle(&edgeDark, 7, 7, kFlagPanelWidth - 14, kFlagPanelHeight - 14);

                const int inner = kFlagPanelWidth - 2 * kFlagPanelBorder;
                gfx.FillRectangle(
                    &field,
                    kFlagPanelBorder,
                    kFlagPanelHeaderHeight,
                    inner,
                    kFlagPanelHeight - kFlagPanelBorder - kFlagPanelHeaderHeight);

                // Rule under the header band.
                gfx.FillRectangle(&edgeBright, kFlagPanelBorder, 40, inner, 4);
                gfx.FillRectangle(&edgeMid, kFlagPanelBorder, 44, inner, 3);
                gfx.FillRectangle(&edgeDark, kFlagPanelBorder, 47, inner, 2);

                if (!title.empty())
                {
                    std::wstring wide(title.begin(), title.end());
                    Gdiplus::Font font(L"Lucida Console", 13.0f, Gdiplus::FontStyleBold, Gdiplus::UnitPixel);
                    Gdiplus::StringFormat format;
                    format.SetAlignment(Gdiplus::StringAlignmentCenter);
                    format.SetLineAlignment(Gdiplus::StringAlignmentCenter);
                    format.SetTrimming(Gdiplus::StringTrimmingEllipsisCharacter);
                    format.SetFormatFlags(Gdiplus::StringFormatFlagsNoWrap);
                    Gdiplus::SolidBrush text(Gdiplus::Color(255, 64, 220, 64));
                    const Gdiplus::RectF layout(
                        static_cast<float>(kFlagPanelBorder),
                        9.0f,
                        static_cast<float>(inner),
                        30.0f);
                    gfx.DrawString(wide.c_str(), -1, &font, layout, &format, &text);
                }
            }

            for (int y = 0; y < kFlagPreviewHeight; ++y)
            {
                const int payloadRow = (kLegacyFlagHeight - 1) - y;
                for (int x = 0; x < kFlagPreviewWidth; ++x)
                {
                    const uint8_t packed = payload[
                        static_cast<size_t>(payloadRow) * kLegacyFlagRowBytes +
                        static_cast<size_t>(x / 8)];
                    const bool on = (packed & static_cast<uint8_t>(0x80u >> (x & 7))) != 0;
                    // Opaque now that there is a panel around it: a translucent
                    // field let the menu art through and made the panel look
                    // like it was floating over nothing.
                    const Gdiplus::Color color = on
                        ? Gdiplus::Color(255, 0, 0, 0)
                        : Gdiplus::Color(255, 232, 31, 18);
                    for (int sy = 0; sy < kFlagPreviewFieldScale; ++sy)
                    {
                        for (int sx = 0; sx < kFlagPreviewFieldScale; ++sx)
                        {
                            bitmap.SetPixel(
                                kFlagPanelFieldX + x * kFlagPreviewFieldScale + sx,
                                kFlagPanelFieldY + y * kFlagPreviewFieldScale + sy,
                                color);
                        }
                    }
                }
            }

            CLSID pngClsid = {};
            if (!GetPngEncoderClsid(pngClsid))
            {
                Log(L"[FLAG] preview PNG encoder unavailable\n");
                return false;
            }

            std::error_code ec;
            std::filesystem::create_directories(outPath.parent_path(), ec);
            const Gdiplus::Status saved = bitmap.Save(outPath.wstring().c_str(), &pngClsid, nullptr);
            if (saved != Gdiplus::Ok)
            {
                Log(L"[FLAG] preview PNG save failed path=%hs status=%d\n",
                    outPath.string().c_str(), static_cast<int>(saved));
                return false;
            }
            return true;
        }

        // Ensure the preview PNG for the current selection exists on disk and
        // return its bare texture name (empty on failure). Generated once per
        // flag per session.
        static std::string EnsureSelectedFlagPreviewImage()
        {
            const std::string name = GetSelectedFlagPreviewName();
            if (name.empty())
                return std::string();
            if (!g_FlagPayloadReady)
                return std::string();

            const std::filesystem::path outPath = GetFlagPreviewUiDirectory() / name;
            static std::string s_LastPreviewName;
            std::error_code ec;
            if (name == s_LastPreviewName && std::filesystem::exists(outPath, ec))
                return name;

            // The panel header carries both the flag name and the position in
            // the catalogue. Keeping the counter in the texture removes the
            // old label below the arrows, where it collided with the lobby's
            // bottom Options strip.
            std::string title;
            if (const FlagCatalogEntry* entry = GetSelectedFlagEntry())
            {
                char compactTitle[96] = {};
                std::snprintf(
                    compactTitle,
                    sizeof(compactTitle),
                    "%s  %d/%u",
                    entry->displayName.c_str(),
                    g_SelectedFlagIndex + 1,
                    static_cast<unsigned>(g_FlagCatalog.size()));
                title = compactTitle;
            }
            for (char& ch : title)
                ch = static_cast<char>(std::toupper(static_cast<unsigned char>(ch)));
            if (title.empty())
                title = "FLAGS";

            if (!WriteFlagPreviewPng(g_SelectedFlagPayload, title, outPath))
                return std::string();
            s_LastPreviewName = name;
            Log(L"[FLAG] wrote lobby preview name=%hs path=%hs\n",
                name.c_str(), outPath.string().c_str());
            return name;
        }

        static void UpdateFlagPreviewWidget(void* widget)
        {
            if (!widget)
                return;
            EnsureFlagPreviewResourceLocationRegistered();
            const std::string name = EnsureSelectedFlagPreviewImage();
            if (name.empty())
                return;
            if (g_BzrFn_SetTextureOff) g_BzrFn_SetTextureOff(widget, name.c_str());
            if (g_BzrFn_SetTextureOver) g_BzrFn_SetTextureOver(widget, name.c_str());
            if (g_BzrFn_SetTextureOn) g_BzrFn_SetTextureOn(widget, name.c_str());
        }

        // 1.5 shell pixels scale onto the 1440x1080 Redux canvas by a single
        // uniform 2.25 factor (both are 4:3), so the arrow pair keeps its retail
        // proportions: flagLeftButton/flagRightButton are 18x19 at 90,114 and
        // 108,114, i.e. 40.5x42.75 side by side with no gap.
        // A literal 2.25x of the retail 18x19 arrows gives 40.5x42.75, which
        // measured too small to use against Redux's own chrome and -- at 81px
        // for the pair -- overran the 56px of clearance before the Ban button.
        // Keep the retail 18:19 aspect but size the pair to the stock Redux
        // button instead, and give the cluster its own room (see the call sites).
        constexpr float kFlagArrowWidth = kFlagButtonSize;                 // 48
        constexpr float kFlagArrowHeight = kFlagButtonSize * (19.0f / 18.0f); // ~50.7
        constexpr float kFlagArrowGap = 4.0f;
        // The panel is authored at the canvas resolution it is displayed on, so
        // it goes up 1:1 -- any scale here would resample chrome that was
        // measured in screen pixels.
        constexpr float kFlagPreviewDisplayWidth = static_cast<float>(kFlagPanelWidth);   // 224
        constexpr float kFlagPreviewDisplayHeight = static_cast<float>(kFlagPanelHeight); // 170
        constexpr float kFlagPreviewGap = 8.0f;
        static void CreateFlagButtonCommon(
            void* parent,
            float x,
            float y,
            void** outButton,
            void** outButtonRight,
            void** outLabel,
            void** outPreview,
            void* onClickLeft,
            void* onClickRight,
            void* onHover)
        {
            // Both callback slots must be set on an active dialog child (see
            // below), so the setters are required up front.
            if (!parent || !outButton || !outLabel || !g_BzrFn_ButtonCtor || !g_BzrFn_LabelCtor || !g_BzrFn_AddChild ||
                !g_BzrFn_SetOnClick || !g_BzrFn_SetOnHover)
                return;

            EnsureFlagCatalogLoaded();
            PrimeSelectedFlagForTesting("ui_create");
            *outLabel = nullptr;

            // The 1.5 pair, in place of the single cycling "F" button. The retail
            // arrows are bitmaps 2049/2050/2070/2071; until those are extracted
            // the stock Redux button art carries a "<" / ">" caption, which keeps
            // the widget legible without inventing a texture.
            struct FlagArrowSpec
            {
                void** out;
                const char* name;
                const char* caption;
                float offsetX;
                void* onClick;
            };
            const FlagArrowSpec arrows[] =
            {
                { outButton,      "Flag Prev", "<", 0.0f,                               onClickLeft },
                { outButtonRight, "Flag Next", ">", kFlagArrowWidth + kFlagArrowGap,    onClickRight },
            };

            for (const FlagArrowSpec& arrow : arrows)
            {
                if (!arrow.out)
                    continue;

                void* buttonMem = ::operator new(0x1EC, std::nothrow);
                if (!buttonMem)
                    return;
                std::memset(buttonMem, 0, 0x1EC);

                *arrow.out = g_BzrFn_ButtonCtor(
                    buttonMem,
                    arrow.name,
                    x + arrow.offsetX,
                    y,
                    kFlagArrowWidth,
                    kFlagArrowHeight,
                    0x20,
                    parent,
                    0,
                    0);
                if (!*arrow.out)
                    continue;

                if (g_BzrFn_SetTextureOff) g_BzrFn_SetTextureOff(*arrow.out, "MultiplayerModeButton_off.png");
                if (g_BzrFn_SetTextureOver) g_BzrFn_SetTextureOver(*arrow.out, "MultiplayerModeButton_over.png");
                if (g_BzrFn_SetTextureOn) g_BzrFn_SetTextureOn(*arrow.out, "MultiplayerModeButton_on.png");
                if (g_BzrFn_SetButtonLabel) g_BzrFn_SetButtonLabel(*arrow.out, arrow.caption);
                // Both callback slots must be non-null on an active dialog child
                // or the lobby crashes walking its children (see AutoSave note).
                if (g_BzrFn_SetOnClick) g_BzrFn_SetOnClick(*arrow.out, arrow.onClick);
                if (g_BzrFn_SetOnHover) g_BzrFn_SetOnHover(*arrow.out, onHover);
                g_BzrFn_AddChild(parent, *arrow.out, 0);
            }

            const float previewY = y - kFlagPreviewDisplayHeight - kFlagPreviewGap;

            // 1.5-style preview tile showing the selected flag, placed just
            // above the arrow pair. It reuses the forward callback, so clicking
            // the preview advances like the right arrow, and — critically —
            // both +0x150/+0x154 callback slots stay non-null (a null slot on
            // an active dialog child crashes when the lobby walks its children;
            // see the AutoSave button note).
            void* const onClick = onClickRight;
            if (outPreview && g_BzrFn_ButtonCtor)
            {
                void* previewMem = ::operator new(0x1EC, std::nothrow);
                if (previewMem)
                {
                    std::memset(previewMem, 0, 0x1EC);
                    // The payload is a fixed 64x32 legacy flag mask, so the PNG
                    // stays at payload resolution (plus its plate) and only the
                    // widget is scaled up -- at 1:1 it was too small to read
                    // against Redux's chrome.
                    *outPreview = g_BzrFn_ButtonCtor(
                        previewMem,
                        "Flag Preview",
                        x,
                        previewY,
                        kFlagPreviewDisplayWidth,
                        kFlagPreviewDisplayHeight,
                        0x20,
                        parent,
                        0,
                        0);
                    if (*outPreview)
                    {
                        UpdateFlagPreviewWidget(*outPreview);
                        if (g_BzrFn_SetOnClick && onClick) g_BzrFn_SetOnClick(*outPreview, onClick);
                        if (g_BzrFn_SetOnHover && onHover) g_BzrFn_SetOnHover(*outPreview, onHover);
                        g_BzrFn_AddChild(parent, *outPreview, 0);
                    }
                }
            }
        }

        // Refresh the negotiated-route readout from the observer's table.
        // The route readout is a cUI_Button, not a cUI_Text. The ban and flag
        // "labels" in this file are hover-driven status text: the engine only
        // renders them while LabelState is being fed a live hover parameter,
        // which is why a plain label created here shows nothing at rest. A
        // button paints its caption unconditionally, so the readout is visible
        // without hovering; clicking it just refreshes.
        // Kept short: these captions are centred inside a 240-wide button in the
        // lobby's narrow left margin, and an over-long caption overflows the
        // button on both sides and runs off the screen edge.
        constexpr char kNicknamePlaceholder[] = "Name: click to edit";
        constexpr float kLobbySidebarWidth = 240.0f;
        constexpr float kNicknamePanelPadding = 12.0f;
        constexpr float kNicknameControlY = 48.0f;
        constexpr float kNicknameControlHeight = 40.0f;
        constexpr float kNicknameRouteGap = 12.0f;
        constexpr float kNicknameConfirmGap = 8.0f;
        constexpr float kNicknameConfirmWidth = 100.0f;
        constexpr float kNicknameConfirmHeight = 36.0f;
        constexpr float kNicknameEntryWidth =
            kLobbySidebarWidth - 2.0f * kNicknamePanelPadding;
        // cUI_TextEntry::AppendChar rebuilds the rendered string as the *last*
        // N characters of the backing string, N being the ctor's display-length
        // argument (+0x948). It is a width budget, not an input limit: stock
        // "chatEntry" is 520 wide and asks for 36, i.e. ~14.4 units per glyph.
        // Sizing it any smaller silently eats the front of the name -- at 10 on
        // the old 164-wide field, "TheGrizzler" rendered as "heGrizzler".
        constexpr float kNicknameCharacterWidth = 14.4f;
        constexpr int kNicknameVisibleCharacters =
            static_cast<int>(kNicknameEntryWidth / kNicknameCharacterWidth);
        static_assert(kNicknameVisibleCharacters >= 15,
                      "nickname field must render at least 15 characters");

        // Kill switch for the injected lobby readouts. They are the newest
        // children on that screen and the lobby crashes on teardown if any child
        // is bad, so there has to be a way to turn them off without a rebuild.
        //   openshim.ini  [Network] LobbyReadouts = 1
        //   environment   OPENSHIM_DISABLE_LOBBY_READOUTS=1
        // Nickname/route sit in the empty left column. Missing key is ON so
        // the name field stays available; Ban/Flags remain separately gated.
        static bool ShouldEnableLobbyReadouts()
        {
            if (EnvFlagEnabled("OPENSHIM_DISABLE_LOBBY_READOUTS"))
                return false;
            bool enabled = true;
            if (TryGetUserConfigBool(kUserConfigNetworkSection, "LobbyReadouts", enabled))
                return enabled;
            return true;
        }

        // Ban User button + label on the waiting-room parent. Independent of
        // nickname/route readouts; `/ban` still works with this off. Default
        // OFF so OpenShim does not overwrite BZP's faction picker.
        //   openshim.ini  [Network] LobbyBanButton = 0
        static bool ShouldEnableLobbyBanButton()
        {
            if (EnvFlagEnabled("OPENSHIM_DISABLE_LOBBY_BAN_BUTTON") ||
                EnvFlagEnabled("BZR_DISABLE_LOBBY_BAN_BUTTON"))
            {
                return false;
            }
            if (EnvFlagEnabled("OPENSHIM_ENABLE_LOBBY_BAN_BUTTON") ||
                EnvFlagEnabled("BZR_ENABLE_LOBBY_BAN_BUTTON"))
            {
                return true;
            }
            bool enabled = false;
            if (TryGetUserConfigBool(kUserConfigNetworkSection, "LobbyBanButton", enabled))
                return enabled;
            return false;
        }

        // A plain cUI_View eats every click that lands on it. cUI_View::
        // MousePressed (0x007D2570) walks the parent's children in insertion
        // order, stops at the first one that reports the press as handled, and
        // -- once no child has taken it -- reports it handled itself whenever
        // the point is inside its own rect and its input-active byte (+0xE9) is
        // set. It invokes no callback while doing so, so the click simply
        // disappears. Decoration is therefore never passive: the nickname panel
        // is created before the controls it frames so that it draws behind
        // them, which is exactly the order that put it ahead of them in that
        // walk, and it swallowed every click on the entry and on OK.
        //
        // Clearing the byte directly is what makes the view input-transparent.
        // SetActive (0x007D3310) is not usable here -- it forwards the same
        // value to the Ogre element's visibility, so it would take the artwork
        // down with the hit rectangle. Nothing else in the image reads +0xE9
        // except the input handlers, all through the getter at 0x007D3360.
        static void MakeViewInputTransparent(void* view)
        {
            if (!view)
                return;
            *(static_cast<uint8_t*>(view) + kUiViewInputActiveOffset) = 0;
        }

        static void InitializeNicknameEntry(void* entry)
        {
            if (!entry)
                return;

            if (g_BzrFn_TextEntrySetInputLimit)
                g_BzrFn_TextEntrySetInputLimit(entry, static_cast<int>(kBzrNetNicknameCapacity - 1));

            char current[128] = {};
            if (ReadBzrNetNickname(current, sizeof(current)) && current[0] != '\0')
            {
                // This is the TextEntry API, not cUI_Text::SetText: it updates
                // both the backing std::string and the rendered tail.
                if (g_BzrFn_TextEntryAppendText)
                    g_BzrFn_TextEntryAppendText(entry, current);
            }
            else if (g_BzrFn_SetTooltip)
            {
                // Show a prompt without putting it in the backing string. The
                // first typed character replaces this display through the
                // entry's normal input path, and Enter on an empty entry is a
                // no-op in ApplyNicknameFromEntry.
                g_BzrFn_SetTooltip(entry, kNicknamePlaceholder);
            }
        }

        static void BeginNicknameEdit(void* entry, void* parent, const char* source)
        {
            if (!entry || !parent || !g_LobbyNicknameInputHookInstalled ||
                !IsWidgetLiveChildOfParent(parent, entry))
            {
                Log(L"[BZRNET] Nickname edit unavailable (source=%hs)\n", source);
                return;
            }

            // This lobby replays the focused transparent button's click
            // callback for keyboard events. Do not restart an edit already in
            // progress: doing so would re-arm replace-on-first-character for
            // every key and leave only the final character in the entry.
            if (g_ActiveNicknameEntry == entry && g_ActiveNicknameParent == parent)
                return;

            // Remove the display-only prompt before the first key arrives. If
            // an actual nickname is present, retain it until the first edited
            // character and then replace it as a unit.
            char current[192] = {};
            const bool haveText = ReadEngineStdString(
                static_cast<uint8_t*>(entry) + kUiTextEntryTextOffset,
                current,
                sizeof(current));
            if (g_BzrFn_SetTooltip)
            {
                // A successful apply leaves a display-only confirmation in
                // the row. Restore the real backing value on the next click.
                g_BzrFn_SetTooltip(entry, (haveText && current[0] != '\0') ? current : "");
            }

            g_ActiveNicknameEntry = entry;
            g_ActiveNicknameParent = parent;
            g_ReplaceNicknameOnNextInput = haveText && current[0] != '\0';
            Log(L"[BZRNET] Nickname edit active (source=%hs replace=%hs)\n",
                source,
                g_ReplaceNicknameOnNextInput ? "yes" : "no");
        }

        static void EndNicknameEdit(void* entry)
        {
            if (g_ActiveNicknameEntry != entry)
                return;
            g_ActiveNicknameEntry = nullptr;
            g_ActiveNicknameParent = nullptr;
            g_ReplaceNicknameOnNextInput = false;
        }

        // The field is only 15 visible characters. Lounge re-auth is the live
        // path; in-match and no-session applies still wait for the next connect.
        void ShowNicknameApplyConfirmation(void* entry, BzrNetNicknameResult result)
        {
            if (!entry || !g_BzrFn_SetTooltip)
                return;
            const bool hostLive = g_HostUiParent &&
                IsWidgetLiveChildOfParent(g_HostUiParent, entry);
            const bool clientLive = g_ClientUiParent &&
                IsWidgetLiveChildOfParent(g_ClientUiParent, entry);
            const bool preLobbyLive = g_PreLobbyUiParent &&
                IsWidgetLiveChildOfParent(g_PreLobbyUiParent, entry);
            if (!hostLive && !clientLive && !preLobbyLive)
                return;
            const char* text = (result == BzrNetNicknameResult::NativeSendCompleted)
                ? "Sent to server"
                : (result == BzrNetNicknameResult::ReauthQueued)
                    ? "Reconnecting..."
                    : "Saved-next conn";
            g_BzrFn_SetTooltip(entry, text);
        }

        // Refresh callers reach this from the chat command and the external
        // bridge as well as from live UI events, so the owning lobby screen may
        // already be gone. Both in-match /nickname attempts on 2026-09-04 faulted
        // at 0x007C2967 -- inside SetButtonLabel, dereferencing the stale
        // button's +0x144 render object -- because a null check was the only
        // gate. Require containment in the cached owner, the same evidence
        // SyncOneNicknameEntry already demands.
        static void UpdateNetRouteLabel(void* owner, void* readout)
        {
            if (!g_BzrFn_SetButtonLabel)
                return;
            if (!NativeUiValidation::CachedChildAccessAllowed(
                    owner != nullptr,
                    readout != nullptr,
                    IsWidgetLiveChildOfParent(owner, readout)))
            {
                return;
            }
            char summary[256] = {};
            FormatBzrNetRouteSummary(summary, sizeof(summary));
            __try
            {
                g_BzrFn_SetButtonLabel(readout, summary);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                Log(L"[BZRNET] Route label refresh faulted code=0x%08X\n",
                    static_cast<uint32_t>(GetExceptionCode()));
            }
        }


        // Keep the launch/auth nickname synchronized with the committed UI
        // value, then try the native live SetPlayerData path. The fixed buffer
        // at 0x009453E0 remains the Authorization `name` source for a later
        // reconnect in this same process.
        static void SyncNicknameEntryText(void* entry, const char* value)
        {
            if (!entry || !value || !g_BzrFn_TextEntryClear || !g_BzrFn_TextEntryAppendText)
                return;
            __try
            {
                g_BzrFn_TextEntryClear(entry);
                g_BzrFn_TextEntryAppendText(entry, value);
                if (g_BzrFn_SetTooltip)
                    g_BzrFn_SetTooltip(entry, value);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                Log(L"[BZRNET] Nickname UI synchronization faulted code=0x%08X\n",
                    static_cast<uint32_t>(GetExceptionCode()));
            }
        }

        static void SyncOneNicknameEntry(bool host, void* entry, const char* value)
        {
            if (!entry || !value || !g_BzrFn_TextEntryClear || !g_BzrFn_TextEntryAppendText)
                return;
            if (!CachedLobbyWidgetIsLive(host, entry, "nickname_sync"))
                return;
            SyncNicknameEntryText(entry, value);
        }

        void SyncNicknameEntriesFromAuthoritativeValue(const char* value)
        {
            SyncOneNicknameEntry(true, g_NicknameEntryHost, value);
            SyncOneNicknameEntry(false, g_NicknameEntryClient, value);
        }

        // Commit through the same authoritative operation used by chat and the
        // exported bridge. This is the UI's natural Apply/Enter event, so no
        // SetPlayerData traffic is generated for intermediate keystrokes.
        static BzrNetNicknameResult ApplyNicknameFromEntry(void* entry, const char* source)
        {
            if (!entry)
                return BzrNetNicknameResult::InvalidNickname;

            char text[192] = {};
            if (!ReadEngineStdString(
                    static_cast<uint8_t*>(entry) + kUiTextEntryTextOffset,
                    text, sizeof(text)))
            {
                Log(L"[BZRNET] Nickname entry unreadable (source=%hs)\n", source);
                return BzrNetNicknameResult::InvalidNickname;
            }

            const std::string trimmed = TrimAsciiCopy(text);
            if (trimmed.empty() || trimmed == kNicknamePlaceholder)
                return BzrNetNicknameResult::InvalidNickname;

            const BzrNetNicknameResult result = ApplyBzrNetNicknameAuthoritative(
                trimmed.c_str(), source);
            if (!IsAcceptedBzrNetNicknameResult(result))
                return result;

            SyncNicknameEntriesFromAuthoritativeValue(trimmed.c_str());
            Log(L"[BZRNET] Nickname UI apply result=%hs (source=%hs)\n",
                BzrNetNicknameResultName(result), source);
            return result;
        }

        // Redux's multiplayer panels are pre-rendered artwork rather than a
        // resizable frame widget. Generate a small matching plate for the
        // nickname controls and place the native entry/button over its field.
        static bool WriteNicknamePanelPng(const std::filesystem::path& outPath)
        {
            std::string gdiplusError;
            if (!EnsureGdiplusInitialized(gdiplusError))
            {
                Log(L"[BZRNET] nickname panel GDI+ init failed: %hs\n", gdiplusError.c_str());
                return false;
            }

            Gdiplus::Bitmap bitmap(kNicknamePanelWidth, kNicknamePanelHeight, PixelFormat32bppARGB);
            if (bitmap.GetLastStatus() != Gdiplus::Ok)
                return false;

            {
                Gdiplus::Graphics gfx(&bitmap);
                gfx.SetSmoothingMode(Gdiplus::SmoothingModeNone);
                gfx.SetPixelOffsetMode(Gdiplus::PixelOffsetModeHalf);
                gfx.SetTextRenderingHint(Gdiplus::TextRenderingHintSingleBitPerPixelGridFit);

                Gdiplus::SolidBrush edgeDark(Gdiplus::Color(255, 0, 42, 0));
                Gdiplus::SolidBrush edgeBright(Gdiplus::Color(255, 0, 127, 0));
                Gdiplus::SolidBrush edgeMid(Gdiplus::Color(255, 0, 84, 0));
                Gdiplus::SolidBrush field(Gdiplus::Color(255, 0, 0, 0));

                gfx.FillRectangle(&edgeDark, 0, 0, kNicknamePanelWidth, kNicknamePanelHeight);
                gfx.FillRectangle(&edgeBright, 3, 3, kNicknamePanelWidth - 6, kNicknamePanelHeight - 6);
                gfx.FillRectangle(&edgeMid, 5, 5, kNicknamePanelWidth - 10, kNicknamePanelHeight - 10);
                gfx.FillRectangle(&edgeDark, 7, 7, kNicknamePanelWidth - 14, kNicknamePanelHeight - 14);

                const int inner = kNicknamePanelWidth - 18;
                gfx.FillRectangle(
                    &field,
                    9,
                    kNicknamePanelHeaderHeight,
                    inner,
                    kNicknamePanelHeight - kNicknamePanelHeaderHeight - 9);
                gfx.FillRectangle(&edgeBright, 9, 32, inner, 4);
                gfx.FillRectangle(&edgeMid, 9, 36, inner, 2);
                gfx.FillRectangle(&edgeDark, 9, 38, inner, 2);

                Gdiplus::Font font(L"Lucida Console", 13.0f, Gdiplus::FontStyleBold, Gdiplus::UnitPixel);
                Gdiplus::StringFormat format;
                format.SetAlignment(Gdiplus::StringAlignmentCenter);
                format.SetLineAlignment(Gdiplus::StringAlignmentCenter);
                format.SetFormatFlags(Gdiplus::StringFormatFlagsNoWrap);
                Gdiplus::SolidBrush text(Gdiplus::Color(255, 64, 220, 64));
                const Gdiplus::RectF layout(9.0f, 4.0f, static_cast<float>(inner), 28.0f);
                gfx.DrawString(L"PLAYER NAME", -1, &font, layout, &format, &text);
            }

            CLSID pngClsid = {};
            if (!GetPngEncoderClsid(pngClsid))
                return false;
            std::error_code ec;
            std::filesystem::create_directories(outPath.parent_path(), ec);
            const Gdiplus::Status saved = bitmap.Save(outPath.wstring().c_str(), &pngClsid, nullptr);
            if (saved != Gdiplus::Ok)
            {
                Log(L"[BZRNET] nickname panel PNG save failed path=%hs status=%d\n",
                    outPath.string().c_str(), static_cast<int>(saved));
                return false;
            }
            return true;
        }

        static std::string EnsureNicknamePanelImage()
        {
            EnsureFlagPreviewResourceLocationRegistered();
            const std::filesystem::path outPath =
                GetFlagPreviewUiDirectory() / kNicknamePanelTextureName;
            static bool s_Written = false;
            std::error_code ec;
            if (s_Written && std::filesystem::exists(outPath, ec))
                return kNicknamePanelTextureName;
            if (!WriteNicknamePanelPng(outPath))
                return std::string();
            s_Written = true;
            Log(L"[BZRNET] wrote nickname panel path=%hs\n", outPath.string().c_str());
            return kNicknamePanelTextureName;
        }

        static void CompleteNicknameEdit(
            void* entry,
            void* routeLabel,
            const char* source)
        {
            // The pre-lobby only ends the edit and keeps the typed text: its
            // Continue button is what applies the name (and recycles the
            // connection), so Enter must not do either.
            if (entry && entry == g_NicknameEntryPreLobby)
            {
                EndNicknameEdit(entry);
                return;
            }
            const bool host = entry == g_NicknameEntryHost;
            const BzrNetNicknameResult result = ApplyNicknameFromEntry(entry, source);
            EndNicknameEdit(entry);
            if (routeLabel && CachedLobbyWidgetIsLive(host, routeLabel, "nickname_complete"))
                UpdateNetRouteLabel(CachedLobbyOwner(host), routeLabel);
            if (!IsAcceptedBzrNetNicknameResult(result))
                return;

            if (g_NicknameEnterDispatchEntry == entry)
            {
                g_PendingNicknameConfirmationEntry = entry;
                g_PendingNicknameConfirmationResult = result;
            }
            else
                ShowNicknameApplyConfirmation(entry, result);
        }

        // A native cUI_TextEntry over the nickname buffer plus the route readout.
        // Do not install cUI_Button callbacks on the entry: the button setters
        // write +0x150/+0x154, which lie inside cUI_Text's 2000-byte display
        // buffer and corrupt it. A transparent button supplies the proven click
        // path; the guarded TextEntry append hook supplies keyboard input.
        static void CreateNicknameAndRouteWidgets(
            void* parent,
            float x,
            float y,
            void** outPanel,
            void** outEntry,
            void** outEditProxy,
            void** outConfirm,
            void** outRouteLabel,
            void* onEnter,
            void* onEdit,
            void* onRefresh,
            void* onHover)
        {
            if (!parent || !g_BzrFn_AddChild || !ShouldEnableLobbyReadouts() ||
                !g_BzrFn_SetOnClick || !g_BzrFn_SetOnHover)
                return;

            // Draw first so the interactive children are above it in the
            // dialog's child order, then hand the mouse back with
            // MakeViewInputTransparent -- that same order is the hit-test
            // order, and a live cUI_View consumes anything inside its rect.
            if (outPanel && g_BzrFn_OverlayCtor)
            {
                const std::string textureName = EnsureNicknamePanelImage();
                if (!textureName.empty())
                {
                    void* panelMem = ::operator new(0x144, std::nothrow);
                    if (panelMem)
                    {
                        std::memset(panelMem, 0, 0x144);
                        *outPanel = g_BzrFn_OverlayCtor(
                            panelMem,
                            "Nickname Panel",
                            x,
                            y,
                            static_cast<float>(kNicknamePanelWidth),
                            static_cast<float>(kNicknamePanelHeight),
                            0x20,
                            parent,
                            0);
                        if (*outPanel)
                        {
                            if (g_BzrFn_SetTextureOff)
                                g_BzrFn_SetTextureOff(*outPanel, textureName.c_str());
                            MakeViewInputTransparent(*outPanel);
                            g_BzrFn_AddChild(parent, *outPanel, 0);
                        }
                    }
                }
            }

            const float controlX = x + kNicknamePanelPadding;
            const float controlY = y + kNicknameControlY;

            if (outEntry && g_BzrFn_TextEntryCtor)
            {
                void* entryMem = ::operator new(kUiTextEntrySize, std::nothrow);
                if (entryMem)
                {
                    std::memset(entryMem, 0, kUiTextEntrySize);
                    *outEntry = g_BzrFn_TextEntryCtor(
                        entryMem,
                        0,      // matches this lobby's stock chatEntry
                        1,      // allow Enter
                        kNicknameVisibleCharacters,
                        "Nickname",
                        controlX,
                        controlY,
                        kNicknameEntryWidth,
                        kNicknameControlHeight,
                        0x8020,
                        parent);
                    if (*outEntry)
                    {
                        if (g_BzrFn_TextEntrySetEnterCb && onEnter)
                            g_BzrFn_TextEntrySetEnterCb(*outEntry, onEnter);
                        InitializeNicknameEntry(*outEntry);
                        g_BzrFn_AddChild(parent, *outEntry, 0);
                    }
                }
            }

            // The lobby's OnChar virtual calls AppendChar directly on its stock
            // chatEntry member, so ordinary UI focus cannot redirect it. A
            // textureless cUI_Button over the same rectangle enters our guarded
            // nickname-edit mode. It draws nothing, leaving the entry visible.
            if (outEditProxy && onEdit && g_BzrFn_ButtonCtor)
            {
                void* focusMem = ::operator new(kUiButtonSize, std::nothrow);
                if (focusMem)
                {
                    std::memset(focusMem, 0, kUiButtonSize);
                    *outEditProxy = g_BzrFn_ButtonCtor(
                        focusMem,
                        "Nickname Edit",
                        controlX,
                        controlY,
                        kNicknameEntryWidth,
                        kNicknameControlHeight,
                        0x20,
                        parent,
                        0,
                        0);
                    if (*outEditProxy)
                    {
                        if (g_BzrFn_SetOnClick) g_BzrFn_SetOnClick(*outEditProxy, onEdit);
                        if (g_BzrFn_SetOnHover) g_BzrFn_SetOnHover(*outEditProxy, onHover);
                        g_BzrFn_AddChild(parent, *outEditProxy, 0);
                    }
                }
            }

            if (outConfirm && onEnter && g_BzrFn_ButtonCtor)
            {
                void* confirmMem = ::operator new(kUiButtonSize, std::nothrow);
                if (confirmMem)
                {
                    std::memset(confirmMem, 0, kUiButtonSize);
                    *outConfirm = g_BzrFn_ButtonCtor(
                        confirmMem,
                        "Apply Nickname",
                        x + 0.5f * (kLobbySidebarWidth - kNicknameConfirmWidth),
                        controlY + kNicknameControlHeight + kNicknameConfirmGap,
                        kNicknameConfirmWidth,
                        kNicknameConfirmHeight,
                        0x20,
                        parent,
                        0,
                        0);
                    if (*outConfirm)
                    {
                        if (g_BzrFn_SetTextureOff) g_BzrFn_SetTextureOff(*outConfirm, "MultiplayerModeButton_off.png");
                        if (g_BzrFn_SetTextureOver) g_BzrFn_SetTextureOver(*outConfirm, "MultiplayerModeButton_over.png");
                        if (g_BzrFn_SetTextureOn) g_BzrFn_SetTextureOn(*outConfirm, "MultiplayerModeButton_on.png");
                        if (g_BzrFn_SetButtonLabel) g_BzrFn_SetButtonLabel(*outConfirm, "OK");
                        if (g_BzrFn_SetOnClick) g_BzrFn_SetOnClick(*outConfirm, onEnter);
                        if (g_BzrFn_SetOnHover) g_BzrFn_SetOnHover(*outConfirm, onHover);
                        g_BzrFn_AddChild(parent, *outConfirm, 0);
                    }
                }
            }

            if (outRouteLabel && g_BzrFn_ButtonCtor)
            {
                void* readoutMem = ::operator new(kUiButtonSize, std::nothrow);
                if (readoutMem)
                {
                    std::memset(readoutMem, 0, kUiButtonSize);
                    *outRouteLabel = g_BzrFn_ButtonCtor(
                        readoutMem,
                        "Net Route",
                        x,
                        y + static_cast<float>(kNicknamePanelHeight) + kNicknameRouteGap,
                        kLobbySidebarWidth,
                        44.0f,
                        0x20,
                        parent,
                        0,
                        0);
                    if (*outRouteLabel)
                    {
                        if (g_BzrFn_SetTextureOff) g_BzrFn_SetTextureOff(*outRouteLabel, "MultiplayerModeButton_off.png");
                        if (g_BzrFn_SetTextureOver) g_BzrFn_SetTextureOver(*outRouteLabel, "MultiplayerModeButton_over.png");
                        if (g_BzrFn_SetTextureOn) g_BzrFn_SetTextureOn(*outRouteLabel, "MultiplayerModeButton_on.png");
                        // Both slots must stay non-null on an active dialog
                        // child; clicking simply refreshes the readout.
                        if (g_BzrFn_SetOnClick && onRefresh) g_BzrFn_SetOnClick(*outRouteLabel, onRefresh);
                        if (g_BzrFn_SetOnHover && onHover) g_BzrFn_SetOnHover(*outRouteLabel, onHover);
                        g_BzrFn_AddChild(parent, *outRouteLabel, 0);
                        UpdateNetRouteLabel(parent, *outRouteLabel);
                    }
                }
            }
        }

        static void CycleSelectedFlag(int delta, const char* source)
        {
            EnsureFlagCatalogLoaded();
            if (g_FlagCatalog.empty())
                return;

            int nextIndex = g_SelectedFlagIndex;
            if (nextIndex < 0)
                nextIndex = 0;
            else
                nextIndex += delta;

            SelectFlagEntryByIndex(nextIndex, source);
            PrimeSelectedFlagForTesting(source);
        }
    }

    void __cdecl BanButtonOnClickHost()
    {
        if (!g_BzrPtr_9456D0 || !g_BzrFn_GetSelected)
            return;
        if (g_BzrFn_IsHost && g_BzrFn_IsHost() == 0)
        {
            Log(L"[BAN] Host ban button ignored while not hosting\n");
            return;
        }

        void* root = *g_BzrPtr_9456D0;
        if (!root)
            return;

        auto listObj = *reinterpret_cast<void**>(reinterpret_cast<uint8_t*>(root) + 0x0C);
        auto selected = g_BzrFn_GetSelected(listObj);
        if (!selected)
            return;

        int type = *reinterpret_cast<int*>(reinterpret_cast<uint8_t*>(selected) + 0x08);
        if (type != 1 && type != 2)
            return;

        const char prefix = (type == 1) ? 'S' : 'G';
        uint64_t id = *reinterpret_cast<uint64_t*>(reinterpret_cast<uint8_t*>(selected) + 0x10);
        char idbuf[32] = {};
        std::snprintf(idbuf, sizeof(idbuf), "%c%llu", prefix, static_cast<unsigned long long>(id));

        BzrString name;
        BzrStringInitEmpty(&name);
        BzrStringCopy(&name, reinterpret_cast<BzrString*>(reinterpret_cast<uint8_t*>(selected) + 0x2C));
        Log(L"[BAN] Host button selected stable=%hs name=%hs\n",
            idbuf,
            name.size ? BzrStringData(&name) : "");
        AddBanConfigEntry(idbuf, &name, "host_button");
        KickBannedPlayers("host_button", 0, 0, 0);
        BzrStringFree(&name);
    }

    void __cdecl BanButtonOnClickClient()
    {
        if (!g_BzrPtr_94557C || !g_BzrFn_GetSelected || !g_BzrFn_CommandHandler)
            return;
        if (g_BzrFn_IsHost && g_BzrFn_IsHost() == 0)
        {
            Log(L"[BAN] Client-side ban button blocked because local user is not host\n");
            return;
        }

        void* root = *g_BzrPtr_94557C;
        if (!root)
            return;

        void* listObj = *reinterpret_cast<void**>(reinterpret_cast<uint8_t*>(root) + 0x194);
        void* selected = g_BzrFn_GetSelected(listObj);
        if (!selected)
            return;

        if (g_BzrPtr_CurrentUser)
        {
            auto cur = g_BzrPtr_CurrentUser;
            if (*reinterpret_cast<uint32_t*>(reinterpret_cast<uint8_t*>(selected) + 0x38) ==
                    *reinterpret_cast<uint32_t*>(cur + 8) &&
                *reinterpret_cast<uint32_t*>(reinterpret_cast<uint8_t*>(selected) + 0x3C) ==
                    *reinterpret_cast<uint32_t*>(cur + 0x0C))
                return;

            if (*reinterpret_cast<uint32_t*>(reinterpret_cast<uint8_t*>(selected) + 0x30) ==
                *reinterpret_cast<uint32_t*>(cur))
                return;
        }

        uint16_t id = *reinterpret_cast<uint16_t*>(reinterpret_cast<uint8_t*>(selected) + 0x28);
        Log(L"[BAN] Client-style lobby button issuing /ban for session=%u\n", id);
        g_BzrFn_CommandHandler(id, "/ban");
    }

    void __cdecl BanButtonOnHoverHost(void* param)
    {
        if (g_BzrFn_LabelState && g_BanLabelHost)
            g_BzrFn_LabelState(g_BanLabelHost, param);
    }

    void __cdecl BanButtonOnHoverClient(void* param)
    {
        if (g_BzrFn_LabelState && g_BanLabelClient)
            g_BzrFn_LabelState(g_BanLabelClient, param);
    }

    void __cdecl FlagButtonOnClickHost()
    {
        CycleSelectedFlag(1, "host_button");
        UpdateFlagSelectionUiLabel(g_FlagLabelHost);
        UpdateFlagPreviewWidget(g_FlagPreviewHost);
    }

    void __cdecl FlagButtonOnClickClient()
    {
        CycleSelectedFlag(1, "client_button");
        UpdateFlagSelectionUiLabel(g_FlagLabelClient);
        UpdateFlagPreviewWidget(g_FlagPreviewClient);
    }

    void __cdecl FlagButtonOnClickPrevHost()
    {
        CycleSelectedFlag(-1, "host_button_prev");
        UpdateFlagSelectionUiLabel(g_FlagLabelHost);
        UpdateFlagPreviewWidget(g_FlagPreviewHost);
    }

    void __cdecl FlagButtonOnClickPrevClient()
    {
        CycleSelectedFlag(-1, "client_button_prev");
        UpdateFlagSelectionUiLabel(g_FlagLabelClient);
        UpdateFlagPreviewWidget(g_FlagPreviewClient);
    }

    void __cdecl NetRouteRefreshHost()
    {
        if (CachedLobbyWidgetIsLive(true, g_NetRouteLabelHost, "route_refresh"))
            UpdateNetRouteLabel(g_HostUiParent, g_NetRouteLabelHost);
    }

    void __cdecl NetRouteRefreshClient()
    {
        if (CachedLobbyWidgetIsLive(false, g_NetRouteLabelClient, "route_refresh"))
            UpdateNetRouteLabel(g_ClientUiParent, g_NetRouteLabelClient);
    }

    void __cdecl NicknameEntryOnEnterHost()
    {
        CompleteNicknameEdit(
            g_NicknameEntryHost,
            g_NetRouteLabelHost,
            "host_lobby");
    }

    void __cdecl NicknameEntryOnEnterClient()
    {
        CompleteNicknameEdit(
            g_NicknameEntryClient,
            g_NetRouteLabelClient,
            "client_lobby");
    }

    void __cdecl NicknameEditOnClickHost()
    {
        BeginNicknameEdit(g_NicknameEntryHost, g_HostUiParent, "host_lobby_click");
    }

    void __cdecl NicknameEditOnClickClient()
    {
        BeginNicknameEdit(g_NicknameEntryClient, g_ClientUiParent, "client_lobby_click");
    }

    // The route table is filled from the BZRNet worker thread, so the label is
    // refreshed from UI-thread events rather than pushed from the observer.
    // Hover is the same refresh point the flag label already uses.
    void __cdecl FlagButtonOnHoverHost(void* param)
    {
        if (g_BzrFn_LabelState && g_FlagLabelHost)
            g_BzrFn_LabelState(g_FlagLabelHost, param);
        UpdateFlagSelectionUiLabel(g_FlagLabelHost);
        NetRouteRefreshHost();
    }

    void __cdecl FlagButtonOnHoverClient(void* param)
    {
        if (g_BzrFn_LabelState && g_FlagLabelClient)
            g_BzrFn_LabelState(g_FlagLabelClient, param);
        UpdateFlagSelectionUiLabel(g_FlagLabelClient);
        NetRouteRefreshClient();
    }

    void BanButtonCreateHost()
    {
        if (!g_BzrFn_ButtonCtor || !g_BzrFn_LabelCtor || !g_BzrFn_AddChild || !g_BanParentHost ||
            !g_BzrFn_SetOnClick || !g_BzrFn_SetOnHover)
            return;

        void* parent = g_BanParentHost;
        EnsureUiCacheMatchesParent(parent, true);

        if (ShouldEnableLobbyBanButton())
        {
            void* buttonMem = ::operator new(0x1EC, std::nothrow);
            if (buttonMem)
            {
                std::memset(buttonMem, 0, 0x1EC);
                g_BanButtonHost = g_BzrFn_ButtonCtor(
                    buttonMem,
                    "Ban User",
                    g_BanX - 48.0f,
                    g_BanY + 96.0f,
                    48.0f,
                    48.0f,
                    0x20,
                    parent,
                    0,
                    0);

                if (g_BanButtonHost)
                {
                    if (g_BzrFn_SetTextureOff) g_BzrFn_SetTextureOff(g_BanButtonHost, "MultiplayerModeButton_off.png");
                    if (g_BzrFn_SetTextureOver) g_BzrFn_SetTextureOver(g_BanButtonHost, "MultiplayerModeButton_over.png");
                    if (g_BzrFn_SetTextureOn) g_BzrFn_SetTextureOn(g_BanButtonHost, "MultiplayerModeButton_on.png");
                    if (g_BzrFn_SetButtonLabel) g_BzrFn_SetButtonLabel(g_BanButtonHost, "B");
                    if (g_BzrFn_SetOnClick) g_BzrFn_SetOnClick(g_BanButtonHost, reinterpret_cast<void*>(BanButtonOnClickHost));
                    if (g_BzrFn_SetOnHover) g_BzrFn_SetOnHover(g_BanButtonHost, reinterpret_cast<void*>(BanButtonOnHoverHost));
                    g_BzrFn_AddChild(parent, g_BanButtonHost, 0);
                }
            }

            void* labelMem = ::operator new(0x930, std::nothrow);
            if (labelMem)
            {
                std::memset(labelMem, 0, 0x930);
                g_BanLabelHost = g_BzrFn_LabelCtor(
                    labelMem,
                    "Lobby",
                    270.0f,
                    980.0f,
                    338.0f,
                    43.0f,
                    0x8020,
                    parent,
                    0);

                if (g_BanLabelHost)
                {
                    if (g_BzrFn_SetTooltip) g_BzrFn_SetTooltip(g_BanLabelHost, "Ban highlighted player");
                    if (g_BzrFn_LabelState) g_BzrFn_LabelState(g_BanLabelHost, nullptr);
                    g_BzrFn_AddChild(parent, g_BanLabelHost, 0);
                }
            }
        }

        // With [Network] PreLobby on, the flag and nickname pickers live on the
        // pre-lobby screen only; the net-route readout stays here.
        const bool pickersMoved = IsPreLobbyEnabled();

        if (!pickersMoved && ShouldEnableMultiplayerFlagUi() &&
            (!g_FlagButtonHost ||
             !IsWidgetLiveChildOfParent(parent, g_FlagButtonHost)))
        {
            // The pair plus its gap is 100px wide, so it starts far enough left
            // of the Ban button (g_BanX - 48, 48 wide) to clear it entirely.
            CreateFlagButtonCommon(
                parent,
                g_BanX - 224.0f,
                g_BanY + 96.0f,
                &g_FlagButtonHost,
                &g_FlagButtonHostRight,
                &g_FlagLabelHost,
                &g_FlagPreviewHost,
                reinterpret_cast<void*>(FlagButtonOnClickPrevHost),
                reinterpret_cast<void*>(FlagButtonOnClickHost),
                reinterpret_cast<void*>(FlagButtonOnHoverHost));
        }

        if (pickersMoved)
        {
            // Same position as the full cluster would give the route row.
            if (!g_NetRouteLabelHost || !IsWidgetLiveChildOfParent(parent, g_NetRouteLabelHost))
            {
                CreateNicknameAndRouteWidgets(
                    parent,
                    g_BanX - 208.0f,
                    g_BanY - 360.0f,
                    nullptr, nullptr, nullptr, nullptr,
                    &g_NetRouteLabelHost,
                    nullptr,
                    nullptr,
                    reinterpret_cast<void*>(NetRouteRefreshHost),
                    reinterpret_cast<void*>(FlagButtonOnHoverHost));
            }
            else
            {
                NetRouteRefreshHost();
            }
        }
        else if (!g_NicknamePanelHost || !g_NicknameEntryHost || !g_NicknameEditButtonHost ||
            !g_NicknameConfirmButtonHost ||
            !IsWidgetLiveChildOfParent(parent, g_NicknamePanelHost) ||
            !IsWidgetLiveChildOfParent(parent, g_NicknameEntryHost) ||
            !IsWidgetLiveChildOfParent(parent, g_NicknameEditButtonHost) ||
            !IsWidgetLiveChildOfParent(parent, g_NicknameConfirmButtonHost))
        {
            // Use the otherwise empty upper-left column. This keeps the name,
            // explicit OK button and compact route row together and leaves a
            // clear gap above the framed flag selector and stock W/M controls.
            CreateNicknameAndRouteWidgets(
                parent,
                g_BanX - 208.0f,
                g_BanY - 360.0f,
                &g_NicknamePanelHost,
                &g_NicknameEntryHost,
                &g_NicknameEditButtonHost,
                &g_NicknameConfirmButtonHost,
                &g_NetRouteLabelHost,
                reinterpret_cast<void*>(NicknameEntryOnEnterHost),
                reinterpret_cast<void*>(NicknameEditOnClickHost),
                reinterpret_cast<void*>(NetRouteRefreshHost),
                reinterpret_cast<void*>(FlagButtonOnHoverHost));
        }
        else
        {
            // Re-assert it: SetActive on a surviving panel would restore the
            // byte and put the click-swallowing rectangle back over the row.
            MakeViewInputTransparent(g_NicknamePanelHost);
            NetRouteRefreshHost();
        }

        if (ShouldRunUiWidgetProbe())
            CreateUiWidgetProbe(parent);
    }

    void BanButtonCreateClient()
    {
        if (!g_BzrFn_ButtonCtor || !g_BzrFn_LabelCtor || !g_BzrFn_AddChild || !g_BanParentClient ||
            !g_BzrFn_SetOnClick || !g_BzrFn_SetOnHover)
            return;

        void* parent = g_BanParentClient;
        EnsureUiCacheMatchesParent(parent, false);

        if (ShouldEnableLobbyBanButton())
        {
            void* buttonMem = ::operator new(0x1EC, std::nothrow);
            if (buttonMem)
            {
                std::memset(buttonMem, 0, 0x1EC);
                g_BanButtonClient = g_BzrFn_ButtonCtor(
                    buttonMem,
                    "Ban User",
                    -33.0f,
                    942.0f,
                    48.0f,
                    48.0f,
                    0,
                    parent,
                    0,
                    0);

                if (g_BanButtonClient)
                {
                    if (g_BzrFn_SetTextureOff) g_BzrFn_SetTextureOff(g_BanButtonClient, "MultiplayerModeButton_off.png");
                    if (g_BzrFn_SetTextureOver) g_BzrFn_SetTextureOver(g_BanButtonClient, "MultiplayerModeButton_over.png");
                    if (g_BzrFn_SetTextureOn) g_BzrFn_SetTextureOn(g_BanButtonClient, "MultiplayerModeButton_on.png");
                    if (g_BzrFn_SetButtonLabel) g_BzrFn_SetButtonLabel(g_BanButtonClient, "B");
                    if (g_BzrFn_SetOnClick) g_BzrFn_SetOnClick(g_BanButtonClient, reinterpret_cast<void*>(BanButtonOnClickClient));
                    if (g_BzrFn_SetOnHover) g_BzrFn_SetOnHover(g_BanButtonClient, reinterpret_cast<void*>(BanButtonOnHoverClient));
                    g_BzrFn_AddChild(parent, g_BanButtonClient, 0);
                }
            }

            void* labelMem = ::operator new(0x930, std::nothrow);
            if (labelMem)
            {
                std::memset(labelMem, 0, 0x930);
                g_BanLabelClient = g_BzrFn_LabelCtor(
                    labelMem,
                    "Lobby",
                    270.0f,
                    1000.0f,
                    338.0f,
                    43.0f,
                    0x20,
                    parent,
                    0);

                if (g_BanLabelClient)
                {
                    if (g_BzrFn_SetTooltip) g_BzrFn_SetTooltip(g_BanLabelClient, "Ban highlighted player");
                    if (g_BzrFn_LabelState) g_BzrFn_LabelState(g_BanLabelClient, nullptr);
                    g_BzrFn_AddChild(parent, g_BanLabelClient, 0);
                }
            }
        }

        // With [Network] PreLobby on, the flag and nickname pickers live on the
        // pre-lobby screen only; the net-route readout stays here.
        const bool pickersMoved = IsPreLobbyEnabled();

        if (!pickersMoved && ShouldEnableMultiplayerFlagUi() &&
            (!g_FlagButtonClient ||
             !IsWidgetLiveChildOfParent(parent, g_FlagButtonClient)))
        {
            CreateFlagButtonCommon(
                parent,
                -205.0f,
                942.0f,
                &g_FlagButtonClient,
                &g_FlagButtonClientRight,
                &g_FlagLabelClient,
                &g_FlagPreviewClient,
                reinterpret_cast<void*>(FlagButtonOnClickPrevClient),
                reinterpret_cast<void*>(FlagButtonOnClickClient),
                reinterpret_cast<void*>(FlagButtonOnHoverClient));
        }

        if (pickersMoved)
        {
            if (!g_NetRouteLabelClient || !IsWidgetLiveChildOfParent(parent, g_NetRouteLabelClient))
            {
                CreateNicknameAndRouteWidgets(
                    parent,
                    -189.0f,
                    496.0f,
                    nullptr, nullptr, nullptr, nullptr,
                    &g_NetRouteLabelClient,
                    nullptr,
                    nullptr,
                    reinterpret_cast<void*>(NetRouteRefreshClient),
                    reinterpret_cast<void*>(FlagButtonOnHoverClient));
            }
            else
            {
                NetRouteRefreshClient();
            }
        }
        else if (!g_NicknamePanelClient || !g_NicknameEntryClient || !g_NicknameEditButtonClient ||
            !g_NicknameConfirmButtonClient ||
            !IsWidgetLiveChildOfParent(parent, g_NicknamePanelClient) ||
            !IsWidgetLiveChildOfParent(parent, g_NicknameEntryClient) ||
            !IsWidgetLiveChildOfParent(parent, g_NicknameEditButtonClient) ||
            !IsWidgetLiveChildOfParent(parent, g_NicknameConfirmButtonClient))
        {
            // Mirror the host layout in the client's empty left column.
            CreateNicknameAndRouteWidgets(
                parent,
                -189.0f,
                496.0f,
                &g_NicknamePanelClient,
                &g_NicknameEntryClient,
                &g_NicknameEditButtonClient,
                &g_NicknameConfirmButtonClient,
                &g_NetRouteLabelClient,
                reinterpret_cast<void*>(NicknameEntryOnEnterClient),
                reinterpret_cast<void*>(NicknameEditOnClickClient),
                reinterpret_cast<void*>(NetRouteRefreshClient),
                reinterpret_cast<void*>(FlagButtonOnHoverClient));
        }
        else
        {
            // Re-assert it: SetActive on a surviving panel would restore the
            // byte and put the click-swallowing rectangle back over the row.
            MakeViewInputTransparent(g_NicknamePanelClient);
            NetRouteRefreshClient();
        }
    }

    // ---- Multiplayer pre-lobby ----------------------------------------------
    //
    // prelobby_screen.cpp builds the screen and calls in here for the widgets
    // it borrows from the lobby. Every callback is bound to the pre-lobby
    // globals, so nothing here can touch a lobby screen.

    static bool PreLobbyWidgetLive(void* widget)
    {
        return g_PreLobbyUiParent && widget &&
               IsWidgetLiveChildOfParent(g_PreLobbyUiParent, widget);
    }

    static void __cdecl FlagButtonOnClickPreLobby()
    {
        CycleSelectedFlag(1, "prelobby_button");
        if (PreLobbyWidgetLive(g_FlagPreviewPreLobby))
            UpdateFlagPreviewWidget(g_FlagPreviewPreLobby);
    }

    static void __cdecl FlagButtonOnClickPrevPreLobby()
    {
        CycleSelectedFlag(-1, "prelobby_button_prev");
        if (PreLobbyWidgetLive(g_FlagPreviewPreLobby))
            UpdateFlagPreviewWidget(g_FlagPreviewPreLobby);
    }

    static void __cdecl FlagButtonOnHoverPreLobby(void* /*param*/)
    {
        UpdateFlagSelectionUiLabel(g_FlagLabelPreLobby);
    }

    static void __cdecl NicknameEntryOnEnterPreLobby()
    {
        CompleteNicknameEdit(g_NicknameEntryPreLobby, nullptr, "prelobby");
    }

    static void __cdecl NicknameEditOnClickPreLobby()
    {
        BeginNicknameEdit(g_NicknameEntryPreLobby, g_PreLobbyUiParent, "prelobby_click");
    }

    void ResetPreLobbyLobbyWidgets()
    {
        if (g_NicknameEntryPreLobby)
        {
            if (g_ActiveNicknameEntry == g_NicknameEntryPreLobby)
            {
                g_ActiveNicknameEntry = nullptr;
                g_ActiveNicknameParent = nullptr;
                g_ReplaceNicknameOnNextInput = false;
            }
            if (g_NicknameEnterDispatchEntry == g_NicknameEntryPreLobby)
                g_NicknameEnterDispatchEntry = nullptr;
            if (g_PendingNicknameConfirmationEntry == g_NicknameEntryPreLobby)
                g_PendingNicknameConfirmationEntry = nullptr;
        }
        g_PreLobbyUiParent = nullptr;
        g_NicknamePanelPreLobby = nullptr;
        g_NicknameEntryPreLobby = nullptr;
        g_NicknameEditButtonPreLobby = nullptr;
        g_FlagButtonPreLobby = nullptr;
        g_FlagButtonPreLobbyRight = nullptr;
        g_FlagLabelPreLobby = nullptr;
        g_FlagPreviewPreLobby = nullptr;
    }

    bool CreatePreLobbyNicknameAndFlagWidgets(
        void* parent, float nicknameX, float nicknameY, float flagX, float flagY)
    {
        if (!parent || !g_BzrFn_ButtonCtor || !g_BzrFn_AddChild ||
            !g_BzrFn_SetOnClick || !g_BzrFn_SetOnHover)
            return false;

        if (g_PreLobbyUiParent != parent)
        {
            ResetPreLobbyLobbyWidgets();
            g_PreLobbyUiParent = parent;
        }

        // Gated exactly as the lobby gates them: the flag pair by
        // [Display] MultiplayerFlags, the name entry by [Network]
        // LobbyReadouts (inside CreateNicknameAndRouteWidgets).
        if (ShouldEnableMultiplayerFlagUi() && !PreLobbyWidgetLive(g_FlagButtonPreLobby))
        {
            CreateFlagButtonCommon(
                parent,
                flagX,
                flagY,
                &g_FlagButtonPreLobby,
                &g_FlagButtonPreLobbyRight,
                &g_FlagLabelPreLobby,
                &g_FlagPreviewPreLobby,
                reinterpret_cast<void*>(FlagButtonOnClickPrevPreLobby),
                reinterpret_cast<void*>(FlagButtonOnClickPreLobby),
                reinterpret_cast<void*>(FlagButtonOnHoverPreLobby));
        }

        // The panel is decoration only; a failed panel texture must not make
        // every setup pass add another entry.
        if (!PreLobbyWidgetLive(g_NicknameEntryPreLobby) ||
            !PreLobbyWidgetLive(g_NicknameEditButtonPreLobby))
        {
            // No OK button and no route readout: Continue applies the name and
            // the page has its own status line.
            CreateNicknameAndRouteWidgets(
                parent,
                nicknameX,
                nicknameY,
                &g_NicknamePanelPreLobby,
                &g_NicknameEntryPreLobby,
                &g_NicknameEditButtonPreLobby,
                nullptr,
                nullptr,
                reinterpret_cast<void*>(NicknameEntryOnEnterPreLobby),
                reinterpret_cast<void*>(NicknameEditOnClickPreLobby),
                nullptr,
                reinterpret_cast<void*>(FlagButtonOnHoverPreLobby));
        }

        return g_NicknameEntryPreLobby != nullptr || g_FlagButtonPreLobby != nullptr;
    }

    size_t GetPreLobbyLobbyWidgets(void** out, size_t capacity)
    {
        void* const widgets[] =
        {
            g_NicknamePanelPreLobby,
            g_NicknameEntryPreLobby,
            g_NicknameEditButtonPreLobby,
            g_FlagButtonPreLobby,
            g_FlagButtonPreLobbyRight,
            g_FlagPreviewPreLobby,
        };
        size_t count = 0;
        for (void* widget : widgets)
        {
            if (widget && out && count < capacity)
                out[count++] = widget;
        }
        return count;
    }

    bool IsPreLobbyLobbyWidget(void* view)
    {
        if (!view)
            return false;
        return view == g_NicknamePanelPreLobby || view == g_NicknameEntryPreLobby ||
               view == g_NicknameEditButtonPreLobby || view == g_FlagButtonPreLobby ||
               view == g_FlagButtonPreLobbyRight || view == g_FlagPreviewPreLobby;
    }

    // Fills the entry with the persisted nickname and the arrows' captions
    // when the screen is built. Called with visible=false it blanks them.
    void RefreshPreLobbyLobbyWidgets(bool visible)
    {
        if (!visible)
            EndNicknameEdit(g_NicknameEntryPreLobby);

        if (PreLobbyWidgetLive(g_NicknameEntryPreLobby))
        {
            if (visible)
            {
                // SetActive restores the input byte the panel had cleared, which
                // would put the click-swallowing rectangle back over the entry.
                MakeViewInputTransparent(g_NicknamePanelPreLobby);

                char current[128] = {};
                if (ReadBzrNetNickname(current, sizeof(current)) && current[0] != '\0')
                {
                    SyncNicknameEntryText(g_NicknameEntryPreLobby, current);
                }
                else if (g_BzrFn_TextEntryClear && g_BzrFn_SetTooltip)
                {
                    __try
                    {
                        g_BzrFn_TextEntryClear(g_NicknameEntryPreLobby);
                        g_BzrFn_SetTooltip(g_NicknameEntryPreLobby, kNicknamePlaceholder);
                    }
                    __except (EXCEPTION_EXECUTE_HANDLER)
                    {
                        Log(L"[PRELOBBY] nickname placeholder faulted code=0x%08X\n",
                            static_cast<uint32_t>(GetExceptionCode()));
                    }
                }
            }
            else if (g_BzrFn_SetTooltip)
            {
                __try
                {
                    g_BzrFn_SetTooltip(g_NicknameEntryPreLobby, "");
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    Log(L"[PRELOBBY] nickname blanking faulted code=0x%08X\n",
                        static_cast<uint32_t>(GetExceptionCode()));
                }
            }
        }

        if (g_BzrFn_SetButtonLabel)
        {
            __try
            {
                if (PreLobbyWidgetLive(g_FlagButtonPreLobby))
                    g_BzrFn_SetButtonLabel(g_FlagButtonPreLobby, visible ? "<" : "");
                if (PreLobbyWidgetLive(g_FlagButtonPreLobbyRight))
                    g_BzrFn_SetButtonLabel(g_FlagButtonPreLobbyRight, visible ? ">" : "");
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                Log(L"[PRELOBBY] flag arrow captions faulted code=0x%08X\n",
                    static_cast<uint32_t>(GetExceptionCode()));
            }
        }

        if (visible && PreLobbyWidgetLive(g_FlagPreviewPreLobby))
            UpdateFlagPreviewWidget(g_FlagPreviewPreLobby);
    }

    // True when the entry holds a usable name that is not already the
    // persisted one: Continue applies exactly in that case.
    bool PreLobbyGetPendingNickname(char* out, size_t outSize)
    {
        if (!out || outSize == 0)
            return false;
        out[0] = '\0';
        if (!PreLobbyWidgetLive(g_NicknameEntryPreLobby))
            return false;

        char text[192] = {};
        if (!ReadEngineStdString(
                static_cast<uint8_t*>(g_NicknameEntryPreLobby) + kUiTextEntryTextOffset,
                text, sizeof(text)))
        {
            return false;
        }

        const std::string trimmed = TrimAsciiCopy(text);
        if (trimmed.empty() || trimmed == kNicknamePlaceholder)
            return false;

        char persisted[128] = {};
        if (ReadBzrNetNickname(persisted, sizeof(persisted)) && trimmed == persisted)
            return false;

        std::snprintf(out, outSize, "%s", trimmed.c_str());
        return true;
    }

    // False when the name was not stored (invalid or not persisted).
    bool PreLobbyApplyNickname(const char* nickname, BzrNetNicknameResult& result)
    {
        EndNicknameEdit(g_NicknameEntryPreLobby);
        result = ApplyBzrNetNicknameForPreLobby(nickname);
        if (!IsAcceptedBzrNetNicknameResult(result))
            return false;
        if (PreLobbyWidgetLive(g_NicknameEntryPreLobby))
            SyncNicknameEntryText(g_NicknameEntryPreLobby, nickname);
        return true;
    }

    void PreLobbyEndNicknameEdit()
    {
        EndNicknameEdit(g_NicknameEntryPreLobby);
    }

    // The pre-lobby screen's char slot hands every typed character here first.
    // Consumed only while the pre-lobby nickname edit is the active one; the
    // existing AppendChar detour then does the usual replace-on-first-key and
    // Enter routing.
    bool PreLobbyForwardChar(uint8_t character)
    {
        void* const entry = g_NicknameEntryPreLobby;
        if (!entry || g_ActiveNicknameEntry != entry ||
            g_ActiveNicknameParent != g_PreLobbyUiParent ||
            !g_BzrFn_TextEntryAppendChar || !PreLobbyWidgetLive(entry))
        {
            return false;
        }
        __try
        {
            g_BzrFn_TextEntryAppendChar(entry, character);
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            Log(L"[PRELOBBY] nickname key routing faulted code=0x%08X\n",
                static_cast<uint32_t>(GetExceptionCode()));
        }
        return true;
    }
}
