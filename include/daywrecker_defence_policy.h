#pragma once
// daywrecker_defence_policy.h
// Pure rules for [SinglePlayer] DaywreckerDefence: an enemy Daywrecker in
// flight, or an enemy Comet (radarmsl, class Torpedo), can be ordered
// attacked, AI units that see one shoot it, and units that do not shoot it
// dodge it. No Windows or engine calls, so
// tests/daywrecker_defence_policy_tests.cpp runs them directly. The engine
// side is src/patches/daywrecker_defence.cpp; evidence and the live
// checklist: Docs/DAYWRECKER_AI_DEFENCE_RESEARCH.md section 4.
//
// "Bomb" below means an enemy Daywrecker in flight or an enemy Comet.

#include <cmath>
#include <cstddef>
#include <cstdint>

namespace BZROpenShim
{
    namespace DaywreckerDefencePolicy
    {
        // AiCommand ids (reverse_engineering/bsim/out/object_model/enums.md).
        constexpr int kCmdNone = 0;
        constexpr int kCmdGo = 3;
        constexpr int kCmdAttack = 4;
        constexpr int kCmdDefend = 15;

        // Every gate: the ini option and a single-player session.
        inline bool Active(bool optionOn, bool singlePlayer)
        {
            return optionOn && singlePlayer;
        }

        // ---- Player order (GetCommand slot 13) ---------------------------
        // Stock Craft::GetCommand (GOG 0x004AE110) returns CMD_GO for any
        // target whose class category is 3 (PowerUp) before it tests for an
        // enemy, so a bomb never offers Attack. Same armed test as stock:
        // CMD_ATTACK needs [craft+0x1A0] (weapon) non-zero.
        inline bool ShouldOfferAttack(bool isBomb, bool enemy, bool hasWeapon, bool optionOn, bool singlePlayer)
        {
            return Active(optionOn, singlePlayer) && isBomb && enemy && hasWeapon;
        }

        // The command the wrapper returns for a stock result.
        inline int OfferedCommand(int stockCommand, bool isBomb, bool enemy, bool hasWeapon, bool optionOn,
                                  bool singlePlayer)
        {
            if (stockCommand == kCmdGo && ShouldOfferAttack(isBomb, enemy, hasWeapon, optionOn, singlePlayer))
                return kCmdAttack;
            return stockCommand;
        }

        struct Vec3
        {
            float x = 0.0f;
            float y = 0.0f;
            float z = 0.0f;
        };

        inline Vec3 Make(float x, float y, float z)
        {
            Vec3 v;
            v.x = x;
            v.y = y;
            v.z = z;
            return v;
        }
        inline Vec3 Sub(const Vec3& a, const Vec3& b) { return Make(a.x - b.x, a.y - b.y, a.z - b.z); }
        inline Vec3 Add(const Vec3& a, const Vec3& b) { return Make(a.x + b.x, a.y + b.y, a.z + b.z); }
        inline Vec3 Scale(const Vec3& a, float s) { return Make(a.x * s, a.y * s, a.z * s); }
        inline float Dot(const Vec3& a, const Vec3& b) { return a.x * b.x + a.y * b.y + a.z * b.z; }
        inline float LengthSq(const Vec3& a) { return Dot(a, a); }

        // ---- Detection (decision 9: like a Person) -----------------------
        // Stock GetClosestEnemyWithin (1.5 0x00406302, lines 72 and 95-99; GOG
        // FUN_00463240 lines 196-201) accepts a non-craft (Person) target only
        // when its XZ distance squared is <= 4900 (70 m) and it is in the
        // unit's front half-space (front . (target - unit) >= 0, 3D). The
        // Person-only extras (it shot me, it shot a friend in the last 10 s,
        // the person-state bit 0x80) do not apply to a bomb.
        constexpr float kDetectRangeSq = 4900.0f;

        inline bool Detects(const Vec3& unitPos, const Vec3& unitFront, const Vec3& bombPos)
        {
            const Vec3 d = Sub(bombPos, unitPos);
            if (d.x * d.x + d.z * d.z > kDetectRangeSq)
                return false;
            return Dot(unitFront, d) >= 0.0f;
        }

        // ---- Radius scan --------------------------------------------------
        constexpr float kScanRadius = 150.0f;
        constexpr float kScanInterval = 0.5f;
        constexpr int kMaxUnitsPerBomb = 4;
        constexpr float kUnitCooldown = 3.0f;

        // XZ distance squared, as GetClosestEnemyPersonWithin (1.5 0x004096BF).
        inline bool InRadius(float dx, float dz, float radius)
        {
            return dx * dx + dz * dz <= radius * radius;
        }

        // A clock that went backwards (new mission) counts as due.
        inline bool ScanDue(float now, float last, float interval)
        {
            return now < last || now - last >= interval;
        }

        inline bool CooldownReady(float now, float lastOrdered, bool everOrdered, float cooldown)
        {
            return !everOrdered || now < lastOrdered || now - lastOrdered >= cooldown;
        }

