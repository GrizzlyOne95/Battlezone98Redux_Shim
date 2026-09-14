// Data-driven replacement for Redux's hard-coded `abstor` tug capability.
//
// Stock GOG v2.2.301:
//   GameObject::tug capability getter @ 0x0046D0C0 -> [this + 0x220]
//   Building::Building @ 0x0047E9C0 sets +0x220 from +0xDC only when the
//   object's own packed ODF name is exactly "abstor".
//
// OpenShim preserves that behavior when no override is present and adds:
//
//   [BuildingClass]
//   tugEnabled = true|false
//
// `true` mirrors the stock constructor assignment (+0xDC -> +0x220).
// `false` masks the getter result. Missing/invalid keys always fall through to
// stock, preserving abstor and Artifact compatibility.

#include "hook_engine.h"
#include "shim_log.h"

#include <Windows.h>
#include <algorithm>
#include <cctype>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <filesystem>
#include <string>
#include <unordered_map>
#include <vector>

namespace BZROpenShim
{
namespace
{
    constexpr uintptr_t kTugCapabilityGetterAddress = 0x0046D0C0u;
    constexpr size_t kTugCapabilityDetourLength = 6;
    constexpr size_t kGameObjectClassOffset = 0xF8;
    constexpr size_t kGameObjectHandleOffset = 0xDC;
    constexpr size_t kGameObjectTugCapabilityOffset = 0x220;
    constexpr size_t kGameObjectClassOdfNameOffset = 0x30;
    constexpr size_t kOdfTokenLength = 8;
    constexpr char kTugSection[] = "BuildingClass";
    constexpr char kTugKey[] = "tugEnabled";

    enum class TugOdfOverride : uint8_t
    {
        Missing = 0,
        Disabled = 1,
        Enabled = 2,
    };

    using FnTugCapability = uint32_t (__thiscall*)(void*);

    InlineDetour32 g_TugCapabilityDetour;
    FnTugCapability g_OriginalTugCapability = nullptr;
    std::unordered_map<std::string, TugOdfOverride> g_TugOverrideCache;
    bool g_TugInstallFailureLogged = false;

    void AppendUniqueTugPath(std::vector<std::filesystem::path>& out,
                             const std::filesystem::path& candidate)
    {
        if (candidate.empty())
            return;
        if (std::find(out.begin(), out.end(), candidate) != out.end())
            return;
        out.push_back(candidate);
    }

    void AppendImmediateTugSubdirectories(
        const std::filesystem::path& parent,
        std::vector<std::filesystem::path>& out)
    {
        if (parent.empty())
            return;

        std::error_code ec;
        if (!std::filesystem::is_directory(parent, ec) || ec)
            return;

        for (std::filesystem::directory_iterator it(parent, ec), end;
             !ec && it != end;
             it.increment(ec))
        {
            if (ec)
                break;
            std::error_code entryEc;
            if (it->is_directory(entryEc) && !entryEc)
                AppendUniqueTugPath(out, it->path());
        }
    }

    std::filesystem::path GetTugGameDirectory()
    {
        char modulePath[MAX_PATH] = {};
        const DWORD len = GetModuleFileNameA(
            nullptr, modulePath, static_cast<DWORD>(sizeof(modulePath)));
        if (len == 0 || len >= sizeof(modulePath))
            return {};
        return std::filesystem::path(modulePath).parent_path();
    }

    std::filesystem::path TryGetTugWorkshopDirectory(
        const std::filesystem::path& gameDir)
    {
        if (gameDir.empty())
            return {};

        const std::string normalized = gameDir.lexically_normal().string();
        std::string lower = normalized;
        std::transform(lower.begin(), lower.end(), lower.begin(),
            [](unsigned char ch) {
                if (ch == '\\')
                    return '/';
                return static_cast<char>(std::tolower(ch));
            });

        constexpr const char* marker = "/steamapps/common/";
        const size_t pos = lower.find(marker);
        if (pos == std::string::npos)
            return {};

        return std::filesystem::path(normalized.substr(0, pos)) /
            "steamapps" / "workshop" / "content" / "301650";
    }

