// unit_loadouts_policy.h
// Pure decision rules for [Gameplay] UnitLoadouts (src/patches/unit_loadouts.cpp,
// Docs/UNIT_LOADOUTS.md). No Windows or engine access, so the tests can
// include it: which cost-function caller is which, the surcharge sum, when a
// chosen weapon falls back to stock, the edit lock, the swap gate and the
// weapon page layout.
#pragma once

#include <cstddef>
#include <cstdint>
#include <cstring>

namespace BZROpenShim
{
    namespace UnitLoadoutsPolicy
    {
        // GameObjectClass weaponHard[5] / weaponClass[5] (FUN_004e0450).
        constexpr int kMaxSlots = 5;
        // A page below the PRODMENU root: slots 1..8 for entries, 9 is Back.
        constexpr int kPagePositions = 8;
        // Label buffer of a menu stub (+0x64, 31 chars and the terminator).
        constexpr size_t kLabelChars = 32;
        // Weapon ODF token as kept in WeaponClass +0x18 (8 chars, unterminated when full).
        constexpr size_t kWeaponOdfChars = 8;
        // A surcharge never exceeds this (sum of five Armory prices).
        constexpr int kMaxSurcharge = 1000000;

        // ---- Who called the cost function --------------------------------------
        enum class CostCaller
        {
            Other,      // menu display, enable gate, RtsBuildQueue afford test, Armory
            StartBuild, // Producer::StartBuild 0x005AECB0: the charge
            Refund,     // Producer cancel 0x005AED80: the refund
        };

        inline CostCaller ClassifyCaller(uint32_t returnAddress, uint32_t startBuildReturn, uint32_t refundReturn)
        {
            if (returnAddress != 0 && returnAddress == startBuildReturn)
                return CostCaller::StartBuild;
            if (returnAddress != 0 && returnAddress == refundReturn)
                return CostCaller::Refund;
            return CostCaller::Other;
        }

        // ---- Surcharge gate ------------------------------------------------------
        // A surcharge applies only to the local player's team, in single player,
        // with the feature active and a loadout stored for the unit ODF.
        inline bool SurchargeApplies(bool active, bool singlePlayer, bool playerTeam, bool hasLoadout)
        {
            return active && singlePlayer && playerTeam && hasLoadout;
        }

        // ---- Choice resolution ---------------------------------------------------
        enum class ChoiceVerdict
        {
            Stock,         // nothing chosen for this slot
            Chosen,        // the chosen weapon is fitted and charged
            NoArmory,      // fallback: the player has no live Armory
            NotOffered,    // fallback: the Armory does not offer the weapon
            WrongCategory, // fallback: the offer does not fit the slot's hardpoint type
        };

        inline const char* VerdictName(ChoiceVerdict verdict)
        {
            switch (verdict)
            {
            case ChoiceVerdict::Stock:
                return "stock";
            case ChoiceVerdict::Chosen:
                return "chosen";
            case ChoiceVerdict::NoArmory:
                return "stock (no Armory)";
            case ChoiceVerdict::NotOffered:
                return "stock (not offered by the Armory)";
            case ChoiceVerdict::WrongCategory:
                return "stock (hardpoint type differs)";
            }
            return "unknown";
        }

        // The design's fallback rule: a chosen weapon is fitted only when the
        // player's current Armory offers it and it fits the slot; anything
        // else builds the stock weapon at no surcharge.
        inline ChoiceVerdict ResolveChoice(bool hasChoice, bool armoryPresent, bool offered, bool categoryMatches)
        {
            if (!hasChoice)
                return ChoiceVerdict::Stock;
            if (!armoryPresent)
                return ChoiceVerdict::NoArmory;
            if (!offered)
                return ChoiceVerdict::NotOffered;
            if (!categoryMatches)
                return ChoiceVerdict::WrongCategory;
            return ChoiceVerdict::Chosen;
        }

