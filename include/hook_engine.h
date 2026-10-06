#pragma once
#include <cstdint>
#include <vector>
#include <string>

namespace HookEngine
{
    enum class PatchType : uint8_t
    {
        JMP5,       // 5-byte relative JMP:  E9 rel32
        REL32,      // 4-byte relative operand (CALL/JMP rel32)
        DWORD,      // 4-byte DWORD overwrite
        BYTE1,      // 1-byte overwrite
        BYTES,      // raw byte array
    };

    struct PatchDef
    {
        uint32_t address;
        PatchType type;
        std::vector<uint8_t> payload;
        std::string name;
        bool verified;
        std::vector<uint8_t> expected_original;
    };

    struct ScanTarget {
        std::string name;
        std::string ida_pattern;
        uint32_t offset;
        uint32_t expected_size;
        uint32_t fallback_addr;
        bool require_unique = false;
    };

    // Core Memory Utilities
    bool ApplyPatch(const PatchDef& patch);
    // ApplyPatch for a whole list under one suspension of the other threads
    // instead of one per patch. Returns each patch's outcome in order, so the
    // caller logs after the threads are running again.
    std::vector<bool> ApplyPatches(const std::vector<PatchDef>& patches);
    // A write into an executable page is committed with every other thread
    // of the process held and none of them executing inside the site, then
    // the instruction cache is flushed; a site some thread keeps running
    // through is left untouched and reported. A write into data is plain.
    bool WriteMemory(uint32_t address, const void* data, size_t len);
    bool ReadMemory(uint32_t address, void* buffer, size_t len);

    // Serialises every code write (ApplyPatch, WriteMemory, the inline-detour
    // installer) and the deferred-hook retry across threads: the patch
    // thread's settle loop and the game thread's SDK bridges both install
    // hooks, and two installers on one site used to race between the
    // "already installed" check and the write. Recursive, because
    // RetryDeferredRuntimeHooks holds it while the installers it fans out to
    // take it again.
    class CodePatchLock
    {
    public:
        CodePatchLock();
        ~CodePatchLock();
        CodePatchLock(const CodePatchLock&) = delete;
        CodePatchLock& operator=(const CodePatchLock&) = delete;
    };

    // Pattern Scanning.
    //
    // missesAreProvisional says a retry pass is still to come, so a
    // require_unique target that finds nothing is reported as pending rather
    // than failed. SteamStub leaves parts of .text unsettled for the first
    // ~100ms after launch; a miss in that window means "too early", not
    // "wrong signature", and logging it as a failure sends readers hunting
    // for a build difference that is not there.
    void ScanForPatterns(const std::string& moduleName, std::vector<PatchDef>& patches, const std::vector<ScanTarget>& targets, bool missesAreProvisional = false);
    std::vector<uint16_t> ParseIdaPattern(const std::string& hex);

    // Declarative address resolution ("resolves" in scripts/patches.json).
    //
    // Returns the address the name stands for, or 0 when neither the signature
    // nor a fallback constant produced one. Successful resolutions are cached,
    // so a caller that runs before the target module is mapped can simply ask
    // again later; each attempt emits one [RESOLVE] log line naming the match
    // count, the scanned address, the fallback, and the entry's identity note.
    uint32_t ResolveNamedAddress(const char* name);

    // Fixed engine addresses ("engine_addresses" in scripts/patches.json).
    //
    // Looks the name up and, for a code row, compares the guard bytes with
    // what is mapped at the address now. Bound means the address may be used;
    // BoundData means a data row, taken as recorded; every other status
    // returns 0 in outAddress, so the caller's pointer stays null and the
    // feature built on it stands down. Nothing is cached: a Mismatch on Steam
    // can be "SteamStub has not settled this page yet", so callers may ask
    // again. Logs nothing; the caller reports.
    enum class EngineAddressStatus
    {
        Bound,
        BoundData,
        Missing,    // no row with that name (or no patches.json)
        Mismatch,   // the guard bytes differ from what is mapped
        Unreadable, // the address could not be read
    };
    EngineAddressStatus ResolveEngineAddress(const char* name, uint32_t& outAddress);

    // A feature's engine addresses, bound all or nothing. Every row must be
    // Bound (code) or BoundData (data); otherwise every output is set to 0,
    // one log line names the rows that failed and why, and false comes back so
    // the feature stands down. On Steam a Mismatch can be SteamStub still
    // decrypting the page, so mismatched rows get about a second of retries.
    struct EngineRow
    {
        const char* name;
        uint32_t* out;
    };
    bool BindEngineRows(const char* feature, const EngineRow* rows, size_t count);

    // One engine_addresses row by name, for addresses several files share:
    // the address when the row is Bound or BoundData, else 0 (logged once per
    // name). Successes are cached; a failure is asked again next time, since
    // on Steam it can be a page SteamStub has not finished with. Never waits.
    uint32_t EngineAddress(const char* name);
    template <size_t N>
    bool BindEngineRows(const char* feature, const EngineRow (&rows)[N])
    {
        return BindEngineRows(feature, rows, N);
    }

    // Locates scripts/patches.json: working directory first, then the exe's
    // own directory, since the game is routinely launched from elsewhere.
    // Empty when neither exists.
    std::string FindPatchesJsonPath();

    // Which battlezone98redux.exe build is running, and which of the builds
    // patches.json describes it is (build_overlay.h). Decided once, from the
    // exe's PE link timestamp, the first time anything reads patches.json.
    enum class BuildMatch : uint8_t
    {
        Base,        // the build the file's top-level entries describe
        Overlay,     // a build described by one of the file's build_overlays
        Unknown,     // the file names builds and this is none of them
        Unversioned, // the file names no build (older patches.json)
    };
    struct BuildInfo
    {
        uint32_t exeStamp = 0;
        BuildMatch match = BuildMatch::Unversioned;
        std::string label;  // the selected build's label
        std::string known;  // every build label the file names, comma separated
        size_t replaced = 0;
        size_t dropped = 0;
    };
    const BuildInfo& GetBuildInfo();

    // patches.json as it applies to the running build: the base entries, the
    // selected overlay merged over them, or no address entries at all for an
    // unknown build. Every reader of the file goes through this, so the patch
    // list and the resolve table cannot come from different builds. Empty when
    // the file is missing.
    const std::string& EffectivePatchesText();

    // True when the running exe is the build that the addresses still written
    // as literals in feature code were taken from. A feature built on such a
    // literal must stand down when this is false: no patches.json can move it.
    bool IsReferenceBuild();

    // The gate for a feature whose engine addresses are still literals in its
    // code: true on the reference build; on any other build false, with one
    // log line per feature naming it. Put at every entry point that installs,
    // writes or reads through those literals, and remove it once the
    // feature's addresses come from patches.json.
    bool LiteralAddressesApply(const char* feature);

    // Helpers
    void* ResolveRelCallTarget(uint32_t instrAddr);
    void* ResolveRelCallTargetWithRetry(uint32_t instrAddr, int maxAttempts, uint32_t delayMs);
    std::vector<uint8_t> MakeJmp5Payload(uint32_t src, uint32_t dst, size_t total_len = 5);
}