    std::vector<std::filesystem::path> GetTugOdfDirectories()
    {
        std::vector<std::filesystem::path> directories;
        const std::filesystem::path gameDir = GetTugGameDirectory();
        if (gameDir.empty())
            return directories;

        std::vector<std::filesystem::path> roots;
        AppendImmediateTugSubdirectories(gameDir / "addon", roots);
        AppendImmediateTugSubdirectories(gameDir / "mods", roots);
        AppendImmediateTugSubdirectories(gameDir / "packaged_mods", roots);
        AppendImmediateTugSubdirectories(TryGetTugWorkshopDirectory(gameDir), roots);

        for (const auto& root : roots)
        {
            AppendUniqueTugPath(directories, root / "ODF");
            AppendUniqueTugPath(directories, root / "_Release" / "ODF");
            AppendUniqueTugPath(directories, root / "_Source" / "ODF");
        }

        AppendUniqueTugPath(directories, gameDir / "Edit" / "stock");
        return directories;
    }

    bool TryResolveTugOdfPath(const char* odfToken,
                              std::filesystem::path& outPath)
    {
        outPath.clear();
        if (!odfToken || !*odfToken)
            return false;

        for (const auto& directory : GetTugOdfDirectories())
        {
            std::error_code ec;
            const auto mpPath = directory /
                (std::string(odfToken) + "_mp.odf");
            if (std::filesystem::is_regular_file(mpPath, ec) && !ec)
            {
                outPath = mpPath;
                return true;
            }

            ec.clear();
            const auto normalPath = directory /
                (std::string(odfToken) + ".odf");
            if (std::filesystem::is_regular_file(normalPath, ec) && !ec)
            {
                outPath = normalPath;
                return true;
            }
        }

        return false;
    }

    bool TryGetTugOdfToken(void* objectPtr,
                           char (&outToken)[kOdfTokenLength + 1])
    {
        outToken[0] = '\0';
        if (!objectPtr)
            return false;

        __try
        {
            const auto* objectBytes = reinterpret_cast<const uint8_t*>(objectPtr);
            const void* objectClass = *reinterpret_cast<void* const*>(
                objectBytes + kGameObjectClassOffset);
            if (!objectClass)
                return false;

            const auto* classBytes = reinterpret_cast<const uint8_t*>(objectClass);
            std::memcpy(outToken,
                        classBytes + kGameObjectClassOdfNameOffset,
                        kOdfTokenLength);
            outToken[kOdfTokenLength] = '\0';
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            outToken[0] = '\0';
            return false;
        }

        size_t length = 0;
        while (length < kOdfTokenLength && outToken[length] != '\0')
        {
            const unsigned char ch =
                static_cast<unsigned char>(outToken[length]);
            if (!(std::isalnum(ch) || ch == '_' || ch == '-'))
            {
                outToken[0] = '\0';
                return false;
            }
            outToken[length] = static_cast<char>(std::tolower(ch));
            ++length;
        }

        return length != 0;
    }

    bool TryParseTugBool(const char* raw, bool& outValue)
    {
        if (!raw)
            return false;

        std::string value(raw);
        value.erase(std::remove_if(value.begin(), value.end(),
            [](unsigned char ch) { return std::isspace(ch) != 0; }), value.end());
        std::transform(value.begin(), value.end(), value.begin(),
            [](unsigned char ch) { return static_cast<char>(std::tolower(ch)); });

        if (value == "1" || value == "true" || value == "yes" ||
            value == "on" || value == "enabled")
        {
            outValue = true;
            return true;
        }
        if (value == "0" || value == "false" || value == "no" ||
            value == "off" || value == "disabled")
        {
            outValue = false;
            return true;
        }
        return false;
    }

