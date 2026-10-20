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
    static Matrix MeshFlashPose(Matrix pose, const WeaponConvergence::Vec3& offset) noexcept
    {
        pose.positionX += pose.rightX * offset.x + pose.upX * offset.y + pose.frontX * offset.z;
        pose.positionY += pose.rightY * offset.x + pose.upY * offset.y + pose.frontY * offset.z;
        pose.positionZ += pose.rightZ * offset.x + pose.upZ * offset.y + pose.frontZ * offset.z;
        return pose;
    }
    bool AnimationBinding::Valid() const noexcept
    {
        return !clip.empty() && clip.size() <= 63 &&
            std::all_of(clip.begin(), clip.end(), [](unsigned char c) { return c >= 0x21 && c <= 0x7e; }) &&
            std::isfinite(length) && length > 0 && length <= 60 &&
            std::isfinite(playbackRate) && playbackRate > 0 && playbackRate <= 50;
    }

    bool MuzzleRenderConfig::Valid() const noexcept
    {
        return !effect.empty() && effect.size() <= 63 &&
            std::all_of(effect.begin(), effect.end(), [](unsigned char c) { return c >= 0x21 && c <= 0x7e && c != '"'; }) &&
            std::isfinite(duration) && duration >= 0.005f && duration <= 5 &&
            std::isfinite(offset.x) && std::isfinite(offset.y) && std::isfinite(offset.z) &&
            std::fabs(offset.x) <= 20 && std::fabs(offset.y) <= 20 && std::fabs(offset.z) <= 20;
    }

    bool FlashConfig::Valid() const noexcept
    {
        if (IsMesh())
        {
            const auto resource = [](const std::string& value, bool optional) {
                return (optional || !value.empty()) && value.size() <= 127 &&
                    std::all_of(value.begin(), value.end(), [](unsigned char c) { return c >= 0x20 && c <= 0x7e; });
            };
            return resource(mesh, false) && resource(material, true) &&
                std::isfinite(duration) && duration >= 0.005f && duration <= 5 &&
                std::isfinite(startScale) && startScale >= 0 && startScale <= 100 &&
                std::isfinite(finishScale) && finishScale >= 0 && finishScale <= 100 &&
                (startScale > 0 || finishScale > 0) && std::isfinite(offset.x) &&
                std::isfinite(offset.y) && std::isfinite(offset.z) &&
                std::fabs(offset.x) <= 20 && std::fabs(offset.y) <= 20 && std::fabs(offset.z) <= 20 &&
                std::isfinite(rollDegrees) && std::fabs(rollDegrees) <= 360;
        }
        return muzzleRender.Valid() || (!effect.empty() && effect.size() < 128 &&
            effect.find('\0') == std::string::npos &&
            std::isfinite(duration) && duration > 0.0f);
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
        using AnimationKey = std::pair<Identity, std::string>;
        struct Weapon
        {
            BindingToken token;
            Identity owner;
            Identity identity;
            FlashConfig config;
            std::optional<RecoilKey> recoil;
            std::optional<AnimationKey> animation;
            Matrix muzzle = WeaponConvergence::Identity();
            Matrix renderMuzzle = WeaponConvergence::Identity();
            float remaining = 0.0f;
            float renderRemaining = 0.0f;
            void* renderer = nullptr;
            MeshFlashToken meshFlash;
            uint64_t lastShot = 0;
            bool createAttempted = false;
            bool renderCreateAttempted = false;
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
            float distance = kRecoilKick;
            float returnSpeed = kRecoilReturnSpeed;
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

        struct Animation
        {
            AnimationBinding config;
            float time = 0;
            size_t references = 0;
            bool active = false;
            bool dirty = false;
            bool presented = false;
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
        std::map<AnimationKey, Animation> animations;

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
            weapon.renderRemaining = 0.0f;
            if (weapon.animation)
            {
                auto it = animations.find(*weapon.animation);
                if (it != animations.end() && it->second.references && --it->second.references == 0)
                {
                    it->second.active = false;
                    it->second.dirty = it->second.presented;
                }
            }
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
            {
                entry.second->remaining = 0.0f;
                entry.second->renderRemaining = 0.0f;
            }
        }
        if (!settings.meshRecoil)
        {
            for (auto& entry : impl_->animations)
            {
                entry.second.active = false;
                entry.second.dirty = entry.second.presented;
            }
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
        const bool validAnimation = request.animation && request.animation->Valid();
        const bool validRecoil = !request.animation && request.recoil && request.recoil->node.Valid() &&
            ValidPose(request.recoil->unrecoiledPose) && std::isfinite(request.recoil->distance) &&
            request.recoil->distance > 0 && request.recoil->distance <= 10 &&
            std::isfinite(request.recoil->returnSpeed) && request.recoil->returnSpeed > 0 &&
            request.recoil->returnSpeed <= 100;
        if (validAnimation && impl_->animations.size() >= kMaxBindings &&
            !impl_->animations.count({request.owner, request.animation->clip})) return std::nullopt;
        // A failed visual restoration can retain a controller after its last
        // weapon record is gone. Bound that table independently of weapons.
        if (validRecoil && impl_->recoils.size() >= kMaxBindings &&
            impl_->recoils.find({ request.owner, request.recoil->node }) == impl_->recoils.end())
            return std::nullopt;
        if (!(impl_->settings.muzzleFlash && request.flash.Valid()) &&
            !(impl_->settings.meshRecoil && (validRecoil || validAnimation)))
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
            if (validAnimation)
            {
                const Impl::AnimationKey key{request.owner, request.animation->clip};
                auto it = impl_->animations.find(key);
                if (it != impl_->animations.end() && (it->second.config.length != request.animation->length ||
                    it->second.config.playbackRate != request.animation->playbackRate ||
                    it->second.config.cockpit != request.animation->cockpit ||
                    (it->second.references == 0 && it->second.presented)))
                { impl_->weapons.erase(inserted.first); return std::nullopt; }
                // Copy the key before incrementing references (allocation can throw).
                inserted.first->second->animation = key;
                if (it == impl_->animations.end())
                {
                    Impl::Animation anim; anim.config = *request.animation;
                    it = impl_->animations.emplace(key, std::move(anim)).first;
                }
                ++it->second.references;
            }
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
                    recoil.distance = request.recoil->distance;
                    recoil.returnSpeed = request.recoil->returnSpeed;
                    recoilIt = impl_->recoils.emplace(key, recoil).first;
                }
                else if (recoilIt->second.distance != request.recoil->distance ||
                    recoilIt->second.returnSpeed != request.recoil->returnSpeed)
                { impl_->weapons.erase(inserted.first); return std::nullopt; }
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
            if (weapon->config.IsMesh() && weapon->remaining <= 0.0f && !weapon->meshFlash)
            {
                weapon->remaining = weapon->config.duration;
                weapon->muzzle = committedPose;
                if (weapon->config.IsMesh())
                    weapon->muzzle = MeshFlashPose(committedPose, weapon->config.offset);
                weapon->muzzleDirty = true;
                weapon->createAttempted = false;
                result.flashStarted = true;
            }
            const auto& render = weapon->config.muzzleRender;
            const bool legacy = !weapon->config.IsMesh() && !weapon->config.effect.empty();
            if (weapon->renderCreateAttempted && !weapon->renderer)
                weapon->renderRemaining = 0; // native self-expiry; allow the next accepted shot
            if ((render.Valid() || legacy) && weapon->renderRemaining <= 0 && !weapon->renderer)
            {
                weapon->renderRemaining = render.Valid() ? render.duration : weapon->config.duration;
                weapon->renderMuzzle = render.Valid() ? MeshFlashPose(committedPose, render.offset) : committedPose;
                weapon->muzzleDirty = true;
                weapon->renderCreateAttempted = false;
                result.flashStarted = true;
            }
        }
        if (impl_->settings.meshRecoil && weapon->recoil)
        {
            const auto it = impl_->recoils.find(*weapon->recoil);
            if (it != impl_->recoils.end())
            {
                it->second.displacement = -it->second.distance;
                it->second.dirty = true;
                result.recoilReset = true;
            }
        }
        if (impl_->settings.meshRecoil && weapon->animation)
        {
            auto it = impl_->animations.find(*weapon->animation);
            if (it != impl_->animations.end())
            {
                it->second.time = 0;
                it->second.active = true;
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
        weapon->muzzle = weapon->config.IsMesh() ? MeshFlashPose(worldPose, weapon->config.offset) : worldPose;
        weapon->renderMuzzle = weapon->config.muzzleRender.Valid()
            ? MeshFlashPose(worldPose, weapon->config.muzzleRender.offset) : worldPose;
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

    bool Runtime::TryGetVisualRecoilPose(const Identity& owner, const Identity& node,
        Matrix& visualPose) const noexcept
    {
        if (!impl_->Active())
            return false;
        const auto it = impl_->recoils.find({ owner, node });
        if (it == impl_->recoils.end() || it->second.references == 0)
            return false;
        visualPose = it->second.Visual();
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
            if (!weapon.retired && weapon.renderRemaining > 0)
                weapon.renderRemaining = std::max(0.0f, weapon.renderRemaining - dt);
        }
        // Iterate the shared-node table, not five slots or every weapon.
        for (auto& entry : impl_->animations)
        {
            auto& anim = entry.second;
            if (!anim.active) continue;
            anim.time = std::min(anim.config.length, anim.time + dt * anim.config.playbackRate);
            anim.active = anim.time < anim.config.length;
            anim.dirty = true;
        }
        for (auto& entry : impl_->recoils)
        {
            auto& recoil = entry.second;
            if (recoil.displacement < 0.0f)
            {
                recoil.displacement = std::min(0.0f,
                    recoil.displacement + recoil.returnSpeed * dt);
                recoil.dirty = true;
            }
        }
        return true;
    }

    void Runtime::SynchronizeVisuals(Backend& backend) noexcept
    {
        for (auto it = impl_->animations.begin(); it != impl_->animations.end();)
        {
            auto& anim = it->second;
            // A failed backend call can still have partially changed a target.
            // Retain restoration responsibility even before its first success.
            if (anim.dirty && anim.active) anim.presented = true;
            if (anim.dirty && backend.ApplyAnimation(it->first.first, anim.config, anim.time, anim.active))
            {
                anim.dirty = false;
                anim.presented = anim.active;
            }
            if (anim.references == 0 && !anim.presented && !anim.dirty) it = impl_->animations.erase(it);
            else ++it;
        }
        for (auto it = impl_->weapons.begin(); it != impl_->weapons.end();)
        {
            Impl::Weapon& weapon = *it->second;
            if (weapon.config.IsMesh())
            {
                if (!impl_->Active() || weapon.retired || weapon.remaining <= 0)
                {
                    if (weapon.meshFlash) (void)backend.CancelMeshFlash(weapon.meshFlash);
                }
                else if (!weapon.createAttempted)
                {
                    weapon.createAttempted = true;
                    if (!backend.CreateMeshFlash(weapon.config, weapon.owner, weapon.muzzle,
                        weapon.remaining, weapon.meshFlash) || !weapon.meshFlash) weapon.remaining = 0;
                }
            }
            if (!impl_->Active() || weapon.retired || weapon.renderRemaining <= 0.0f)
            {
                if (weapon.renderer)
                    (void)backend.DetachFlash(weapon.renderer);
                if (weapon.retired && !weapon.renderer && !weapon.meshFlash)
                {
                    it = impl_->weapons.erase(it);
                    continue;
                }
            }
            else if (!weapon.renderCreateAttempted)
            {
                weapon.renderCreateAttempted = true;
                const auto& effect = weapon.config.muzzleRender.Valid()
                    ? weapon.config.muzzleRender.effect : weapon.config.effect;
                if (!backend.CreateFlash(effect, weapon.renderMuzzle, weapon.renderer) ||
                    !weapon.renderer)
                    weapon.renderRemaining = 0.0f;
                weapon.muzzleDirty = false;
            }
            else if (!weapon.renderer)
                weapon.renderRemaining = 0.0f; // self-expiry; never recreate without a shot
            else if (weapon.muzzleDirty)
            {
                if (!backend.UpdateFlash(weapon.renderer, weapon.renderMuzzle))
                    weapon.renderRemaining = 0.0f;
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
            impl_->animations.clear();
            for (auto it = impl_->weapons.begin(); it != impl_->weapons.end();)
            {
                if (it->second->retired && !it->second->renderer && !it->second->meshFlash)
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
        impl_->animations.clear();
        impl_->RetireAll();
    }

    Snapshot Runtime::Inspect() const noexcept
    {
        Snapshot result;
        result.sharedRecoilNodes = impl_->recoils.size();
        result.sharedAnimationClips = impl_->animations.size();
        for (const auto& entry : impl_->weapons)
        {
            if (entry.second->retired)
                ++result.retiredBindings;
            else
                ++result.bindings;
            if (entry.second->renderer)
                ++result.nativeAttachments;
            if (entry.second->meshFlash) ++result.meshFlashAttachments;
        }
        return result;
    }

    float Runtime::RecoilDisplacement(const Identity& owner, const Identity& node) const noexcept
    {
        const auto it = impl_->recoils.find({ owner, node });
        return it == impl_->recoils.end() ? 0.0f : it->second.displacement;
    }
}
