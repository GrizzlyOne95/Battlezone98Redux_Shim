#include "weapon_presentation.h"

#include <algorithm>
#include <cmath>
#include <limits>
#include <map>
#include <set>
#include <tuple>
#include <utility>
#include <vector>

namespace BZROpenShim::WeaponPresentation
{
    bool FlashConfig::Valid() const noexcept
    {
        return !effect.empty() && effect.size() < 128 &&
            effect.find('\0') == std::string::npos &&
            std::isfinite(duration) && duration > 0.0f;
    }

    FlashConfig ResolveFlashConfig(const FlashConfig& parent,
        std::optional<std::string_view> name, std::optional<float> duration)
    {
        FlashConfig result = parent;
        if (name)
        {
            if (name->empty())
                result.effect.clear();
            else
                result.effect.assign(name->data(), name->size());
        }
        if (duration)
            result.duration = *duration;
        if (!result.Valid())
            return {};
        return result;
    }

    std::optional<MeshId> ParseMeshId(std::string_view name) noexcept
    {
        if (name.empty() || name.size() > kMeshIdBytes)
            return std::nullopt;
        MeshId result = {};
        for (size_t i = 0; i < name.size(); ++i)
        {
            const unsigned char ch = static_cast<unsigned char>(name[i]);
            if (ch < 0x21 || ch > 0x7e)
                return std::nullopt;
            result[i] = static_cast<char>(ch);
        }
        return result;
    }

    bool ValidPose(const Matrix& pose) noexcept
    {
        using namespace WeaponConvergence;
        if (!IsFinite(pose) || !IsRotationOrthonormal(pose))
            return false;
        const Vec3 right = { pose.rightX, pose.rightY, pose.rightZ };
        const Vec3 up = Up(pose);
        const Vec3 front = Front(pose);
        return std::fabs(Dot(right, up)) < 0.01f &&
            std::fabs(Dot(right, front)) < 0.01f &&
            std::fabs(Dot(up, front)) < 0.01f &&
            Dot(Cross(right, up), front) > 0.98f;
    }

    MeshLookupResult FindMeshNode(uintptr_t root, const MeshId& id,
        ReadMeshNode read, void* user, size_t limit)
    {
        if (!root || !read || limit == 0 || limit > kMaxBindings)
            return { MeshLookupStatus::InvalidGraph, 0 };
        std::set<uintptr_t> visited;
        std::vector<uintptr_t> pending = { root };
        uintptr_t match = 0;
        while (!pending.empty())
        {
            const uintptr_t node = pending.back();
            pending.pop_back();
            if (visited.find(node) != visited.end())
                return { MeshLookupStatus::InvalidGraph, 0 };
            if (visited.size() == limit)
                return { MeshLookupStatus::LimitExceeded, 0 };
            visited.insert(node);
            MeshNodeView view;
            if (!read(node, view, user))
                return { MeshLookupStatus::InvalidGraph, 0 };
            if (view.id == id)
            {
                if (match)
                    return { MeshLookupStatus::Ambiguous, 0 };
                match = node;
            }
            if (view.sibling)
                pending.push_back(view.sibling);
            if (view.child)
                pending.push_back(view.child);
        }
        return { match ? MeshLookupStatus::Found : MeshLookupStatus::NotFound, match };
    }

    bool Identity::operator==(const Identity& rhs) const noexcept
    {
        return address == rhs.address && lifetime == rhs.lifetime;
    }

    bool Identity::operator<(const Identity& rhs) const noexcept
    {
        return std::tie(address, lifetime) < std::tie(rhs.address, rhs.lifetime);
    }

    struct Runtime::Impl
    {
        using RecoilKey = std::pair<Identity, Identity>;
        struct Weapon
        {
            BindingToken token;
            Identity owner;
            Identity identity;
            FlashConfig config;
            std::optional<RecoilKey> recoil;
            Matrix muzzle = WeaponConvergence::Identity();
            float remaining = 0.0f;
            void* renderer = nullptr;
            uint64_t lastShot = 0;
            bool createAttempted = false;
            bool muzzleDirty = false;
            bool retired = false;
        };
        struct Recoil
        {
            Matrix current = WeaponConvergence::Identity();
            double restX = 0.0;
            double restY = 0.0;
            double restZ = 0.0;
            float displacement = 0.0f;
            size_t references = 0;
            bool dirty = false;
            bool presented = false;

