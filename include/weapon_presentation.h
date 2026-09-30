#pragma once

// Engine-independent singleplayer weapon presentation. Native hooks supply
// copied identities/poses; this layer never reads game memory or changes aim.
// The native firing/factory ABI still needs qualification before a backend is
// connected. See Docs/WEAPON_PRESENTATION_IMPLEMENTATION.md.

#include "weapon_convergence.h"

#include <array>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <optional>
#include <string>
#include <string_view>

namespace BZROpenShim::WeaponPresentation
{
    using Matrix = WeaponConvergence::Matrix;

    inline constexpr float kRecoilKick = 0.6f;
    inline constexpr float kRecoilReturnSpeed = 3.0f;
    inline constexpr size_t kMeshIdBytes = 8;
    inline constexpr size_t kMaxBindings = 4096;

    struct FlashConfig
    {
        std::string effect;
        float duration = 0.0f;
        bool Valid() const noexcept;
    };

    // An absent value inherits. An explicitly empty name disables; malformed
    // duration must be supplied as an invalid value, never as "absent".
    FlashConfig ResolveFlashConfig(const FlashConfig& parent,
        std::optional<std::string_view> name,
        std::optional<float> duration);

    using MeshId = std::array<char, kMeshIdBytes>;
    std::optional<MeshId> ParseMeshId(std::string_view name) noexcept;
    bool ValidPose(const Matrix& pose) noexcept;

    struct MeshNodeView
    {
        MeshId id = {};
        uintptr_t child = 0;
        uintptr_t sibling = 0;
    };
    using ReadMeshNode = bool (*)(uintptr_t, MeshNodeView&, void*);
    enum class MeshLookupStatus { Found, NotFound, Ambiguous, InvalidGraph, LimitExceeded };
    struct MeshLookupResult
    {
        MeshLookupStatus status = MeshLookupStatus::NotFound;
        uintptr_t node = 0;
    };
    // Reader must validate the memory/lifetime. Traverse bounded child/sibling
    // edges; refuse cycles, duplicate matches, failed reads and partial graphs.
    MeshLookupResult FindMeshNode(uintptr_t root, const MeshId& id,
        ReadMeshNode read, void* user, size_t limit = kMaxBindings);

    struct Identity
    {
        uintptr_t address = 0;
        uint64_t lifetime = 0; // native object lifetime/handle, not just address
        bool Valid() const noexcept { return address != 0 && lifetime != 0; }
        bool operator==(const Identity& rhs) const noexcept;
        bool operator<(const Identity& rhs) const noexcept;
    };

    struct BindingToken
    {
        uint64_t epoch = 0;
        uint64_t serial = 0;
        bool Valid() const noexcept { return epoch != 0 && serial != 0; }
    };

    struct Settings
    {
        bool muzzleFlash = false;
        bool meshRecoil = false;
    };

    struct RecoilBinding
    {
        Identity node;
        Matrix unrecoiledPose = WeaponConvergence::Identity();
    };

    struct BindRequest
    {
        Identity owner;
        Identity weapon;
        FlashConfig flash;
        std::optional<RecoilBinding> recoil;
    };

    struct ShotResult
    {
        bool observed = false;
        bool flashStarted = false;
        bool recoilReset = false;
    };

    class Backend
    {
    public:
        virtual ~Backend() = default;
        // storage has a stable address until detach clears it or scene loss is
        // confirmed. Native renderers can keep &storage and zero it on expiry.
        // Backend methods must catch native faults, validate identities and run
        // only on the engine's safe rendering thread. No callbacks from Fire.
        virtual bool CreateFlash(std::string_view effect, const Matrix& pose,
            void*& storage) noexcept = 0;
        virtual bool UpdateFlash(void* renderer, const Matrix& pose) noexcept = 0;
        virtual bool DetachFlash(void*& storage) noexcept = 0;
        // This writes a presentation pose only; never the gameplay MAT_3D.
        virtual bool ApplyRecoil(const Identity& owner, const Identity& node,
            const Matrix& visualPose) noexcept = 0;
    };

    struct Snapshot
    {
        size_t bindings = 0;
        size_t retiredBindings = 0;
        size_t nativeAttachments = 0;
        size_t sharedRecoilNodes = 0;
    };

    class Runtime
    {
    public:
        Runtime();
        ~Runtime();
        Runtime(const Runtime&) = delete;
        Runtime& operator=(const Runtime&) = delete;
        Runtime(Runtime&&) = delete;
        Runtime& operator=(Runtime&&) = delete;

        void Configure(Settings settings) noexcept;
        // Production bridge passes the existing IsSinglePlayerSession() gate.
        // A transition out invalidates tokens and queues restoration/detach.
        void SetSession(bool singleplayer, bool missionRunning) noexcept;
        bool AcceptingBindings() const noexcept;
        std::optional<BindingToken> Bind(const BindRequest& request);
        bool Release(BindingToken token) noexcept;

        // Called only AFTER the native path has accepted/committed a shot.
        // Serial is monotonically increasing per binding, including pellets'
        // shared logical shot. Matrix is the copied final factory argument.
        ShotResult Fire(BindingToken token, uint64_t shotSerial,
            const Matrix& committedPose) noexcept;
        bool SetMuzzlePose(BindingToken token, const Matrix& worldPose) noexcept;
        // Static-translation node contract: refresh live orientation without
        // recapturing rest from an already displaced renderer pose.
        bool SetRecoilPose(const Identity& owner, const Identity& node,
            const Matrix& unrecoiledPose) noexcept;

        // Call at global simulation-pass entry, before accepted shots in that
        // pass. A repeated serial cannot recover a shared node twice. Rendering
        // never supplies dt. Zero dt freezes; invalid dt/serial is rejected.
        bool BeginSimulationStep(uint64_t stepSerial, float dt) noexcept;
        void SynchronizeVisuals(Backend& backend) noexcept;

        // Paired around native scene destruction. Nested clearScene ->
        // destroyAllMovableObjects retains stable slots through the outer return.
        // Completion removes only cleared slots: Ogre destruction alone does
        // not establish that native ParticleRender back-references are gone.
        void BeginSceneTeardown() noexcept;
        void EndSceneTeardown() noexcept;
        // Use only AFTER native objects/back-references have ceased to exist.
        void InvalidateResources() noexcept;
        Snapshot Inspect() const noexcept;
        float RecoilDisplacement(const Identity& owner, const Identity& node) const noexcept;

    private:
        struct Impl;
        std::unique_ptr<Impl> impl_;
    };
}
