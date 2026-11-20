#pragma once
// mru_class_policy.h
// Pure rules for ODF `classLabel = "mru"` (Docs/MRU_CLASS.md): the
// [MruClass] key set with its defaults and sanitizing, the menu slot/mode
// mapping, and the gameplay rules (pod drop gate, service tick, deploy
// hold). No Windows or engine calls, so
// tests/mru_class_policy_tests.cpp runs them directly. The engine side is
// src/patches/mru_class.cpp.
//
// Portable C++14 (the Linux CTest lane builds with -Wall -Wextra -Werror).

#include <cmath>
#include <cstddef>
#include <cstdint>
#include <cstdlib>

namespace BZROpenShim
{
    namespace MruClassPolicy
    {
        // ---- [MruClass] keys (Docs/NIGHTINGALE_RESEARCH.md section 5) ------

        constexpr size_t kPodClassBytes = 16;  // an ODF name is 8 characters

        // Read per class at BuildClass; used by the gameplay rules below.
        struct Config
        {
            float serviceRadius = 0.0f;     // metres; 0 = no service
            float serviceInterval = 1.0f;   // seconds per service tick
            float repairPerTick = 100.0f;   // health per unit per tick
            float reloadPerTick = 50.0f;    // ammo per unit per tick
            float ammoPerRepair = 1.0f;     // gauge cost per health point; 0 = free
            float ammoPerReload = 1.0f;     // gauge cost per ammo point; 0 = free
            bool serviceSelf = false;
            bool serviceDeployed = true;    // service only while deployed
            float podCooldown = 30.0f;      // seconds between pod drops
            char repairPodClass[kPodClassBytes] = {};  // empty: no repair pod
            char ammoPodClass[kPodClassBytes] = {};    // empty: no ammo pod
            float ammoPerRepairPod = 0.0f;  // gauge cost per pod; 0 = free
            float ammoPerAmmoPod = 0.0f;
        };

        // Order of the raw values ReadMruKeys copies out of the ODF.
        enum Key : int
        {
            kKeyServiceRadius,
            kKeyServiceInterval,
            kKeyRepairPerTick,
            kKeyReloadPerTick,
            kKeyAmmoPerRepair,
            kKeyAmmoPerReload,
            kKeyServiceSelf,
            kKeyServiceDeployed,
            kKeyPodCooldown,
            kKeyRepairPodClass,
            kKeyAmmoPodClass,
            kKeyAmmoPerRepairPod,
            kKeyAmmoPerAmmoPod,
            kKeyCount
        };

        constexpr const char* kSectionName = "MruClass";

        inline const char* KeyName(int key)
        {
            static const char* const kNames[kKeyCount] = {
                "serviceRadius", "serviceInterval", "repairPerTick", "reloadPerTick",
                "ammoPerRepair", "ammoPerReload", "serviceSelf", "serviceDeployed",
                "podCooldown", "repairPodClass", "ammoPodClass", "ammoPerRepairPod",
                "ammoPerAmmoPod",
            };
            return key >= 0 && key < kKeyCount ? kNames[key] : "";
        }

        // Lower bound of serviceInterval: one tick per frame at most.
        constexpr float kMinServiceInterval = 0.05f;

        // One raw value per key; null when the key is absent.
        struct RawKeys
        {
            const char* values[kKeyCount] = {};
        };

        // The section is present when the ODF sets at least one known key.
        // ParameterDB has no section lookup, so an [MruClass] header with no
        // known key reads as absent.
        inline bool SectionPresent(const RawKeys& raw)
        {
            for (int i = 0; i < kKeyCount; ++i)
            {
                if (raw.values[i] && raw.values[i][0])
                    return true;
            }
            return false;
        }

        // A finite number, else `value` is left alone.
        inline void ParseFloat(const char* raw, float& value)
        {
            if (!raw || !raw[0])
                return;
            char* end = nullptr;
            const float parsed = std::strtof(raw, &end);
            if (end != raw && std::isfinite(parsed))
                value = parsed;
        }