            Matrix Visual() const noexcept
            {
                Matrix visual = current;
                visual.positionX = restX + current.frontX * displacement;
                visual.positionY = restY + current.frontY * displacement;
                visual.positionZ = restZ + current.frontZ * displacement;
                return visual;
            }
        };

        Settings settings;
        bool singleplayer = false;
        bool running = false;
        size_t sceneDepth = 0;
        uint64_t epoch = 1;
        uint64_t nextBinding = 1;
        uint64_t lastStep = 0;
        // Moving a unique_ptr does not move Weapon::renderer, which is the
        // address a native ParticleRender may keep for its back-reference.
        std::map<uint64_t, std::unique_ptr<Weapon>> weapons;
        std::map<RecoilKey, Recoil> recoils;

        bool Active() const noexcept
        {
            return singleplayer && running && sceneDepth == 0 &&
                (settings.muzzleFlash || settings.meshRecoil);
        }

        Weapon* Find(BindingToken token) noexcept
        {
            const auto it = weapons.find(token.serial);
            if (it == weapons.end() || it->second->retired ||
                token.epoch != epoch || it->second->token.epoch != token.epoch)
                return nullptr;
            return it->second.get();
        }

        void Retire(Weapon& weapon) noexcept
        {
            if (weapon.retired)
                return;
            weapon.retired = true;
            weapon.remaining = 0.0f;
            if (weapon.recoil)
            {
                const auto it = recoils.find(*weapon.recoil);
                if (it != recoils.end())
                {
                    Recoil& recoil = it->second;
                    if (recoil.references)
                        --recoil.references;
                    if (recoil.references == 0)
                    {
                        recoil.displacement = 0.0f;
                        recoil.dirty = recoil.presented;
                    }
                }
            }
        }

        void RetireAll() noexcept
        {
            for (auto& entry : weapons)
                Retire(*entry.second);
            if (epoch != std::numeric_limits<uint64_t>::max())
                ++epoch;
            else
                nextBinding = 0; // fail closed on identity exhaustion
            lastStep = 0;
        }
    };

    Runtime::Runtime() : impl_(std::make_unique<Impl>()) {}

    Runtime::~Runtime()
    {
        // Destruction must not call a backend with an unknown engine lifetime.
        // A failed detach retains its slot until native back-references end.
        // If a caller violates that contract, leak only the stable slot record
        // rather than leave the engine with a dangling back-reference.
        for (auto& entry : impl_->weapons)
        {
            if (entry.second->renderer)
                (void)entry.second.release();
        }
    }

    void Runtime::Configure(Settings settings) noexcept
    {
        const bool wasEnabled = impl_->settings.muzzleFlash || impl_->settings.meshRecoil;
        impl_->settings = settings;
        if (wasEnabled && !settings.muzzleFlash && !settings.meshRecoil)
            impl_->RetireAll();
        if (!settings.muzzleFlash)
        {
            for (auto& entry : impl_->weapons)
                entry.second->remaining = 0.0f;
        }
        if (!settings.meshRecoil)
        {
            for (auto& entry : impl_->recoils)
            {
                entry.second.displacement = 0.0f;
                entry.second.dirty = entry.second.presented;
            }
        }
    }

    void Runtime::SetSession(bool singleplayer, bool missionRunning) noexcept
    {
        if ((impl_->singleplayer && !singleplayer) || (impl_->running && !missionRunning))
            impl_->RetireAll();
        impl_->singleplayer = singleplayer;
        impl_->running = missionRunning;
    }

    bool Runtime::AcceptingBindings() const noexcept { return impl_->Active(); }