        // What the scan knows about one candidate unit.
        struct UnitView
        {
            bool isCraft = false;
            bool isPlayer = false;   // the local player's own craft
            bool hasWeapon = false;  // [craft+0x1A0] != 0
            bool enemy = false;      // GameObject::EnemyP(unit, bomb)
            bool isCargo = false;
            int curWhat = kCmdNone;  // curCmd.what
            uint32_t curWho = 0;     // curCmd.who (handle)
            int nextWhat = kCmdNone; // nextCmd.what (pending order)
            uint32_t nextWho = 0;
            uint32_t target = 0;     // GameObject target handle (+0x21C)
        };

        // The unit is already on this bomb: attacking it, ordered to, or
        // aiming at it.
        inline bool TargetsBomb(const UnitView& u, uint32_t bomb)
        {
            if (bomb == 0)
                return false;
            return (u.curWhat == kCmdAttack && u.curWho == bomb) || (u.nextWhat == kCmdAttack && u.nextWho == bomb) ||
                   u.target == bomb;
        }

        // Idle or defending, with no order pending. There is no WAIT
        // AiCommand; idle is CMD_NONE. Anything else (GO, FOLLOW, ATTACK on
        // something else, a pending order) is a player or AIP order that is
        // never overridden.
        inline bool IsInterruptible(const UnitView& u)
        {
            return (u.curWhat == kCmdNone || u.curWhat == kCmdDefend) && u.nextWhat == kCmdNone;
        }

        // Whether the scan orders this unit to attack the bomb. The unit has
        // already detected the bomb (Detects) and passed InRadius.
        inline bool ShouldTargetBomb(const UnitView& u, uint32_t bomb, int assignedToBomb, bool cooldownReady,
                                     bool optionOn, bool singlePlayer)
        {
            return Active(optionOn, singlePlayer) && bomb != 0 && u.isCraft && !u.isPlayer && u.hasWeapon &&
                   u.enemy && !u.isCargo && IsInterruptible(u) && !TargetsBomb(u, bomb) &&
                   assignedToBomb < kMaxUnitsPerBomb && cooldownReady;
        }

        // An AI unit, armed or not (stock evasion has no weapon test), that
        // has detected the bomb and is not attacking or aiming at it. The
        // player's craft is never touched.
        inline bool ShouldEvade(bool isBomb, bool enemy, bool unitIsPlayer, bool targetsThisBomb, bool detected,
                                bool optionOn, bool singlePlayer)
        {
            return Active(optionOn, singlePlayer) && isBomb && enemy && !unitIsPlayer && !targetsThisBomb && detected;
        }

        // ---- Evasion force (mirrors stock EvadeOrdnanceForce) ------------
        // 1.5 0x0046DD9D lines 113-197, GOG FUN_005fd5f0 lines 149-255:
        // range 200 m (3D distance squared <= 40000); forward cone in the
        // unit frame (dropped if z < |x| or z < 1.5|y|); closest approach
        // time t = -(rel . relVel) / |relVel|^2 (skipped if |relVel|^2 <
        // 0.0001); threat if t > 0 and miss < (r1) * 2.5 with r1 = unit
        // radius + ordnance radius; force away from the miss point with
        // weight / (t + 1) times Min(2.5 - miss / r1, 1).
        constexpr float kEvadeRangeSq = 40000.0f;
        constexpr float kMinRelSpeedSq = 0.0001f;
        constexpr float kMissFactor = 2.5f;
        constexpr float kConeYFactor = 1.5f;
        constexpr float kNormaliseLength = 20.0f;
        // The stock weight is GetOrdnanceDamage; the bomb's damage offset is
        // not verified, so a constant stands in. Any threat weight above 20
        // is cut to 20 by the normalise step anyway.
        constexpr float kBombWeight = 1000.0f;

        struct Frame
        {
            Vec3 right;
            Vec3 up;
            Vec3 front;
        };

        struct EvadeResult
        {
            Vec3 force;
            bool threat = false;
        };

        inline float Min(float a, float b) { return a < b ? a : b; }

        inline EvadeResult EvadeForce(const Vec3& selfPos, const Vec3& selfVel, const Frame& selfFrame,
                                      float selfRadius, const Vec3& bombPos, const Vec3& bombVel, float bombRadius,
                                      float weight)
        {
            EvadeResult out;
            const Vec3 d = Sub(bombPos, selfPos);
            if (LengthSq(d) > kEvadeRangeSq)
                return out;
            const float lx = Dot(selfFrame.right, d);
            const float ly = Dot(selfFrame.up, d);
            const float lz = Dot(selfFrame.front, d);
            if (lz < std::fabs(lx) || lz < std::fabs(ly) * kConeYFactor)
                return out;
            const Vec3 rv = Sub(bombVel, selfVel);
            const float rvSq = LengthSq(rv);
            if (rvSq < kMinRelSpeedSq)
                return out;
            const float t = -Dot(rv, d) / rvSq;
            const float r1 = selfRadius + bombRadius;
            if (!(t > 0.0f) || !(r1 > 0.0f))
                return out;
            const Vec3 miss = Add(d, Scale(rv, t));
            const float m = std::sqrt(LengthSq(miss));
            if (!(m < r1 * kMissFactor))
                return out;
            const float factor = Min(kMissFactor - m / r1, 1.0f);
            const float w = weight / (t + 1.0f);
            if (factor == 0.0f || !(w > 0.0f))
                return out;
            const Vec3 dir = Scale(miss, -1.0f / (m + 1.1920929e-07f));
            out.force = Scale(dir, w * factor);
            out.threat = true;
            return out;
        }