        // ODF booleans are integers: 0 off, anything else on.
        inline void ParseBool(const char* raw, bool& value)
        {
            if (!raw || !raw[0])
                return;
            char* end = nullptr;
            const long parsed = std::strtol(raw, &end, 10);
            if (end != raw)
                value = parsed != 0;
        }

        // `repairPodClass = "repamine"`: quotes optional, the name ends at
        // whitespace or a quote. A name that does not fit leaves `out` empty
        // and returns false.
        template <size_t N>
        bool ParseName(const char* raw, char (&out)[N])
        {
            out[0] = 0;
            if (!raw)
                return true;
            while (*raw == ' ' || *raw == '\t' || *raw == '"')
                ++raw;
            size_t n = 0;
            while (raw[n] && raw[n] != '"' && raw[n] != ' ' && raw[n] != '\t' && raw[n] != '\r' &&
                   raw[n] != '\n')
            {
                if (n + 1 >= N)
                {
                    out[0] = 0;
                    return false;
                }
                out[n] = raw[n];
                ++n;
            }
            out[n] = 0;
            return true;
        }

        inline float NonNegative(float value, float fallback)
        {
            return std::isfinite(value) && value >= 0.0f ? value : fallback;
        }

        // Negative amounts fall back to the default; the interval is floored.
        inline Config Sanitize(Config c)
        {
            const Config d;
            c.serviceRadius = NonNegative(c.serviceRadius, d.serviceRadius);
            c.serviceInterval = NonNegative(c.serviceInterval, d.serviceInterval);
            if (c.serviceInterval < kMinServiceInterval)
                c.serviceInterval = kMinServiceInterval;
            c.repairPerTick = NonNegative(c.repairPerTick, d.repairPerTick);
            c.reloadPerTick = NonNegative(c.reloadPerTick, d.reloadPerTick);
            c.ammoPerRepair = NonNegative(c.ammoPerRepair, d.ammoPerRepair);
            c.ammoPerReload = NonNegative(c.ammoPerReload, d.ammoPerReload);
            c.podCooldown = NonNegative(c.podCooldown, d.podCooldown);
            c.ammoPerRepairPod = NonNegative(c.ammoPerRepairPod, d.ammoPerRepairPod);
            c.ammoPerAmmoPod = NonNegative(c.ammoPerAmmoPod, d.ammoPerAmmoPod);
            return c;
        }

        struct ParseResult
        {
            Config config;
            bool sectionPresent = false;
            bool repairPodNameTooLong = false;
            bool ammoPodNameTooLong = false;
        };

        inline ParseResult ParseConfig(const RawKeys& raw)
        {
            ParseResult r;
            r.sectionPresent = SectionPresent(raw);
            Config& c = r.config;
            ParseFloat(raw.values[kKeyServiceRadius], c.serviceRadius);
            ParseFloat(raw.values[kKeyServiceInterval], c.serviceInterval);
            ParseFloat(raw.values[kKeyRepairPerTick], c.repairPerTick);
            ParseFloat(raw.values[kKeyReloadPerTick], c.reloadPerTick);
            ParseFloat(raw.values[kKeyAmmoPerRepair], c.ammoPerRepair);
            ParseFloat(raw.values[kKeyAmmoPerReload], c.ammoPerReload);
            ParseBool(raw.values[kKeyServiceSelf], c.serviceSelf);
            ParseBool(raw.values[kKeyServiceDeployed], c.serviceDeployed);
            ParseFloat(raw.values[kKeyPodCooldown], c.podCooldown);
            r.repairPodNameTooLong = !ParseName(raw.values[kKeyRepairPodClass], c.repairPodClass);
            r.ammoPodNameTooLong = !ParseName(raw.values[kKeyAmmoPodClass], c.ammoPodClass);
            ParseFloat(raw.values[kKeyAmmoPerRepairPod], c.ammoPerRepairPod);
            ParseFloat(raw.values[kKeyAmmoPerAmmoPod], c.ammoPerAmmoPod);
            c = Sanitize(c);
            return r;
        }

        // ---- the menu -----------------------------------------------------

