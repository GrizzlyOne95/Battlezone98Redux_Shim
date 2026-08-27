#pragma once

// OpenShim backend-selection boot-request and Ogre.cfg transport logic.
//
// Owns the decision core for the startup backend seam documented in
// reverse_engineering/renderer_startup_backend_selection_20260825.md:
//
//   persistent requested renderer (openshim.ini [Graphics] Renderer)
//     + launch-scoped CLI override (/renderer:dx9|dx11|gl)
//       -> effective request for this boot
//         -> stock renderer-selection ladder (untouched)
//           -> observed effective renderer
//             -> diagnostic classification
//
// The key ownership invariant: Redux may rewrite Ogre.cfg at will (it does so
// on every clean exit, after in-game renderer changes, and even on failed
// boots); it must never thereby redefine OpenShim's persistent requested
// renderer, which lives only in openshim.ini.
//
// Everything here is pure and free of Win32/Ogre dependencies so the decision
// table stays unit-testable (tests/backend_selection_tests.cpp,
// scripts/run_backend_selection_tests.ps1), mirroring render_profile.h/cpp.

#include <cstdint>
#include <string>
#include <string_view>

#include "render_profile.h"

namespace BZROpenShim::BackendSelection
{
    // Where this boot's non-Auto request came from. Persistent = openshim.ini;
    // CliOverride = /renderer:... seen on this boot's command line (stock
    // absorbs that choice into Ogre.cfg via saveConfig(), which is exactly why
    // OpenShim must re-assert the persistent preference on later boots).
    enum class RequestSource : uint8_t
    {
        None = 0,
        Persistent = 1,
        CliOverride = 2,
    };

    // Token vocabulary shared by the INI value space and the command line.
    // GL is recognized because stock supports it (/renderer:gl), but OpenShim
    // has no GL capability in its resolver, so a GL result can never become a
    // transport request; callers fall through to stock selection for it.
    enum class RendererToken : uint8_t
    {
        None = 0,
        Dx9 = 1,
        Dx11 = 2,
        Gl = 3,
    };

    // Case-insensitive single-token classification: dx9/d3d9/directx9,
    // dx11/d3d11/directx11, gl/opengl. Anything else is None.
    RendererToken ClassifyRendererToken(std::string_view token);

    // Scans a full command line for /renderer:VALUE, -renderer=VALUE or the
    // '+' prefixed form (the stock parser accepts all three separators).
    // Case-insensitive on both key and value. When several occurrences exist
    // the LAST one wins, mirroring the stock strtok loop's overwrite behavior.
    // Returns None when no renderer token is present.
    RendererToken FindCommandLineRendererOverride(std::string_view commandLine);

    struct BootRequest
    {
        RenderProfiles::RendererBackend backend =
            RenderProfiles::RendererBackend::Auto;
        RequestSource source = RequestSource::None;
    };

    // Effective request for one boot. Priority:
    //   CLI DX9/DX11 > persistent DX9/DX11 > Auto (stock).
    // A GL CLI token is honored as "explicit but unsupported": it yields an
    // Auto request with source None so stock selection proceeds untouched
    // (OpenShim never transports GL). An explicit CLI token beats the
    // persistent preference for THIS boot only.
    BootRequest ResolveBootRequest(RenderProfiles::RendererBackend persistent,
                                   RendererToken cliToken);

    // Exact Ogre subsystem names required by Root::getRenderSystemByName /
    // Ogre.cfg's "Render System=" line. Returns nullptr for Auto.
    const char* SubsystemNameFor(RenderProfiles::RendererBackend backend);

    // Inverse mapping used when classifying post-boot stock state.
    bool BackendFromSubsystemName(std::string_view name,
                                  RenderProfiles::RendererBackend& out);

    // Value of the first line starting with "Render System=" (leading
    // whitespace tolerated); empty view when absent.
    std::string_view ExtractStockRenderSystemValue(std::string_view cfgText);

    // Rewrites ONLY the "Render System=" line inside an in-memory Ogre.cfg
    // image, preserving every other byte including EOL style. Appends the
    // line when absent. Fails (leaving the text untouched) when the image is
    // empty or contains bytes outside plain ASCII — the refuse-to-touch
    // policy that keeps unexpected encodings on the stock path.
    bool ApplyTransportToConfigImage(std::string& cfgText,
                                     std::string_view subsystemName);

    // Minimal Ogre.cfg image used when the file does not exist yet: a single
    // keyed line in stock's own CRLF style. Stock's restore/default-seeding
    // path completes every remaining section on this boot (the game recreates
    // the full file even from nothing, per RE matrix case cfg-missing).
    // Returns an empty string for an empty subsystem name (refuse-to-write).
    std::string BuildMinimalConfigImage(std::string_view subsystemName);

    // Process-unique transport temporary filename:
    //   "Ogre.cfg.openshim-<pid>.tmp"
    // Two concurrent game processes therefore never write the same temp file,
    // and cleanup paths only ever delete the exact name this process made.
    std::string MakeTransportTempFileName(uint32_t processId);

    // True unless the kill-switch value disables the transport. Accepts the
    // canonical "0" plus false/no/off aliases, case-insensitive, surrounding
    // whitespace tolerated. Any other text (including empty) means enabled.
    bool ParseTransportEnabled(std::string_view value);

    // Whether a ConfigFile::load filename argument names the startup config:
    // exactly "Ogre.cfg" or a path ending in "\Ogre.cfg" / "/Ogre.cfg",
    // case-insensitive. Anything else is some other configuration load and
    // must pass through untouched.
    bool IsStartupConfigFilename(std::string_view filename);

    // Post-boot classification for diagnostics. See
    // renderer_startup_backend_selection_20260825.md §"diagnostics".
    enum class SelectionReason : uint8_t
    {
        None = 0,              // requested == effective (persistent preference)
        CliOverride = 1,       // requested == effective (this boot came from CLI)
        BackendUnavailable = 2,// stock ladder fell back AND rewrote the transport
        UnresolvedMismatch = 3,// identified != requested while transport intact
        NoEstablishment = 4,   // observation window ended with no active renderer
        Stock = 5,             // no explicit request this boot
    };

    const char* ReasonName(SelectionReason reason);

    struct OutcomeInput
    {
        bool haveRequest = false;
        RenderProfiles::RendererBackend requested =
            RenderProfiles::RendererBackend::Auto;
        RequestSource source = RequestSource::None;
        bool backendIdentified = false;
        RenderProfiles::ActiveBackend effective = RenderProfiles::ActiveBackend::DX9;
        // Post-boot value of Ogre.cfg's "Render System=" line ("" if absent);
        // distinguishes a burned transport (backend-unavailable) from other
        // mismatches.
        std::string_view stockLineAfterBoot;
    };

    SelectionReason ClassifyOutcome(const OutcomeInput& input);
}
