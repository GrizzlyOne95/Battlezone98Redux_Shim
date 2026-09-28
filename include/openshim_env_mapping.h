#pragma once

// The decision half of the OPENSHIM_* / BZR_* environment redirect.
//
// openshim_env_config.h force-includes a GetEnvironmentVariableA replacement
// into every plugin translation unit, so a legacy environment name is answered
// from openshim.ini before the real process environment. The order is:
//
//   1. A capture/diagnostic override name (IsCaptureOverrideName) that is set
//      in the process environment wins, so a capture wrapper can switch on a
//      shipped-OFF trace without rewriting the player's INI.
//   2. The friendly mapping: a known name reads its documented [Section] Key
//      (booleans normalised to "1"/"0", DISABLE_* names inverted).
//   3. The verbatim [Environment] entry in openshim.ini, for any name.
//   4. The real process environment.
//
// Everything here is free of Windows calls: the INI files and the process
// environment are passed in, so the unit tests drive the whole order without
// a plugin directory. openshim_env_config.cpp supplies the Win32 readers.

#include <cstdint>
#include <functional>
#include <string>

namespace BZROpenShim
{
namespace EnvConfig
{
    // The INI files the redirect reads, both beside the executable.
    enum class IniFile
    {
        Main,               // openshim.ini
        ProducerBuildMenus, // openshim_producer_build_menus.ini
    };

    const char* IniFileName(IniFile file);

    // Reads [section] key from `file`. Returns true and sets `out` only when
    // the key is present with a non-empty value; a missing file, section or
    // key, or an empty value, all return false.
    using IniReader = std::function<bool(IniFile file, const char* section, const char* key, std::string& out)>;

    // GetEnvironmentVariableA's contract: copies the value into `buffer` and
    // returns its length, or returns the required size including the
    // terminator when `size` is too small; 0 when the variable is not set.
    using EnvironmentReader = std::function<uint32_t(const char* name, char* buffer, uint32_t size)>;

    // True for the capture names whose process-environment value, when set,
    // beats openshim.ini (step 1 above).
    bool IsCaptureOverrideName(const char* name);

    // Steps 2 and 3: the INI answer for `name`, if it has one.
    bool TryReadFromIni(const char* name, const IniReader& ini, std::string& out);

    // GetEnvironmentVariableA's buffer contract for a value OpenShim supplies.
    uint32_t CopyEnvironmentValue(const std::string& value, char* buffer, uint32_t size);

    // The whole lookup. `ini` is null when the plugin directory is unknown,
    // which skips steps 2 and 3.
    uint32_t GetEnvironmentValue(const char* name,
                                 char* buffer,
                                 uint32_t size,
                                 const IniReader* ini,
                                 const EnvironmentReader& env);
}
}