        // Stock force plus the bomb forces. The stock normalise-to-20 runs
        // only when a threat was recorded and |F|^2 > 400 (GOG FUN_005fd5f0
        // lines 104-118; 1.5 lines 209-219); a bomb threat counts as one.
        inline Vec3 Combine(const Vec3& stockForce, bool stockThreat, const Vec3& bombForce, bool bombThreat)
        {
            Vec3 f = Add(stockForce, bombForce);
            const float lenSq = LengthSq(f);
            if ((stockThreat || bombThreat) && lenSq > kNormaliseLength * kNormaliseLength)
                f = Scale(f, kNormaliseLength / std::sqrt(lenSq));
            return f;
        }

        // ---- Registry of live bombs ---------------------------------------
        // Handles only; the engine side re-resolves each one on use. An entry
        // not refreshed by its Simulate wrapper for kStaleAfter seconds is
        // dropped (covers a bomb shot down or removed without a grounded tick).
        constexpr float kStaleAfter = 0.25f;
        constexpr size_t kRegistryCapacity = 32;

        struct BombEntry
        {
            uint32_t handle = 0;
            float lastSeen = 0.0f;
            float lastScan = 0.0f;
            bool scanned = false;
            int assigned = 0; // units ordered onto this bomb
        };

        inline bool IsStale(float now, float lastSeen)
        {
            return now < lastSeen || now - lastSeen > kStaleAfter;
        }

        template <size_t N = kRegistryCapacity>
        class BombRegistry
        {
        public:
            // Adds or refreshes; null when full or handle is 0.
            BombEntry* Refresh(uint32_t handle, float now)
            {
                if (handle == 0)
                    return nullptr;
                BombEntry* free = nullptr;
                for (size_t i = 0; i < N; ++i)
                {
                    if (entries_[i].handle == handle)
                    {
                        entries_[i].lastSeen = now;
                        return &entries_[i];
                    }
                    if (!free && entries_[i].handle == 0)
                        free = &entries_[i];
                }
                if (!free)
                    return nullptr;
                *free = BombEntry{};
                free->handle = handle;
                free->lastSeen = now;
                return free;
            }

            bool Remove(uint32_t handle)
            {
                for (size_t i = 0; i < N; ++i)
                {
                    if (handle != 0 && entries_[i].handle == handle)
                    {
                        entries_[i] = BombEntry{};
                        return true;
                    }
                }
                return false;
            }

            // Drops stale entries; returns how many.
            size_t Prune(float now)
            {
                size_t dropped = 0;
                for (size_t i = 0; i < N; ++i)
                {
                    if (entries_[i].handle != 0 && IsStale(now, entries_[i].lastSeen))
                    {
                        entries_[i] = BombEntry{};
                        ++dropped;
                    }
                }
                return dropped;
            }

            void Clear()
            {
                for (size_t i = 0; i < N; ++i)
                    entries_[i] = BombEntry{};
            }

            size_t Count() const
            {
                size_t n = 0;
                for (size_t i = 0; i < N; ++i)
                    n += entries_[i].handle != 0 ? 1u : 0u;
                return n;
            }

            static constexpr size_t Capacity() { return N; }
            const BombEntry& At(size_t i) const { return entries_[i]; }
            BombEntry& At(size_t i) { return entries_[i]; }

        private:
            BombEntry entries_[N];
        };

        // ---- Per-unit order cooldown --------------------------------------
        template <size_t N = 64>
        class CooldownTable
        {
        public:
            bool Ready(uint32_t unit, float now, float cooldown) const
            {
                for (size_t i = 0; i < N; ++i)
                    if (units_[i] == unit && unit != 0)
                        return CooldownReady(now, times_[i], true, cooldown);
                return true;
            }

            // Records an order; replaces the oldest entry when full.
            void Mark(uint32_t unit, float now)
            {
                if (unit == 0)
                    return;
                size_t slot = N;
                size_t oldest = 0;
                for (size_t i = 0; i < N; ++i)
                {
                    if (units_[i] == unit)
                    {
                        slot = i;
                        break;
                    }
                    if (slot == N && units_[i] == 0)
                        slot = i;
                    if (times_[i] < times_[oldest])
                        oldest = i;
                }
                if (slot == N)
                    slot = oldest;
                units_[slot] = unit;
                times_[slot] = now;
            }

            void Clear()
            {
                for (size_t i = 0; i < N; ++i)
                {
                    units_[i] = 0;
                    times_[i] = 0.0f;
                }
            }

        private:
            uint32_t units_[N] = {};
            float times_[N] = {};
        };
    }
}