        // ---- Surcharge math ------------------------------------------------------
        // The FULL Armory price of every slot whose verdict is Chosen. A
        // negative price (never seen) counts as 0; the sum is capped.
        inline int Surcharge(const ChoiceVerdict* verdicts, const int* prices, int count)
        {
            long long sum = 0;
            for (int i = 0; i < count && i < kMaxSlots; ++i)
            {
                if (verdicts[i] == ChoiceVerdict::Chosen && prices[i] > 0)
                    sum += prices[i];
            }
            return sum > kMaxSurcharge ? kMaxSurcharge : static_cast<int>(sum);
        }

        inline int QuotedCost(int baseCost, int surcharge)
        {
            if (surcharge <= 0)
                return baseCost;
            const long long total = static_cast<long long>(baseCost) + surcharge;
            return total > 0x7FFFFFFF ? 0x7FFFFFFF : static_cast<int>(total);
        }

        // The refund returns base + the surcharge frozen at StartBuild, but only
        // for the build that quote belongs to (the class the producer still
        // builds, +0x300, is the class the quote was frozen for).
        inline int RefundSurcharge(bool haveFrozen, uint32_t frozenClass, uint32_t refundClass, uint32_t buildClass,
                                   int frozenSurcharge)
        {
            if (!haveFrozen || frozenClass == 0 || frozenClass != refundClass || buildClass != refundClass)
                return 0;
            return frozenSurcharge > 0 ? frozenSurcharge : 0;
        }

        // ---- Edit lock -----------------------------------------------------------
        // Edits of a unit's loadout are refused while any of the player's
        // producers is building that unit (its +0x300 build class).
        inline bool EditLocked(uint32_t unitClass, const uint32_t* buildingClasses, int count)
        {
            if (unitClass == 0)
                return false;
            for (int i = 0; i < count; ++i)
            {
                if (buildingClasses[i] == unitClass)
                    return true;
            }
            return false;
        }

        // ---- Swap gate -----------------------------------------------------------
        enum class SwapVerdict
        {
            Swap,
            NoQuote,         // no frozen quote for this producer, or another class
            NotChosen,       // the slot builds stock
            SlotOutOfRange,  // FUN_00612f10's own range test never rejects; ours does
            NotStock,        // the slot no longer holds the class's stock weapon
            HardpointDiffers // the built unit's hardpoint type is not the weapon's
        };

        inline const char* SwapVerdictName(SwapVerdict verdict)
        {
            switch (verdict)
            {
            case SwapVerdict::Swap:
                return "swap";
            case SwapVerdict::NoQuote:
                return "no quote";
            case SwapVerdict::NotChosen:
                return "stock";
            case SwapVerdict::SlotOutOfRange:
                return "slot out of range";
            case SwapVerdict::NotStock:
                return "slot does not hold the stock weapon";
            case SwapVerdict::HardpointDiffers:
                return "hardpoint type differs";
            }
            return "unknown";
        }

        inline SwapVerdict PlanSwap(bool quoteMatches, bool slotChosen, int slot, bool slotHoldsStock,
                                    bool hardpointMatches)
        {
            if (!quoteMatches)
                return SwapVerdict::NoQuote;
            if (!slotChosen)
                return SwapVerdict::NotChosen;
            if (slot < 0 || slot >= kMaxSlots)
                return SwapVerdict::SlotOutOfRange;
            if (!slotHoldsStock)
                return SwapVerdict::NotStock;
            if (!hardpointMatches)
                return SwapVerdict::HardpointDiffers;
            return SwapVerdict::Swap;
        }