        // HoverCraft::UpdateModeList (0x004EBD60) fills slots 0-6 and 10;
        // slot 7 is Cloak/Decloak (0x18/0x19) only on a cloak-capable craft
        // (FUN_004aefa0), else mode 0 like slots 8 and 9. The MRU entries
        // take slots 7-9 after the stock fill. Their ids are stock ids the
        // hover menu never shows and that open no submenu (ControlPanel::
        // Render opens one only for 10, 0xE and 0x11, FUN_004a08e0.c
        // lines 1359-1371), relabelled by the shim. Mode 4 sits in slot 9 so
        // it never shares a slot with the Howitzer's slot-7 Drop Off.
        constexpr int kModeSlots = 11;
        constexpr int kModeDropRepair = 0xB;  // stock "Go To Geyser"
        constexpr int kModeDropAmmo = 0xF;    // stock "Lay Mines"
        constexpr int kModeDeploy = 0x4;      // stock "Drop Off"
        constexpr int kSlotDropRepair = 7;
        constexpr int kSlotDropAmmo = 8;
        constexpr int kSlotDeploy = 9;

        enum class Action : int
        {
            None,
            DropRepair,
            DropAmmo,
            Deploy,
        };

        struct MenuEntry
        {
            int slot;
            int mode;
            Action action;
        };

        constexpr int kMenuEntryCount = 3;
        constexpr MenuEntry kMenuEntries[kMenuEntryCount] = {
            { kSlotDropRepair, kModeDropRepair, Action::DropRepair },
            { kSlotDropAmmo, kModeDropAmmo, Action::DropAmmo },
            { kSlotDeploy, kModeDeploy, Action::Deploy },
        };

        inline Action ActionForMode(int mode)
        {
            for (int i = 0; i < kMenuEntryCount; ++i)
            {
                if (kMenuEntries[i].mode == mode)
                    return kMenuEntries[i].action;
            }
            return Action::None;
        }

        inline const char* ActionName(Action action)
        {
            switch (action)
            {
            case Action::DropRepair:
                return "Drop Repair";
            case Action::DropAmmo:
                return "Drop Ammo";
            case Action::Deploy:
                return "Deploy";
            default:
                return "stock";
            }
        }

        // True when an MRU entry `mode` is in its own slot of the unit's
        // ModeList (11 ids, enabled mask bit = slot) and enabled there.
        inline bool UnitOffersAction(const int32_t (&modes)[kModeSlots], uint32_t enabled, int mode)
        {
            for (int i = 0; i < kMenuEntryCount; ++i)
            {
                const MenuEntry& e = kMenuEntries[i];
                if (e.mode == mode)
                    return modes[e.slot] == mode && ((enabled >> e.slot) & 1u) != 0;
            }
            return false;
        }

        // ---- gameplay (plan steps 3-6, Docs/MRU_CLASS.md) ------------------

        // A pod spawns this far behind the MRU (metres, along -front), so it
        // does not spawn inside the hull.
        constexpr float kPodDropBackOffset = 6.0f;
        // Bound on the per-tick service scan.
        constexpr int kMaxServiceTargets = 32;
        // Craft::GetCommand treats class_id 1 (helicopter) and 6 (vehicle)
        // as units (FUN_004ae110.c lines 30-45).
        constexpr int kClassIdHelicopter = 1;
        constexpr int kClassIdVehicle = 6;
        // Command ids that leave a deployed MRU deployed: CMD_NONE,
        // CMD_SELECT, CMD_STOP (rts_commands_policy.h IsIdleWhat).
        constexpr int kWhatNone = 0;
        constexpr int kWhatSelect = 1;
        constexpr int kWhatStop = 2;

        // Non-combat (user, 2026-11-20): an MRU is pure utility, like the
        // Tug. It refuses CMD_ATTACK and CMD_HUNT (AiCommand 4 and 20,
        // bz15_pdb enum_values.tsv) from any source, and its menu loses the
        // Attack entry HoverCraft::UpdateModeList puts in slot 3 (mode 0xE,
        // FUN_004ebd60.c line 19), cleared as stock TurretTank does
        // (FUN_005f5a50.c line 19: SetMode(3, 0, 0)).
        constexpr int kWhatAttack = 4;
        constexpr int kWhatHunt = 20;
        constexpr int kSlotAttack = 3;
        constexpr int kModeAttack = 0xE;