    std::optional<BindingToken> Runtime::Bind(const BindRequest& request)
    {
        if (!impl_->Active() || !request.owner.Valid() || !request.weapon.Valid() ||
            impl_->nextBinding == 0 || impl_->weapons.size() >= kMaxBindings)
            return std::nullopt;
        for (const auto& entry : impl_->weapons)
        {
            if (!entry.second->retired && entry.second->identity.address == request.weapon.address)
                return std::nullopt; // replacement must release the old token first
        }
        const bool validRecoil = request.recoil && request.recoil->node.Valid() &&
            ValidPose(request.recoil->unrecoiledPose);
        if (!(impl_->settings.muzzleFlash && request.flash.Valid()) &&
            !(impl_->settings.meshRecoil && validRecoil))
            return std::nullopt;

        auto weapon = std::make_unique<Impl::Weapon>();
        weapon->owner = request.owner;
        weapon->identity = request.weapon;
        weapon->config = request.flash.Valid() ? request.flash : FlashConfig{};
        const uint64_t serial = impl_->nextBinding;
        weapon->token = { impl_->epoch, serial };

        // Commit the weapon allocation first. On a recoil-map allocation
        // failure, remove it before propagating; no shared reference is added.
        auto inserted = impl_->weapons.emplace(serial, std::move(weapon));
        try
        {
            if (validRecoil)
            {
                const Impl::RecoilKey key = { request.owner, request.recoil->node };
                auto recoilIt = impl_->recoils.find(key);
                if (recoilIt != impl_->recoils.end() && recoilIt->second.references == 0 &&
                    recoilIt->second.presented)
                {
                    impl_->weapons.erase(inserted.first);
                    return std::nullopt; // restore old visual pose before rebinding
                }
                if (recoilIt == impl_->recoils.end())
                {
                    Impl::Recoil recoil;
                    recoil.current = request.recoil->unrecoiledPose;
                    recoil.restX = recoil.current.positionX;
                    recoil.restY = recoil.current.positionY;
                    recoil.restZ = recoil.current.positionZ;
                    recoilIt = impl_->recoils.emplace(key, recoil).first;
                }
                ++recoilIt->second.references;
                inserted.first->second->recoil = key;
            }
        }
        catch (...)
        {
            impl_->weapons.erase(inserted.first);
            throw;
        }
        ++impl_->nextBinding; // wraps to zero, which rejects further binds
        return inserted.first->second->token;
    }

    bool Runtime::Release(BindingToken token) noexcept
    {
        Impl::Weapon* weapon = impl_->Find(token);
        if (!weapon)
            return false;
        impl_->Retire(*weapon);
        return true;
    }

    ShotResult Runtime::Fire(BindingToken token, uint64_t shotSerial,
        const Matrix& committedPose) noexcept
    {
        if (!impl_->Active() || shotSerial == 0 || !ValidPose(committedPose))
            return {};
        Impl::Weapon* weapon = impl_->Find(token);
        if (!weapon || shotSerial <= weapon->lastShot)
            return {};
        weapon->lastShot = shotSerial;
        ShotResult result = { true, false, false };
        if (impl_->settings.muzzleFlash && weapon->config.Valid())
        {
            if (weapon->createAttempted && !weapon->renderer)
                weapon->remaining = 0.0f; // renderer self-expired; allow next shot
            if (weapon->remaining <= 0.0f && !weapon->renderer)
            {
                weapon->remaining = weapon->config.duration;
                weapon->muzzle = committedPose;
                weapon->muzzleDirty = true;
                weapon->createAttempted = false;
                result.flashStarted = true;
            }
        }
        if (impl_->settings.meshRecoil && weapon->recoil)
        {
            const auto it = impl_->recoils.find(*weapon->recoil);
            if (it != impl_->recoils.end())
            {
                it->second.displacement = -kRecoilKick;
                it->second.dirty = true;
                result.recoilReset = true;
            }
        }
        return result;
    }

    bool Runtime::SetMuzzlePose(BindingToken token, const Matrix& worldPose) noexcept
    {
        if (!impl_->Active() || !ValidPose(worldPose))
            return false;
        Impl::Weapon* weapon = impl_->Find(token);
        if (!weapon)
            return false;
        weapon->muzzle = worldPose;
        weapon->muzzleDirty = true;
        return true;
    }

    bool Runtime::SetRecoilPose(const Identity& owner, const Identity& node,
        const Matrix& unrecoiledPose) noexcept
    {
        if (!impl_->Active() || !ValidPose(unrecoiledPose))
            return false;
        const auto it = impl_->recoils.find({ owner, node });
        if (it == impl_->recoils.end() || it->second.references == 0)
            return false;
        // This milestone supports a static translation. Animated translation
        // needs its own qualified baseline writer, rather than hiding drift.
        if (unrecoiledPose.positionX != it->second.restX ||
            unrecoiledPose.positionY != it->second.restY ||
            unrecoiledPose.positionZ != it->second.restZ)
            return false;
        it->second.current = unrecoiledPose;
        it->second.dirty = it->second.displacement != 0.0f || it->second.presented;
        return true;
    }