        // ---- Unfitted credit -----------------------------------------------------
        // Scrap given back at FinishBuild for weapons that were paid for but not
        // fitted. When the built unit is not the quoted class, the whole frozen
        // surcharge comes back; otherwise the price of each Chosen slot that was
        // not fitted. Never negative, never more than the frozen surcharge.
        inline int UnfittedCredit(bool quoteMatches, int frozenSurcharge, const ChoiceVerdict* verdicts,
                                  const int* prices, const bool* fitted, int count)
        {
            if (frozenSurcharge <= 0)
                return 0;
            if (!quoteMatches)
                return frozenSurcharge;
            long long sum = 0;
            for (int i = 0; i < count && i < kMaxSlots; ++i)
            {
                if (verdicts[i] == ChoiceVerdict::Chosen && !fitted[i] && prices[i] > 0)
                    sum += prices[i];
            }
            return sum > frozenSurcharge ? frozenSurcharge : static_cast<int>(sum);
        }

        // ---- Weapon page layout --------------------------------------------------
        // Entries are "Stock" then each compatible weapon the Armory offers.
        // When they fit in kPagePositions they all show; otherwise each page
        // shows kPagePositions - 1 entries and a "More" button that pages on
        // (wrapping to the first page).
        struct PageLayout
        {
            int first = 0;      // first entry index shown
            int count = 0;      // entries shown
            bool more = false;  // the last position is "More"
            int nextOffset = 0; // offset "More" moves to
        };

        inline PageLayout LayoutPage(int total, int offset)
        {
            PageLayout page;
            if (total <= 0)
                return page;
            if (total <= kPagePositions)
            {
                page.count = total;
                return page;
            }
            const int per = kPagePositions - 1;
            if (offset < 0 || offset >= total)
                offset = 0;
            offset -= offset % per;
            page.first = offset;
            page.count = total - offset < per ? total - offset : per;
            page.more = true;
            page.nextOffset = offset + per >= total ? 0 : offset + per;
            return page;
        }

        // ---- Labels ----------------------------------------------------------------
        // Appends text to out (truncating, always terminated); returns the new length.
        inline size_t AppendText(char* out, size_t outSize, size_t length, const char* text)
        {
            while (text && *text && length + 1 < outSize)
                out[length++] = *text++;
            out[length] = '\0';
            return length;
        }

        // Slot page: "N: <weapon>" with "*" when the slot is changed from stock.
        inline bool FormatSlotLabel(int slot, const char* weaponName, bool changed, char* out, size_t outSize)
        {
            if (!out || outSize == 0)
                return false;
            out[0] = '\0';
            if (slot < 0 || slot >= kMaxSlots)
                return false;
            const char prefix[4] = {static_cast<char>('1' + slot), ':', ' ', '\0'};
            size_t length = AppendText(out, outSize, 0, prefix);
            length = AppendText(out, outSize, length, weaponName && weaponName[0] ? weaponName : "?");
            if (changed)
                length = AppendText(out, outSize, length, "*");
            return length > 0;
        }

        // Weapon page entry: the name, "*" on the current choice.
        inline bool FormatChoiceLabel(const char* name, bool current, char* out, size_t outSize)
        {
            if (!out || outSize == 0)
                return false;
            out[0] = '\0';
            if (!name || !name[0])
                return false;
            size_t length = AppendText(out, outSize, 0, name);
            if (current)
                length = AppendText(out, outSize, length, "*");
            return length > 0;
        }

        // Weapon ODF tokens compare on at most kWeaponOdfChars, case-insensitive.
        inline bool SameWeaponOdf(const char* a, const char* b)
        {
            if (!a || !b || !a[0] || !b[0])
                return false;
            for (size_t i = 0; i < kWeaponOdfChars; ++i)
            {
                char ca = a[i];
                char cb = b[i];
                if (ca >= 'A' && ca <= 'Z')
                    ca = static_cast<char>(ca - 'A' + 'a');
                if (cb >= 'A' && cb <= 'Z')
                    cb = static_cast<char>(cb - 'A' + 'a');
                if (ca != cb)
                    return false;
                if (ca == '\0')
                    return true;
            }
            return true;
        }
    }
}