        inline bool RefusesOrder(int what)
        {
            return what == kWhatAttack || what == kWhatHunt;
        }

        // Slot 3 is cleared only while it holds the stock Attack entry.
        inline bool ClearsAttackSlot(const int32_t (&modes)[kModeSlots])
        {
            return modes[kSlotAttack] == kModeAttack;
        }

        inline bool IsPodAction(Action action)
        {
            return action == Action::DropRepair || action == Action::DropAmmo;
        }

        inline const char* PodClass(const Config& c, Action action)
        {
            return action == Action::DropRepair ? c.repairPodClass
                   : action == Action::DropAmmo ? c.ammoPodClass
                                                : "";
        }

        // Gauge cost of one pod, rounded up to whole ammo (0 = free).
        inline long PodCost(const Config& c, Action action)
        {
            const float cost = action == Action::DropRepair ? c.ammoPerRepairPod
                               : action == Action::DropAmmo ? c.ammoPerAmmoPod
                                                            : 0.0f;
            return cost > 0.0f ? static_cast<long>(std::ceil(cost)) : 0;
        }

        enum class DropBlock : int
        {
            None,         // the drop may go
            NotPod,       // not Drop Repair / Drop Ammo
            NoPodClass,   // the ODF names no pod for it
            PodNotFound,  // the engine could not find the pod class
            Cooldown,
            Gauge,        // the MRU's ammo is below the pod cost
        };

        // A drop needs a configured pod, a finished cooldown and enough
        // gauge. `nameFailed` is set once the engine could not find the pod
        // class.
        inline DropBlock WhyNoDrop(const Config& c, Action action, float cooldownLeft, long gauge,
                                   bool nameFailed)
        {
            if (!IsPodAction(action))
                return DropBlock::NotPod;
            if (PodClass(c, action)[0] == 0)
                return DropBlock::NoPodClass;
            if (nameFailed)
                return DropBlock::PodNotFound;
            if (cooldownLeft > 0.0f)
                return DropBlock::Cooldown;
            if (gauge < PodCost(c, action))
                return DropBlock::Gauge;
            return DropBlock::None;
        }

        inline bool CanDrop(const Config& c, Action action, float cooldownLeft, long gauge,
                            bool nameFailed)
        {
            return WhyNoDrop(c, action, cooldownLeft, gauge, nameFailed) == DropBlock::None;
        }

        inline const char* DropBlockName(DropBlock block)
        {
            switch (block)
            {
            case DropBlock::None:
                return "ok";
            case DropBlock::NotPod:
                return "not a pod entry";
            case DropBlock::NoPodClass:
                return "no pod class in [MruClass]";
            case DropBlock::PodNotFound:
                return "pod class not found";
            case DropBlock::Cooldown:
                return "cooldown";
            default:
                return "gauge too low";
            }
        }

        // True when an MRU entry `mode` sits in its own slot, enabled or
        // not. A disabled entry's pick is still the MRU's (it must never
        // reach the stock dispatch as Go To Geyser / Lay Mines / Drop Off).
        inline bool EntryInItsSlot(const int32_t (&modes)[kModeSlots], int mode)
        {
            for (int i = 0; i < kMenuEntryCount; ++i)
            {
                const MenuEntry& e = kMenuEntries[i];
                if (e.mode == mode)
                    return modes[e.slot] == mode;
            }
            return false;
        }

        inline float TickCooldown(float left, float dt)
        {
            if (!(dt > 0.0f) || !std::isfinite(dt))
                return left;
            const float next = left - dt;
            return next > 0.0f ? next : 0.0f;
        }

        // The service runs when the radius is set and, with serviceDeployed,
        // only while deployed.
        inline bool ServiceActive(const Config& c, bool deployed)
        {
            return c.serviceRadius > 0.0f && (deployed || !c.serviceDeployed);
        }