    TugOdfOverride ReadTugOdfOverride(const char* odfToken)
    {
        std::filesystem::path odfPath;
        if (!TryResolveTugOdfPath(odfToken, odfPath))
            return TugOdfOverride::Missing;

        char value[32] = {};
        const DWORD copied = GetPrivateProfileStringA(
            kTugSection,
            kTugKey,
            "",
            value,
            static_cast<DWORD>(sizeof(value)),
            odfPath.string().c_str());
        if (copied == 0)
            return TugOdfOverride::Missing;

        bool enabled = false;
        if (!TryParseTugBool(value, enabled))
        {
            LogShimA(LogLevel::Warn, "TUGODF",
                "ignoring invalid [BuildingClass] tugEnabled='%s' in %s",
                value, odfPath.string().c_str());
            return TugOdfOverride::Missing;
        }

        LogShimA(LogLevel::Info, "TUGODF",
            "ODF %.8s sets [BuildingClass] tugEnabled=%s (%s)",
            odfToken,
            enabled ? "true" : "false",
            odfPath.string().c_str());
        return enabled ? TugOdfOverride::Enabled : TugOdfOverride::Disabled;
    }

    TugOdfOverride GetTugOdfOverride(const char* odfToken)
    {
        if (!odfToken || !*odfToken)
            return TugOdfOverride::Missing;

        const auto found = g_TugOverrideCache.find(odfToken);
        if (found != g_TugOverrideCache.end())
            return found->second;

        const TugOdfOverride value = ReadTugOdfOverride(odfToken);
        g_TugOverrideCache.emplace(odfToken, value);
        return value;
    }

    uint32_t ReadStockTugCapability(void* objectPtr)
    {
        if (g_OriginalTugCapability)
            return g_OriginalTugCapability(objectPtr);
        if (!objectPtr)
            return 0;

        __try
        {
            return *reinterpret_cast<const uint32_t*>(
                reinterpret_cast<const uint8_t*>(objectPtr) +
                kGameObjectTugCapabilityOffset);
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            return 0;
        }
    }

    uint32_t __fastcall TugCapabilityOdfHook(void* objectPtr, void* /*edx*/)
    {
        const uint32_t stockResult = ReadStockTugCapability(objectPtr);

        char odfToken[kOdfTokenLength + 1] = {};
        if (!TryGetTugOdfToken(objectPtr, odfToken))
            return stockResult;

        const TugOdfOverride overrideValue = GetTugOdfOverride(odfToken);
        if (overrideValue == TugOdfOverride::Missing)
            return stockResult;
        if (overrideValue == TugOdfOverride::Disabled)
            return 0;
        if (stockResult != 0)
            return stockResult;

        // Mirror Building::Building/Artifact exactly: the value copied into the
        // tug capability field is the object's already-assigned native handle.
        __try
        {
            auto* bytes = reinterpret_cast<uint8_t*>(objectPtr);
            const uint32_t handle = *reinterpret_cast<const uint32_t*>(
                bytes + kGameObjectHandleOffset);
            if (handle == 0)
                return 0;

            *reinterpret_cast<uint32_t*>(
                bytes + kGameObjectTugCapabilityOffset) = handle;
            return handle;
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            return 0;
        }
    }

    void InstallTugOdfToggleIfPossible()
    {
        if (g_TugCapabilityDetour.trampoline)
            return;

        // FUN_0046D0C0 begins `mov eax,[ecx+0x220]`. The byte guard makes the
        // GOG address fail closed on an unknown executable instead of patching
        // whatever happens to live there.
        static const uint8_t expected[kTugCapabilityDetourLength] =
            { 0x8B, 0x81, 0x20, 0x02, 0x00, 0x00 };

        if (!InstallInlineDetour32(
                g_TugCapabilityDetour,
                kTugCapabilityGetterAddress,
                reinterpret_cast<void*>(&TugCapabilityOdfHook),
                kTugCapabilityDetourLength,
                expected,
                sizeof(expected)))
        {
            if (!g_TugInstallFailureLogged)
            {
                LogShimA(LogLevel::Warn, "TUGODF",
                    "tug capability hook was not installed; stock behavior retained");
                g_TugInstallFailureLogged = true;
            }
            return;
        }

        g_OriginalTugCapability = reinterpret_cast<FnTugCapability>(
            g_TugCapabilityDetour.trampoline);
        LogShimA(LogLevel::Info, "TUGODF",
            "installed [BuildingClass] tugEnabled override with stock fallback");
    }
}
}