    bool Runtime::BeginSimulationStep(uint64_t stepSerial, float dt) noexcept
    {
        if (!impl_->Active() || stepSerial == 0 || stepSerial <= impl_->lastStep ||
            !std::isfinite(dt) || dt < 0.0f)
            return false;
        impl_->lastStep = stepSerial;
        if (dt == 0.0f)
            return true;
        for (auto& entry : impl_->weapons)
        {
            auto& weapon = *entry.second;
            if (!weapon.retired && weapon.remaining > 0.0f)
                weapon.remaining = std::max(0.0f, weapon.remaining - dt);
        }
        // Iterate the shared-node table, not five slots or every weapon.
        for (auto& entry : impl_->recoils)
        {
            auto& recoil = entry.second;
            if (recoil.displacement < 0.0f)
            {
                recoil.displacement = std::min(0.0f,
                    recoil.displacement + kRecoilReturnSpeed * dt);
                recoil.dirty = true;
            }
        }
        return true;
    }

    void Runtime::SynchronizeVisuals(Backend& backend) noexcept
    {
        for (auto it = impl_->weapons.begin(); it != impl_->weapons.end();)
        {
            Impl::Weapon& weapon = *it->second;
            if (!impl_->Active() || weapon.retired || weapon.remaining <= 0.0f)
            {
                if (weapon.renderer)
                    (void)backend.DetachFlash(weapon.renderer);
                if (weapon.retired && !weapon.renderer)
                {
                    it = impl_->weapons.erase(it);
                    continue;
                }
            }
            else if (!weapon.createAttempted)
            {
                weapon.createAttempted = true;
                if (!backend.CreateFlash(weapon.config.effect, weapon.muzzle, weapon.renderer) ||
                    !weapon.renderer)
                    weapon.remaining = 0.0f;
                weapon.muzzleDirty = false;
            }
            else if (!weapon.renderer)
                weapon.remaining = 0.0f; // self-expiry; never recreate without a shot
            else if (weapon.muzzleDirty)
            {
                if (!backend.UpdateFlash(weapon.renderer, weapon.muzzle))
                    weapon.remaining = 0.0f;
                weapon.muzzleDirty = false;
            }
            ++it;
        }
        for (auto it = impl_->recoils.begin(); it != impl_->recoils.end();)
        {
            auto& recoil = it->second;
            if (recoil.dirty)
            {
                if (backend.ApplyRecoil(it->first.first, it->first.second, recoil.Visual()))
                {
                    recoil.dirty = false;
                    recoil.presented = recoil.displacement != 0.0f;
                }
            }
            if (recoil.references == 0 && !recoil.presented)
                it = impl_->recoils.erase(it);
            else
                ++it;
        }
    }

    void Runtime::BeginSceneTeardown() noexcept
    {
        if (impl_->sceneDepth++ == 0)
            impl_->RetireAll();
    }

    void Runtime::EndSceneTeardown() noexcept
    {
        if (impl_->sceneDepth == 0)
            return;
        if (--impl_->sceneDepth == 0)
        {
            // Ogre scene loss proves the presentation poses are gone. It does
            // NOT prove that every native ParticleRender has been destroyed.
            // Retain every non-null back-reference slot until detach/expiry;
            // the native object list may outlive the Ogre scene manager.
            impl_->recoils.clear();
            for (auto it = impl_->weapons.begin(); it != impl_->weapons.end();)
            {
                if (it->second->retired && !it->second->renderer)
                    it = impl_->weapons.erase(it);
                else
                    ++it;
            }
        }
    }

    void Runtime::InvalidateResources() noexcept
    {
        for (auto& entry : impl_->weapons)
            entry.second->renderer = nullptr;
        impl_->weapons.clear();
        impl_->recoils.clear();
        impl_->RetireAll();
    }

    Snapshot Runtime::Inspect() const noexcept
    {
        Snapshot result;
        result.sharedRecoilNodes = impl_->recoils.size();
        for (const auto& entry : impl_->weapons)
        {
            if (entry.second->retired)
                ++result.retiredBindings;
            else
                ++result.bindings;
            if (entry.second->renderer)
                ++result.nativeAttachments;
        }
        return result;
    }

    float Runtime::RecoilDisplacement(const Identity& owner, const Identity& node) const noexcept
    {
        const auto it = impl_->recoils.find({ owner, node });
        return it == impl_->recoils.end() ? 0.0f : it->second.displacement;
    }
}