        // Adds dt to the interval accumulator; true (and one interval taken
        // off) when a tick is due. At most one tick per call; the remainder
        // is capped at one interval so a long frame does not queue ticks.
        inline bool ConsumeTick(float& accumulator, float dt, float interval)
        {
            if (!(interval >= kMinServiceInterval) || !std::isfinite(interval))
                interval = kMinServiceInterval;
            if (dt > 0.0f && std::isfinite(dt))
                accumulator += dt;
            if (accumulator < interval)
                return false;
            accumulator -= interval;
            if (accumulator > interval)
                accumulator = interval;
            return true;
        }

        // Health to grant one target this tick: the per-tick amount, capped
        // by what the remaining gauge pays for (cost 0 = free). The engine
        // clamps the grant to the target's max; the drain is charged on what
        // was actually served.
        inline float RepairGrant(float perTick, float costPerPoint, float gaugeLeft)
        {
            if (!(perTick > 0.0f))
                return 0.0f;
            if (!(costPerPoint > 0.0f))
                return perTick;
            if (!(gaugeLeft > 0.0f))
                return 0.0f;
            const float affordable = gaugeLeft / costPerPoint;
            return affordable < perTick ? affordable : perTick;
        }

        // Whole ammo to grant one target this tick (AddAmmo takes a long).
        inline long ReloadGrant(float perTick, float costPerPoint, float gaugeLeft)
        {
            const float grant = RepairGrant(perTick, costPerPoint, gaugeLeft);
            return grant >= 1.0f ? static_cast<long>(std::floor(grant)) : 0;
        }

        // Adds `served * cost` to the fractional carry and returns the whole
        // ammo to drain now, capped at the gauge. An unpaid excess is
        // dropped so the carry never grows without bound.
        inline long TakeDrain(float& carry, float served, float costPerPoint, long gauge)
        {
            if (served > 0.0f && costPerPoint > 0.0f)
                carry += served * costPerPoint;
            if (!std::isfinite(carry) || carry < 0.0f)
            {
                carry = 0.0f;
                return 0;
            }
            if (carry < 1.0f)
                return 0;
            long whole = static_cast<long>(std::floor(carry));
            if (whole > gauge)
            {
                carry = 0.0f;
                return gauge > 0 ? gauge : 0;
            }
            carry -= static_cast<float>(whole);
            return whole;
        }

        inline bool IsIdleWhat(int what)
        {
            return what == kWhatNone || what == kWhatSelect || what == kWhatStop;
        }

        // Deploy holds while the pending order is idle and, once the current
        // order has been seen idle after deploying, while it stays idle (the
        // Stop issued at deploy needs a frame to land). `sawIdleCurrent` is
        // updated in place.
        inline bool KeepsDeploy(int pendingWhat, int currentWhat, bool& sawIdleCurrent)
        {
            if (!IsIdleWhat(pendingWhat))
                return false;
            if (IsIdleWhat(currentWhat))
            {
                sawIdleCurrent = true;
                return true;
            }
            return !sawIdleCurrent;
        }

        inline bool IsServiceClassId(int classId)
        {
            return classId == kClassIdHelicopter || classId == kClassIdVehicle;
        }

        // Same team, or an ally per the engine's IsAlly answer; team 0
        // (neutral) is never serviced.
        inline bool IsFriendlyTeam(int mruTeam, int targetTeam, bool engineSaysAlly)
        {
            if (targetTeam <= 0 || mruTeam <= 0)
                return false;
            return targetTeam == mruTeam || engineSaysAlly;
        }

        inline bool InRadius(double dx, double dy, double dz, float radius)
        {
            if (!(radius > 0.0f))
                return false;
            const double r = static_cast<double>(radius);
            const double d2 = dx * dx + dy * dy + dz * dz;
            return std::isfinite(d2) && d2 <= r * r;
        }

        // Pod spawn point: `back` metres behind the MRU along its front axis.
        inline void DropPosition(const double (&posit)[3], const float (&front)[3], float back,
                                 double (&out)[3])
        {
            for (int i = 0; i < 3; ++i)
                out[i] = posit[i] - static_cast<double>(front[i]) * static_cast<double>(back);
        }
    }
}
