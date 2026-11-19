#pragma once
// mru_class_policy.h
// Pure rules for ODF `classLabel = "mru"` (Docs/MRU_CLASS.md): the
// [MruClass] key set with its defaults and sanitizing, and the menu probe's
// slot/mode mapping. No Windows or engine calls, so
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

        // Read and stored; nothing uses them yet (menu probe, plan step 1-2).
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

        // ---- the menu probe -----------------------------------------------

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
    }
}
