// unit_loadouts.cpp
// BZR Open Shim - [Gameplay] UnitLoadouts (default off, single player):
// per-unit weapon loadouts picked in the Recycler/Factory build menu.
// Milestone M1 of Docs/APPROVED_DESIGNS.md item 18 (menu, surcharge, swap);
// the save sidecar (M2) is not built, so loadouts live in memory for the
// mission and are dropped at mission end or load.
//
//   Menu   Alt+pick on a unit in the player's Recycler or Factory menu opens
//          that unit's loadout pages inside the PRODMENU panel: its weapon
//          slots, then for a slot "Stock" and every compatible weapon the
//          player's current Armory offers (with "More" paging). Back steps
//          out. Settings are keyed by the unit ODF and apply wherever it is
//          built.
//   Cost   An entry detour on BuildScrapCost 0x004E1B90 adds the FULL Armory
//          price (that same function on the weapon powerup class) of every
//          slot whose chosen weapon the Armory offers now. That function is
//          the single source for the menu display, the enable gate, the charge
//          (Producer::StartBuild 0x005AECB0) and the refund (0x005AED80): the
//          charge freezes its quote per producer, the refund returns exactly
//          that quote, and edits of a unit are refused while it is building.
//   Swap   The shared Recycler/Factory FinishBuild slot-42 hook
//          (producer_rally_points.cpp) calls UnitLoadoutsOnUnitBuilt after the
//          stock FinishBuild; each frozen choice goes on through
//          FUN_00612F10(unit, WeaponClass*, slot), the powerup give path.
//
// Evidence, decision log lines and limits: Docs/UNIT_LOADOUTS.md.
#include "bzr_hooks_internal.h"
#include "bzr_object_layout.h"
#include "bzr_options_ui.h"
#include "engine_globals.h"
#include "hook_engine.h"
#include "openshim_l10n_text.h"
#include "patcher.h"
#include "shim_log.h"
#include "unit_loadouts_policy.h"

#include <Windows.h>
#include <atomic>
#include <cstdarg>
#include <cstdint>
#include <cstring>
#include <string>
#include <unordered_map>

namespace BZROpenShim::Hooks
{
    using BZROpenShim::L10n::ShimText;

    namespace
    {
        namespace P = UnitLoadoutsPolicy;

        using FnCost = int(__cdecl*)(int teamNumber, void* cls);
        using FnGetObj = void*(__cdecl*)(uint32_t handle);
        using FnGetHandle = uint32_t(__thiscall*)(void* obj);
        using FnGiveWeapon = bool(__cdecl*)(void* obj, void* weaponClass, int slot);
        using FnPlaySound = int(__cdecl*)(const char* filename, uint32_t, uint32_t, uint32_t);
        // Team::AddScrap (FUN_005e1010): __thiscall, ret 4.
        using FnAddScrap = void(__thiscall*)(void* team, int amount);

        // GameObject / Producer (rts_build_queue.cpp, producer_build_menu.cpp).
        constexpr size_t kObjectClassOffset = 0xF8;
        // A producer's Team* (ecx of FUN_005e1010 at 0x005AED01 and 0x005AEDF1).
        constexpr size_t kProducerTeamOffset = 0x17C;
        constexpr size_t kTeamNumberOffset = 0x174;
        constexpr size_t kTeamPtrOffset = 0x17C;
        constexpr size_t kOwnershipOffset = 0x80; // == 2: network replica
        constexpr uint8_t kReplicaOwnership = 2;
        constexpr size_t kObj76FlagsOffset = 0x14;
        constexpr uint32_t kObj76DeadFlag = 0x200;
        constexpr size_t kBuildClassOffset = 0x300;
        constexpr size_t kDeployStateOffset = 0x228; // 2: deployed
        constexpr size_t kModeListOffset = 0x1A4;
        // Team slots (Team::GetSlot FUN_005E0F70 = *(team + slot*4); Lua
        // GetRecyclerHandle/GetFactoryHandle/GetArmoryHandle pass 1/2/3).
        constexpr uint32_t kRecyclerTeamSlot = 1;
        constexpr uint32_t kFactoryTeamSlot = 2;
        constexpr uint32_t kArmoryTeamSlot = 3;
        // GameObjectClass (ctor FUN_004E0450 lines 169-191).
        constexpr size_t kClassOdfOffset = 0x30;         // char[8]
        constexpr size_t kClassWeaponHardOffset = 0xE4;  // char[4] x5
        constexpr size_t kClassWeaponClassOffset = 0xF8; // WeaponClass* x5
        // ArmoryClass build lists (Armory::UpdateModeList FUN_00472780 lines 44-68).
        struct BuildList
        {
            size_t offset;
            int count;
        };
        constexpr BuildList kArmoryLists[] = {
            { 0x608, 5 }, { 0x660, 9 }, { 0x684, 9 }, { 0x6A8, 9 }, { 0x6CC, 9 },
        };
        // Weapon powerup class: 'WEPN' at +0x14, WeaponClass* at +0x170
        // (FUN_00472da0 lines 115-121).
        constexpr size_t kPowerupSigOffset = 0x14;
        constexpr uint32_t kWeaponPowerupSig = 0x5745504E;
        constexpr size_t kPowerupWeaponClassOffset = 0x170;
        // WeaponClass (ctor FUN_00611AA0): ODF +0x18, display name +0x38,
        // hardpoint category +0x74 (matched with hardpoint +0x84 in FUN_00472da0 line 128).
        constexpr size_t kWeaponClassOdfOffset = 0x18;
        constexpr size_t kWeaponClassNameOffset = 0x38;
        constexpr size_t kWeaponClassNameChars = 0x20;
        constexpr size_t kWeaponClassCategoryOffset = 0x74;
        // Carrier (GameObject +0x1A0, FUN_00417CA0): hardpoint i at +4+i*4
        // (FUN_00417F40), weapon i at +0x18+i*4 when mask +0x2C has bit i
        // (FUN_00417F60); a weapon's class at +0x08; a hardpoint's type at +0x84.
        constexpr size_t kCarrierOffset = 0x1A0;
        constexpr size_t kCarrierHardpointsOffset = 0x04;
        constexpr size_t kCarrierWeaponsOffset = 0x18;
        constexpr size_t kCarrierMaskOffset = 0x2C;
        constexpr size_t kWeaponToClassOffset = 0x08;
        constexpr size_t kHardpointTypeOffset = 0x84;
        // Menu stubs (producer_build_menu.cpp): a 0x200-byte class-shaped block
        // with the label at +0x64; unit slot range at +0x13C/+0x140 set to -1
        // (no unit-cap test).
        constexpr size_t kStubSize = 0x200;
        constexpr size_t kStubLabelOffset = 0x64;
        constexpr size_t kStubMinSlotOffset = 0x13C;
        constexpr size_t kStubMaxSlotOffset = 0x140;
        // Mode-list positions of a page below the root: 1..8, Back at 9.
        constexpr int kFirstPosition = 1;
        constexpr int kBackPosition = 9;
        constexpr int kModeBack = 0x16;
        constexpr uint32_t kModeLastNamed = 0x1A;
        constexpr size_t kUpdateModeListVtableIndex = 23;
        constexpr size_t kSetActiveModeVtableIndex = 11;
        // The held-key dword (InputHeldModifierKeys): Alt bit (FUN_00434bf0).
        constexpr uint32_t kHeldAltBit = 0x1000000;
        // Call-site rows: return address = row + length of its guard bytes.
        constexpr uint32_t kStartBuildCostReturnOffset = 0x29;
        constexpr uint32_t kRefundCostReturnOffset = 0x3F;
        // BuildScrapCost prologue: push ebp; mov ebp,esp; sub esp,0Ch (6 bytes stolen).
        const uint8_t kCostPrologue[6] = { 0x55, 0x8B, 0xEC, 0x83, 0xEC, 0x0C };
        constexpr int kMaxInstallAttempts = 40;
        constexpr const char* kRefuseSound = "mnu_buzz.wav";

        // Engine rows (patch thread, then read-only).
        uint32_t g_GetObjAddr = 0;
        uint32_t g_CostAddr = 0;
        uint32_t g_StartBuildSiteAddr = 0;
        uint32_t g_RefundSiteAddr = 0;
        uint32_t g_GiveWeaponAddr = 0;
        uint32_t g_AddScrapAddr = 0;
        uint32_t g_HeldModsAddr = 0;
        uint32_t g_RecyclerVtable = 0;
        uint32_t g_FactoryVtable = 0;
        uint32_t g_ArmoryVtable = 0;
        uint32_t g_StartBuildReturn = 0;
        uint32_t g_RefundReturn = 0;
        FnGetObj g_FnGetObj = nullptr;
        FnGiveWeapon g_FnGiveWeapon = nullptr;
        FnAddScrap g_FnAddScrap = nullptr;
        FnPlaySound g_FnPlaySound = nullptr;

        InlineDetour32 g_CostDetour;
        FnCost volatile g_OrigCost = nullptr;

        bool g_RowsBound = false;
        bool g_CostDetourInstalled = false;
        bool g_CostDetourFailed = false;
        bool g_FinishBuildHooked = false;
        bool g_ConfigRead = false;
        bool g_Enabled = false;
        bool g_KillSwitch = false;
        std::atomic<bool> g_Active{ false };
        volatile long g_LogBudget = 200;
        volatile long g_InstallLogBudget = 16;

        // ---- state (game thread) ------------------------------------------------

        struct SlotChoice
        {
            char odf[P::kWeaponOdfChars + 1] = {};
            char name[kWeaponClassNameChars] = {};
        };
        struct Loadout
        {
            SlotChoice slots[P::kMaxSlots];
        };
        // Keyed by the unit ODF token (class +0x30), lower case.
        std::unordered_map<std::string, Loadout> g_Loadouts;

        // What a build was charged, frozen at StartBuild per producer.
        struct Quote
        {
            uint32_t unitClass = 0;
            int surcharge = 0;
            P::ChoiceVerdict verdicts[P::kMaxSlots] = {};
            uint32_t weaponClasses[P::kMaxSlots] = {};
            uint32_t powerups[P::kMaxSlots] = {};
            int prices[P::kMaxSlots] = {};
        };
        struct FrozenQuote
        {
            uint32_t handle = 0;
            Quote quote;
        };
        std::unordered_map<void*, FrozenQuote> g_Frozen;

        // An open loadout page per producer.
        struct Cursor
        {
            uint32_t unitClass = 0;
            uint32_t team = 0;
            int slot = -1; // -1: the slot page
            int offset = 0;
        };
        std::unordered_map<void*, Cursor> g_Cursors;

        // Buttons: slot 0..4, Stock, More, choice 0..6. Never freed: a stale
        // mode value may still name one.
        enum StubIndex
        {
            kStubSlot0 = 0,
            kStubStock = P::kMaxSlots,
            kStubMore,
            kStubChoice0,
            kStubCount = kStubChoice0 + P::kPagePositions,
        };
        uint8_t* g_Stubs[kStubCount] = {};
        uint32_t g_ChoiceWeaponClass[P::kPagePositions] = {};
        uint32_t g_ChoicePowerup[P::kPagePositions] = {};

        // Change-only decision lines, per key.
        std::unordered_map<std::string, std::string> g_LastDecision;

        void LogBudgeted(const wchar_t* fmt, ...)
        {
            if (InterlockedDecrement(&g_LogBudget) < 0)
                return;
            wchar_t buffer[512];
            va_list args;
            va_start(args, fmt);
            _vsnwprintf_s(buffer, _TRUNCATE, fmt, args);
            va_end(args);
            Log(L"%ls", buffer);
        }

        // Logs `text` for `key` only when it differs from the last line for that key.
        void LogDecision(const std::string& key, const std::string& text)
        {
            std::string& last = g_LastDecision[key];
            if (last == text)
                return;
            last = text;
            Log(L"[LOADOUT] %hs: %hs\n", key.c_str(), text.c_str());
        }

        // ---- fault-safe engine access ---------------------------------------------

        bool ReadBytes(uintptr_t address, void* out, size_t size)
        {
            if (address < 0x10000)
                return false;
            __try
            {
                std::memcpy(out, reinterpret_cast<const void*>(address), size);
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        bool ReadU32(uintptr_t address, uint32_t& out)
        {
            return ReadBytes(address, &out, sizeof(out));
        }

        bool WriteBytes(uintptr_t address, const void* data, size_t size)
        {
            if (address < 0x10000)
                return false;
            __try
            {
                std::memcpy(reinterpret_cast<void*>(address), data, size);
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        void* SafeGetObj(uint32_t handle)
        {
            if (!g_FnGetObj || handle == 0)
                return nullptr;
            __try
            {
                return g_FnGetObj(handle);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return nullptr;
            }
        }

        // A frozen record is honoured only while its handle still names the
        // producer it is keyed by; otherwise the producer died and the address
        // may belong to another object.
        bool FrozenIsLive(const std::pair<void* const, FrozenQuote>& entry)
        {
            return entry.first != nullptr && SafeGetObj(entry.second.handle) == entry.first;
        }

        uint32_t SafeGetHandle(void* obj)
        {
            const auto fn = reinterpret_cast<FnGetHandle>(g_GameObjectGetHandleAddr);
            if (!fn || !obj)
                return 0;
            __try
            {
                return fn(obj);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return 0;
            }
        }

        // The original cost function (the detour trampoline, or the function
        // itself before the detour is in). False on a fault.
        bool SafeOrigCost(int team, uint32_t cls, int& out)
        {
            FnCost fn = g_OrigCost;
            if (!fn)
                fn = reinterpret_cast<FnCost>(static_cast<uintptr_t>(g_CostAddr));
            if (!fn || cls < 0x10000)
                return false;
            __try
            {
                out = fn(team, reinterpret_cast<void*>(static_cast<uintptr_t>(cls)));
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        bool SafeGiveWeapon(void* obj, uint32_t weaponClass, int slot, bool& result)
        {
            result = false;
            if (!g_FnGiveWeapon || !obj || weaponClass == 0)
                return false;
            __try
            {
                result = g_FnGiveWeapon(obj, reinterpret_cast<void*>(static_cast<uintptr_t>(weaponClass)), slot);
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        bool SafeAddScrap(void* team, int amount)
        {
            if (!g_FnAddScrap || !team || amount <= 0)
                return false;
            __try
            {
                g_FnAddScrap(team, amount);
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        bool SafeSetMode(void* modeList, int slot, uint32_t value, bool enabled)
        {
            if (!g_BzrFn_ModeListSetMode || !modeList)
                return false;
            __try
            {
                g_BzrFn_ModeListSetMode(modeList, slot, static_cast<int>(value), enabled ? 1 : 0);
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        bool SafeRefreshModeList(void* self)
        {
            __try
            {
                RefreshProducerMenuModeList(self);
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        void SafePlayRefuse()
        {
            if (!g_FnPlaySound)
                return;
            __try
            {
                g_FnPlaySound(kRefuseSound, 0, 0, 0);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
            }
        }

        // ---- engine reads -----------------------------------------------------------

        // Up to `chars` bytes at `address`, stopped at the first NUL.
        std::string ReadText(uintptr_t address, size_t chars)
        {
            char raw[64] = {};
            if (chars > sizeof(raw) - 1 || !ReadBytes(address, raw, chars))
                return {};
            return std::string(raw, strnlen(raw, chars));
        }

        std::string Lower(std::string text)
        {
            for (char& c : text)
            {
                if (c >= 'A' && c <= 'Z')
                    c = static_cast<char>(c - 'A' + 'a');
            }
            return text;
        }

        std::string UnitKey(uint32_t cls)
        {
            return Lower(ReadText(cls + kClassOdfOffset, 8));
        }

        bool IsProducerVtable(uint32_t vtable)
        {
            return vtable != 0 && (vtable == g_RecyclerVtable || vtable == g_FactoryVtable);
        }

        bool IsLiveOwn(void* obj, uint32_t playerTeam)
        {
            const uintptr_t base = reinterpret_cast<uintptr_t>(obj);
            uint8_t ownership = 0;
            uint32_t obj76 = 0;
            uint32_t team = 0;
            if (!obj || !ReadBytes(base + kOwnershipOffset, &ownership, 1) || ownership == kReplicaOwnership ||
                !ReadU32(base + kGameObjectObjOffset, obj76) || !ReadU32(base + kTeamNumberOffset, team))
                return false;
            if (obj76 != 0)
            {
                uint32_t flags = 0;
                if (!ReadU32(obj76 + kObj76FlagsOffset, flags) || (flags & kObj76DeadFlag) != 0)
                    return false;
            }
            return team == playerTeam;
        }

        // The player's own live Recycler or Factory.
        bool IsLiveOwnProducer(void* obj, uint32_t playerTeam)
        {
            uint32_t vtable = 0;
            return obj && ReadU32(reinterpret_cast<uintptr_t>(obj), vtable) && IsProducerVtable(vtable) &&
                   IsLiveOwn(obj, playerTeam);
        }

        void* ReadPlayer()
        {
            const uintptr_t slot = EngineGlobals::UserObjectSlot();
            uint32_t player = 0;
            return slot && ReadU32(slot, player) && player != 0 ? reinterpret_cast<void*>(static_cast<uintptr_t>(player))
                                                                : nullptr;
        }

        bool ReadPlayerTeam(uint32_t& playerTeam)
        {
            void* const player = ReadPlayer();
            return player && ReadU32(reinterpret_cast<uintptr_t>(player) + kTeamNumberOffset, playerTeam);
        }

        // The object in the player's team slot (Team::GetSlot).
        void* PlayerTeamSlot(uint32_t slot)
        {
            void* const player = ReadPlayer();
            uint32_t team = 0;
            uint32_t obj = 0;
            if (!player || !ReadU32(reinterpret_cast<uintptr_t>(player) + kTeamPtrOffset, team) || team == 0 ||
                !ReadU32(team + slot * 4, obj) || obj == 0)
                return nullptr;
            return reinterpret_cast<void*>(static_cast<uintptr_t>(obj));
        }

        void* FindArmory(uint32_t playerTeam)
        {
            void* const obj = PlayerTeamSlot(kArmoryTeamSlot);
            uint32_t vtable = 0;
            return obj && g_ArmoryVtable != 0 && ReadU32(reinterpret_cast<uintptr_t>(obj), vtable) &&
                           vtable == g_ArmoryVtable && IsLiveOwn(obj, playerTeam)
                       ? obj
                       : nullptr;
        }

        uint32_t BuildClassOf(void* obj)
        {
            uint32_t cls = 0;
            if (obj)
                ReadU32(reinterpret_cast<uintptr_t>(obj) + kBuildClassOffset, cls);
            return cls;
        }

        // The class's stock weapon in slot i (0 when the slot is empty).
        uint32_t StockWeaponClass(uint32_t cls, int slot)
        {
            uint32_t weaponClass = 0;
            char hard[4] = {};
            if (!ReadBytes(cls + kClassWeaponHardOffset + slot * 4, hard, sizeof(hard)) || hard[0] == '\0' ||
                !ReadU32(cls + kClassWeaponClassOffset + slot * 4, weaponClass))
                return 0;
            return weaponClass;
        }

        int ConfigurableSlotCount(uint32_t cls)
        {
            int count = 0;
            for (int i = 0; i < P::kMaxSlots; ++i)
                count += StockWeaponClass(cls, i) != 0 ? 1 : 0;
            return count;
        }

        bool ReadCategory(uint32_t weaponClass, uint32_t& category)
        {
            return weaponClass != 0 && ReadU32(weaponClass + kWeaponClassCategoryOffset, category);
        }

        std::string WeaponName(uint32_t weaponClass)
        {
            std::string name = ReadText(weaponClass + kWeaponClassNameOffset, kWeaponClassNameChars - 1);
            return name.empty() ? ReadText(weaponClass + kWeaponClassOdfOffset, P::kWeaponOdfChars) : name;
        }

        std::string WeaponOdf(uint32_t weaponClass)
        {
            return ReadText(weaponClass + kWeaponClassOdfOffset, P::kWeaponOdfChars);
        }

        struct Offer
        {
            uint32_t powerup = 0;
            uint32_t weaponClass = 0;
        };

        // Every weapon powerup the Armory's class lists, in list order.
        int ReadOffers(void* armory, Offer* out, int capacity)
        {
            uint32_t armoryClass = 0;
            if (!armory || !ReadU32(reinterpret_cast<uintptr_t>(armory) + kObjectClassOffset, armoryClass) ||
                armoryClass == 0)
                return 0;
            int count = 0;
            for (const BuildList& list : kArmoryLists)
            {
                for (int i = 0; i < list.count && count < capacity; ++i)
                {
                    uint32_t cls = 0;
                    uint32_t sig = 0;
                    uint32_t weaponClass = 0;
                    if (!ReadU32(armoryClass + list.offset + i * 4, cls) || cls == 0 ||
                        !ReadU32(cls + kPowerupSigOffset, sig) || sig != kWeaponPowerupSig ||
                        !ReadU32(cls + kPowerupWeaponClassOffset, weaponClass) || weaponClass == 0)
                        continue;
                    out[count++] = Offer{ cls, weaponClass };
                }
            }
            return count;
        }
        constexpr int kMaxOffers = 5 + 9 * 4;

        // ---- quotes ----------------------------------------------------------------

        const Loadout* FindLoadout(uint32_t cls)
        {
            if (g_Loadouts.empty())
                return nullptr;
            const auto found = g_Loadouts.find(UnitKey(cls));
            return found == g_Loadouts.end() ? nullptr : &found->second;
        }

        bool HasChoices(const Loadout& loadout)
        {
            for (const SlotChoice& choice : loadout.slots)
            {
                if (choice.odf[0] != '\0')
                    return true;
            }
            return false;
        }

        // The quote for building `cls` now: each chosen slot resolved against
        // the player's current Armory, priced at the Armory's own cost.
        Quote LiveQuote(uint32_t cls, int team, uint32_t playerTeam, const Loadout& loadout)
        {
            Quote quote;
            quote.unitClass = cls;
            void* const armory = FindArmory(playerTeam);
            Offer offers[kMaxOffers];
            const int offerCount = ReadOffers(armory, offers, kMaxOffers);
            std::string summary;
            for (int i = 0; i < P::kMaxSlots; ++i)
            {
                const SlotChoice& choice = loadout.slots[i];
                const bool hasChoice = choice.odf[0] != '\0';
                const uint32_t stock = StockWeaponClass(cls, i);
                uint32_t stockCategory = 0;
                const bool stockKnown = ReadCategory(stock, stockCategory);
                const Offer* match = nullptr;
                for (int k = 0; hasChoice && k < offerCount && !match; ++k)
                {
                    if (P::SameWeaponOdf(WeaponOdf(offers[k].weaponClass).c_str(), choice.odf))
                        match = &offers[k];
                }
                uint32_t category = 0;
                const bool categoryMatches =
                    match && stockKnown && ReadCategory(match->weaponClass, category) && category == stockCategory;
                quote.verdicts[i] = P::ResolveChoice(hasChoice && stock != 0, armory != nullptr, match != nullptr,
                                                     categoryMatches);
                if (quote.verdicts[i] == P::ChoiceVerdict::Chosen)
                {
                    quote.weaponClasses[i] = match->weaponClass;
                    quote.powerups[i] = match->powerup;
                    int price = 0;
                    quote.prices[i] = SafeOrigCost(team, match->powerup, price) ? price : 0;
                }
                if (hasChoice)
                {
                    char part[96];
                    _snprintf_s(part, _TRUNCATE, "%sslot%d=%s %s", summary.empty() ? "" : ", ", i + 1, choice.odf,
                                P::VerdictName(quote.verdicts[i]));
                    summary += part;
                    if (quote.verdicts[i] == P::ChoiceVerdict::Chosen)
                    {
                        _snprintf_s(part, _TRUNCATE, " +%d", quote.prices[i]);
                        summary += part;
                    }
                }
            }
            quote.surcharge = P::Surcharge(quote.verdicts, quote.prices, P::kMaxSlots);
            if (!summary.empty())
                LogDecision("quote " + UnitKey(cls), summary + "; surcharge " + std::to_string(quote.surcharge));
            return quote;
        }

        // ---- the cost detour ----------------------------------------------------------

        int StubChoiceIndex(uint32_t cls)
        {
            for (int k = 0; k < P::kPagePositions; ++k)
            {
                if (g_Stubs[kStubChoice0 + k] && reinterpret_cast<uintptr_t>(g_Stubs[kStubChoice0 + k]) == cls)
                    return k;
            }
            return -1;
        }

        void* ReadCallerProducer(uint32_t callerEbp)
        {
            uint32_t producer = 0;
            return callerEbp > 4 && ReadU32(callerEbp - 4, producer) && producer != 0
                       ? reinterpret_cast<void*>(static_cast<uintptr_t>(producer))
                       : nullptr;
        }

        int CostBody(uint32_t returnAddress, int team, uint32_t cls, uint32_t callerEbp)
        {
            // A loadout weapon button shows its powerup's Armory price.
            if (cls > kModeLastNamed)
            {
                const int choice = StubChoiceIndex(cls);
                if (choice >= 0)
                {
                    int price = 0;
                    return g_ChoicePowerup[choice] != 0 && SafeOrigCost(team, g_ChoicePowerup[choice], price) ? price
                                                                                                                : 0;
                }
            }

            int base = 0;
            if (!SafeOrigCost(team, cls, base))
                return 0;

            const P::CostCaller caller = P::ClassifyCaller(returnAddress, g_StartBuildReturn, g_RefundReturn);
            if (caller == P::CostCaller::Refund)
            {
                // Honoured even after the option turns off: the player paid it.
                void* const producer = ReadCallerProducer(callerEbp);
                auto found = producer ? g_Frozen.find(producer) : g_Frozen.end();
                if (found != g_Frozen.end() && !FrozenIsLive(*found))
                {
                    g_Frozen.erase(found);
                    found = g_Frozen.end();
                }
                const bool have = found != g_Frozen.end();
                const int surcharge = P::RefundSurcharge(have, have ? found->second.quote.unitClass : 0, cls,
                                                         BuildClassOf(producer), have ? found->second.quote.surcharge : 0);
                if (have)
                {
                    if (surcharge > 0)
                        LogBudgeted(L"[LOADOUT] refund %hs: %d + surcharge %d\n", UnitKey(cls).c_str(), base, surcharge);
                    g_Frozen.erase(found);
                }
                return P::QuotedCost(base, surcharge);
            }

            uint32_t playerTeam = 0;
            const bool active = g_Active.load(std::memory_order_acquire);
            const bool playerSide = ReadPlayerTeam(playerTeam) && static_cast<uint32_t>(team) == playerTeam;

            if (caller == P::CostCaller::StartBuild)
            {
                void* const producer = ReadCallerProducer(callerEbp);
                // A new build replaces whatever this producer had frozen,
                // including a stale record left by a freed object at this address.
                if (producer)
                    g_Frozen.erase(producer);
                if (!producer || !playerSide || !IsLiveOwnProducer(producer, playerTeam))
                    return base;
                const Loadout* const loadout = FindLoadout(cls);
                const bool applies = P::SurchargeApplies(active, IsSinglePlayerSession(), playerSide,
                                                         loadout && HasChoices(*loadout));
                FrozenQuote frozen;
                frozen.handle = SafeGetHandle(producer);
                frozen.quote.unitClass = cls;
                if (applies)
                    frozen.quote = LiveQuote(cls, team, playerTeam, *loadout);
                // Every player build is tracked, surcharge or not, so the
                // edit lock and the swap see it.
                g_Frozen[producer] = frozen;
                if (frozen.quote.surcharge > 0)
                    LogBudgeted(L"[LOADOUT] charge %hs at producer 0x%08X: %d + surcharge %d\n", UnitKey(cls).c_str(),
                                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(producer)), base,
                                frozen.quote.surcharge);
                return P::QuotedCost(base, frozen.quote.surcharge);
            }

            // Display, enable gate, build queue: the live quote.
            const Loadout* const loadout = FindLoadout(cls);
            if (!loadout || !HasChoices(*loadout) || !playerSide)
                return base;
            const bool sp = IsSinglePlayerSession();
            if (!P::SurchargeApplies(active, sp, playerSide, true))
            {
                LogDecision("surcharge " + UnitKey(cls), active ? "not applied (not single player)" : "not applied (inactive)");
                return base;
            }
            return P::QuotedCost(base, LiveQuote(cls, team, playerTeam, *loadout).surcharge);
        }

        // Called by the entry thunk. C++ exceptions (allocation) never cross
        // into the engine: they fall back to the stock cost.
        int __cdecl CostImpl(uint32_t returnAddress, int team, uint32_t cls, uint32_t callerEbp)
        {
            try
            {
                return CostBody(returnAddress, team, cls, callerEbp);
            }
            catch (...)
            {
                int base = 0;
                return SafeOrigCost(team, cls, base) ? base : 0;
            }
        }

#if defined(_M_IX86)
        // Entered in place of BuildScrapCost (cdecl: [esp] return, [esp+4]
        // team, [esp+8] class); ebp is still the caller's frame. Calls
        // CostImpl(return, team, class, caller ebp) and returns its eax.
        __declspec(naked) void CostEntryThunk()
        {
            __asm
            {
                push ebp
                push dword ptr [esp + 12]
                push dword ptr [esp + 12]
                push dword ptr [esp + 12]
                call CostImpl
                add esp, 16
                ret
            }
        }
#endif

        // ---- the edit lock -------------------------------------------------------------

        bool UnitLocked(uint32_t cls, void* self)
        {
            constexpr int kCapacity = 3 + 16;
            uint32_t building[kCapacity] = {};
            int count = 0;
            building[count++] = BuildClassOf(self);
            building[count++] = BuildClassOf(PlayerTeamSlot(kRecyclerTeamSlot));
            building[count++] = BuildClassOf(PlayerTeamSlot(kFactoryTeamSlot));
            // Any other producer whose tracked build is this unit.
            // Records whose handle no longer names the keyed object are stale
            // (the producer died and its address may be reused): drop them.
            for (auto it = g_Frozen.begin(); it != g_Frozen.end();)
            {
                if (!FrozenIsLive(*it))
                {
                    it = g_Frozen.erase(it);
                    continue;
                }
                if (count < kCapacity && it->second.quote.unitClass == cls)
                    building[count++] = BuildClassOf(it->first);
                ++it;
            }
            return P::EditLocked(cls, building, count);
        }

        // ---- menu ------------------------------------------------------------------------

        bool AltHeld()
        {
            uint32_t held = 0;
            return g_HeldModsAddr != 0 && ReadU32(g_HeldModsAddr, held) && (held & kHeldAltBit) != 0;
        }

        bool EnsureStubs()
        {
            if (g_Stubs[kStubCount - 1])
                return true;
            for (int i = 0; i < kStubCount; ++i)
            {
                if (g_Stubs[i])
                    continue;
                uint8_t* const stub = static_cast<uint8_t*>(HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, kStubSize));
                if (!stub)
                    return false; // the ones made stay; the next call makes the rest
                const int32_t none = -1;
                std::memcpy(stub + kStubMinSlotOffset, &none, sizeof(none));
                std::memcpy(stub + kStubMaxSlotOffset, &none, sizeof(none));
                g_Stubs[i] = stub;
                // Weapon choices show their Armory price; the rest hide "00".
                if (i < kStubChoice0)
                    HideProducerMenuButtonCost(stub);
            }
            return true;
        }

        int StubIndexOf(uint32_t mode)
        {
            if (mode <= kModeLastNamed)
                return -1;
            for (int i = 0; i < kStubCount; ++i)
            {
                if (g_Stubs[i] && reinterpret_cast<uintptr_t>(g_Stubs[i]) == mode)
                    return i;
            }
            return -1;
        }

        void SetLabel(int stub, const char* text)
        {
            char label[P::kLabelChars] = {};
            if (text)
                strncpy_s(label, text, _TRUNCATE);
            std::memcpy(g_Stubs[stub] + kStubLabelOffset, label, sizeof(label));
        }

        uint32_t StubMode(int stub)
        {
            return static_cast<uint32_t>(reinterpret_cast<uintptr_t>(g_Stubs[stub]));
        }

        // The weapon page's entries: Stock, then every compatible weapon the
        // Armory offers other than the stock one.
        int ComposeChoices(uint32_t cls, int slot, uint32_t playerTeam, Offer* out, int capacity)
        {
            const uint32_t stock = StockWeaponClass(cls, slot);
            uint32_t stockCategory = 0;
            if (!ReadCategory(stock, stockCategory))
                return 0;
            Offer offers[kMaxOffers];
            const int offerCount = ReadOffers(FindArmory(playerTeam), offers, kMaxOffers);
            int count = 0;
            for (int k = 0; k < offerCount && count < capacity; ++k)
            {
                uint32_t category = 0;
                if (offers[k].weaponClass == stock || !ReadCategory(offers[k].weaponClass, category) ||
                    category != stockCategory)
                    continue;
                bool duplicate = false;
                for (int j = 0; j < count && !duplicate; ++j)
                    duplicate = out[j].weaponClass == offers[k].weaponClass;
                if (!duplicate)
                    out[count++] = offers[k];
            }
            return count;
        }

        void LayoutSlotPage(void* modeList, const Cursor& cursor)
        {
            const Loadout* const loadout = FindLoadout(cursor.unitClass);
            int position = kFirstPosition;
            for (int i = 0; i < P::kMaxSlots && position < kBackPosition; ++i)
            {
                const uint32_t stock = StockWeaponClass(cursor.unitClass, i);
                if (stock == 0)
                    continue;
                const SlotChoice* const choice = loadout ? &loadout->slots[i] : nullptr;
                const bool changed = choice && choice->odf[0] != '\0';
                const std::string stockName = WeaponName(stock);
                char label[P::kLabelChars];
                P::FormatSlotLabel(i, changed ? choice->name : stockName.c_str(), changed, label, sizeof(label));
                SetLabel(kStubSlot0 + i, label);
                SafeSetMode(modeList, position++, StubMode(kStubSlot0 + i), true);
            }
        }

        void LayoutWeaponPage(void* self, void* modeList, Cursor& cursor, uint32_t playerTeam)
        {
            Offer offers[kMaxOffers];
            const int offerCount = ComposeChoices(cursor.unitClass, cursor.slot, playerTeam, offers, kMaxOffers);
            const Loadout* const loadout = FindLoadout(cursor.unitClass);
            const SlotChoice* const choice = loadout ? &loadout->slots[cursor.slot] : nullptr;
            const bool locked = UnitLocked(cursor.unitClass, self);
            LogDecision("lock", locked ? "weapon choices greyed: unit is building" : "weapon choices editable");

            // Entry 0 is Stock, entry k+1 offer k.
            const P::PageLayout page = P::LayoutPage(offerCount + 1, cursor.offset);
            cursor.offset = page.first;
            int position = kFirstPosition;
            int choiceStub = 0;
            for (int e = page.first; e < page.first + page.count; ++e)
            {
                char label[P::kLabelChars];
                if (e == 0)
                {
                    const bool current = !choice || choice->odf[0] == '\0';
                    P::FormatChoiceLabel(ShimText("openshim_ui:unit_loadouts_stock", "Stock"), current, label, sizeof(label));
                    SetLabel(kStubStock, label);
                    SafeSetMode(modeList, position++, StubMode(kStubStock), !locked);
                    continue;
                }
                const Offer& offer = offers[e - 1];
                const std::string odf = WeaponOdf(offer.weaponClass);
                const bool current = choice && P::SameWeaponOdf(choice->odf, odf.c_str());
                P::FormatChoiceLabel(WeaponName(offer.weaponClass).c_str(), current, label, sizeof(label));
                g_ChoiceWeaponClass[choiceStub] = offer.weaponClass;
                g_ChoicePowerup[choiceStub] = offer.powerup;
                SetLabel(kStubChoice0 + choiceStub, label);
                SafeSetMode(modeList, position++, StubMode(kStubChoice0 + choiceStub), !locked);
                ++choiceStub;
            }
            for (int k = choiceStub; k < P::kPagePositions; ++k)
            {
                g_ChoiceWeaponClass[k] = 0;
                g_ChoicePowerup[k] = 0;
            }
            if (page.more)
            {
                SetLabel(kStubMore, ShimText("openshim_ui:unit_loadouts_more", "More"));
                SafeSetMode(modeList, position, StubMode(kStubMore), true);
            }
        }

        // Validates the producer's cursor; drops it (with a decision line)
        // when the page can no longer show.
        Cursor* LiveCursor(void* self, uint32_t& playerTeam)
        {
            const auto found = g_Cursors.find(self);
            if (found == g_Cursors.end())
                return nullptr;
            const char* why = nullptr;
            uint32_t state = 0;
            if (!g_Active.load(std::memory_order_acquire))
                why = "feature inactive";
            else if (!ReadPlayerTeam(playerTeam) || !IsLiveOwnProducer(self, playerTeam))
                why = "producer is not the player's live Recycler/Factory";
            else if (found->second.team != playerTeam)
                why = "team changed";
            else if (!ReadU32(reinterpret_cast<uintptr_t>(self) + kDeployStateOffset, state) || state != 2)
                why = "producer not deployed";
            else if (!EnsureStubs())
                why = "no button memory";
            if (!why)
                return &found->second;
            g_Cursors.erase(found);
            LogDecision("page", std::string("closed: ") + why);
            return nullptr;
        }

        void Refresh(void* self)
        {
            if (!SafeRefreshModeList(self))
                LogBudgeted(L"[LOADOUT] mode-list refresh faulted for producer 0x%08X\n",
                            static_cast<uint32_t>(reinterpret_cast<uintptr_t>(self)));
        }

        void Refuse(const std::string& unit, const char* why)
        {
            SafePlayRefuse();
            LogBudgeted(L"[LOADOUT] refused %hs: %hs\n", unit.c_str(), why);
        }

        // ---- install ----------------------------------------------------------------------

        bool ReadVtableSlot(uint32_t vtable, size_t index, uint32_t& out)
        {
            return vtable != 0 && ReadU32(vtable + index * sizeof(void*), out);
        }

        // The PRODMENU UpdateModeList and SetActiveMode hooks hold both
        // Recycler and Factory vtables ([ProducerBuildMenus] Enabled = 1).
        bool MenuHooksLive()
        {
            const uint32_t update = ProducerBuildMenuPatchTarget("Recycler UpdateModeList VTable Hook");
            const uint32_t pick = ProducerBuildMenuPatchTarget("Recycler SetActiveMode VTable Hook");
            uint32_t a = 0, b = 0, c = 0, d = 0;
            return update != 0 && pick != 0 && ReadVtableSlot(g_RecyclerVtable, kUpdateModeListVtableIndex, a) &&
                   a == update && ReadVtableSlot(g_FactoryVtable, kUpdateModeListVtableIndex, b) && b == update &&
                   ReadVtableSlot(g_RecyclerVtable, kSetActiveModeVtableIndex, c) && c == pick &&
                   ReadVtableSlot(g_FactoryVtable, kSetActiveModeVtableIndex, d) && d == pick &&
                   g_BzrFn_ProducerUpdateModeList != nullptr && g_BzrFn_ModeListSetMode != nullptr;
        }

        bool PartsReady()
        {
            return g_RowsBound && g_CostDetourInstalled && g_FinishBuildHooked && MenuHooksLive();
        }

        void MarkParts()
        {
            if (PartsReady() || !g_Enabled)
                ClearOptionHookFailed("UnitLoadouts");
            else if (g_RowsBound && !MenuHooksLive())
                MarkOptionHookFailed("UnitLoadouts", "Unavailable: needs [ProducerBuildMenus] Enabled = 1");
            else
                MarkOptionHookFailed("UnitLoadouts",
                                     "Unavailable: unit loadouts did not hook on this game build (see openshim.log).");
        }

        void BindRows()
        {
#if defined(_M_IX86)
            if (g_RowsBound)
                return;
            const HookEngine::EngineRow rows[] = {
                { "GameObjectHandleGetObj", &g_GetObjAddr },
                { "BuildScrapCost", &g_CostAddr },
                { "UnitLoadoutStartBuildCostCall", &g_StartBuildSiteAddr },
                { "UnitLoadoutRefundCostCall", &g_RefundSiteAddr },
                { "UnitLoadoutGiveWeapon", &g_GiveWeaponAddr },
                { "UnitLoadoutTeamAddScrap", &g_AddScrapAddr },
                { "InputHeldModifierKeys", &g_HeldModsAddr },
                { "RecyclerVtable", &g_RecyclerVtable },
                { "FactoryVtable", &g_FactoryVtable },
                { "ArmoryVtable", &g_ArmoryVtable },
            };
            const uint32_t sound = HookEngine::ResolveNamedAddress("PlayGlobalSound");
            if (g_GameObjectGetHandleAddr != 0 && HookEngine::BindEngineRows("Unit loadouts", rows))
            {
                g_RowsBound = true;
                g_FnGetObj = reinterpret_cast<FnGetObj>(g_GetObjAddr);
                g_FnGiveWeapon = reinterpret_cast<FnGiveWeapon>(g_GiveWeaponAddr);
                g_FnAddScrap = reinterpret_cast<FnAddScrap>(g_AddScrapAddr);
                g_FnPlaySound = sound != 0 ? reinterpret_cast<FnPlaySound>(sound) : nullptr;
                g_StartBuildReturn = g_StartBuildSiteAddr + kStartBuildCostReturnOffset;
                g_RefundReturn = g_RefundSiteAddr + kRefundCostReturnOffset;
                Log(L"[LOADOUT] rows bound (cost 0x%08X, charge return 0x%08X, refund return 0x%08X, give 0x%08X)\n",
                    g_CostAddr, g_StartBuildReturn, g_RefundReturn, g_GiveWeaponAddr);
            }
            else if (InterlockedDecrement(&g_InstallLogBudget) >= 0)
                Log(L"[LOADOUT] engine rows did not bind; unit loadouts inert\n");
#endif
        }

        // The cost detour and the FinishBuild hook go in only once the option
        // is wanted, so a game with it off never patches the cost function.
        void InstallHooksIfWanted()
        {
#if defined(_M_IX86)
            if (!g_Enabled)
                return;
            BindRows();
            if (!g_RowsBound)
                return;
            if (!g_CostDetourInstalled && !g_CostDetourFailed)
            {
                if (!ExpectedBytesMatchAt(g_CostAddr, kCostPrologue, sizeof(kCostPrologue)))
                {
                    g_CostDetourFailed = true;
                    Log(L"[LOADOUT] BuildScrapCost prologue differs at 0x%08X; cost detour not installed\n", g_CostAddr);
                }
                else if (InstallInlineDetour32(g_CostDetour, g_CostAddr, reinterpret_cast<void*>(&CostEntryThunk),
                                               sizeof(kCostPrologue), kCostPrologue, sizeof(kCostPrologue),
                                               reinterpret_cast<void* volatile*>(&g_OrigCost)))
                {
                    g_CostDetourInstalled = true;
                    Log(L"[LOADOUT] cost detour installed at 0x%08X\n", g_CostAddr);
                }
                else
                {
                    g_CostDetourFailed = true;
                    Log(L"[LOADOUT] cost detour install failed at 0x%08X\n", g_CostAddr);
                }
            }
            if (!g_FinishBuildHooked)
            {
                g_FinishBuildHooked = EnsureProducerFinishBuildHook();
                if (!g_FinishBuildHooked && InterlockedDecrement(&g_InstallLogBudget) >= 0)
                    Log(L"[LOADOUT] FinishBuild hook not installed yet\n");
            }
#endif
        }

        void ReadConfig()
        {
            bool value = false;
            g_Enabled = TryGetUserConfigBool("Gameplay", "UnitLoadouts", value) ? value : false;
            g_KillSwitch = EnvFlagEnabled("OPENSHIM_DISABLE_UNIT_LOADOUTS");
            if (g_KillSwitch && g_Enabled)
            {
                g_Enabled = false;
                Log(L"[LOADOUT] OPENSHIM_DISABLE_UNIT_LOADOUTS is set; unit loadouts stay off\n");
            }
            g_ConfigRead = true;
        }

        // FinishBuild: gives back the surcharge of weapons that were paid for
        // at StartBuild but not fitted, through Team::AddScrap on the
        // producer's team (the same call the stock refund makes).
        void CreditUnfitted(void* producer, const std::string& unit, bool quoteMatches, const Quote& quote,
                            const bool* fitted)
        {
            const int credit =
                P::UnfittedCredit(quoteMatches, quote.surcharge, quote.verdicts, quote.prices, fitted, P::kMaxSlots);
            if (credit <= 0)
                return;
            if (!IsSinglePlayerSession())
            {
                LogDecision("credit " + unit, "not credited (not single player)");
                return;
            }
            uint32_t team = 0;
            const bool read = ReadU32(reinterpret_cast<uintptr_t>(producer) + kProducerTeamOffset, team) && team != 0;
            const bool credited = read && SafeAddScrap(reinterpret_cast<void*>(static_cast<uintptr_t>(team)), credit);
            LogBudgeted(L"[LOADOUT] credit %hs at producer 0x%08X: %d scrap for unfitted weapons%hs\n", unit.c_str(),
                        static_cast<uint32_t>(reinterpret_cast<uintptr_t>(producer)), credit,
                        credited ? "" : (read ? " FAILED (add-scrap faulted)" : " FAILED (no producer team)"));
        }

        void ClearMission()
        {
            g_Loadouts.clear();
            g_Frozen.clear();
            g_Cursors.clear();
            g_LastDecision.clear();
            for (int k = 0; k < P::kPagePositions; ++k)
            {
                g_ChoiceWeaponClass[k] = 0;
                g_ChoicePowerup[k] = 0;
            }
        }
    }

    // ---- public -----------------------------------------------------------------------

    void ReloadUnitLoadoutsConfig()
    {
        ReadConfig();
        RefreshUnitLoadoutsState();
    }

    // Patch thread, retried from InstallAiTuningHooksIfPossible.
    void InstallUnitLoadoutsIfPossible()
    {
        static bool s_done = false;
        static int s_attempts = 0;
        if (s_done)
            return;
        if (!g_ConfigRead)
            ReadConfig();
        ++s_attempts;
        BindRows();
        InstallHooksIfWanted();
        MarkParts();
        if (!g_Enabled || PartsReady() || s_attempts >= kMaxInstallAttempts)
        {
            s_done = true;
            Log(L"[LOADOUT] install %hs after %d attempt(s): option %d, rows %d, cost detour %d, FinishBuild %d, menu hooks %d\n",
                PartsReady() ? "complete" : (g_Enabled ? "gave up" : "deferred (option off)"), s_attempts,
                g_Enabled ? 1 : 0, g_RowsBound ? 1 : 0, g_CostDetourInstalled ? 1 : 0, g_FinishBuildHooked ? 1 : 0,
                MenuHooksLive() ? 1 : 0);
        }
        RefreshUnitLoadoutsState();
    }

    // Config reload and the mission gate reconcile (game thread).
    void RefreshUnitLoadoutsState()
    {
        if (!g_ConfigRead)
            ReadConfig();
        InstallHooksIfWanted();
        const bool ready = PartsReady();
        static int s_marked = -1;
        const int mark = (ready ? 1 : 0) | (g_Enabled ? 2 : 0);
        if (s_marked != mark)
        {
            s_marked = mark;
            MarkParts();
        }
        const bool sp = IsSinglePlayerSession();
        const bool want = g_Enabled && ready && sp;
        const bool was = g_Active.exchange(want, std::memory_order_acq_rel);
        if (was != want)
        {
            Log(L"[LOADOUT] active=%d (option %d, hooks %d, single player %d)\n", want ? 1 : 0, g_Enabled ? 1 : 0,
                ready ? 1 : 0, sp ? 1 : 0);
            // Open pages close; loadouts and frozen quotes stay for the mission.
            if (!want)
                g_Cursors.clear();
        }
    }

    void ResetUnitLoadouts()
    {
        if (!g_Loadouts.empty() || !g_Frozen.empty())
            Log(L"[LOADOUT] mission reset: %u loadout(s), %u frozen quote(s) dropped (no save sidecar in M1)\n",
                static_cast<unsigned>(g_Loadouts.size()), static_cast<unsigned>(g_Frozen.size()));
        ClearMission();
        g_LogBudget = 200;
        RefreshUnitLoadoutsState();
    }

    bool UnitLoadoutsUpdateModeList(void* self)
    {
        if (g_Cursors.empty())
            return false;
        uint32_t playerTeam = 0;
        Cursor* const cursor = LiveCursor(self, playerTeam);
        if (!cursor)
            return false;
        if (!RunProducerUpdateModeListEmptyPage(self))
        {
            g_Cursors.erase(self);
            LogDecision("page", "closed: the stock mode list could not be run");
            return false;
        }
        void* const modeList = static_cast<uint8_t*>(self) + kModeListOffset;
        if (cursor->slot < 0)
            LayoutSlotPage(modeList, *cursor);
        else
            LayoutWeaponPage(self, modeList, *cursor, playerTeam);
        SafeSetMode(modeList, kBackPosition, kModeBack, true);
        return true;
    }

    bool UnitLoadoutsOnSetActiveMode(void* self, int mode)
    {
        const uint32_t value = static_cast<uint32_t>(mode);
        const int stub = StubIndexOf(value);
        const bool hasCursor = g_Cursors.find(self) != g_Cursors.end();
        if (stub < 0 && !hasCursor && value <= kModeLastNamed)
            return false;

        if (stub >= 0 || (hasCursor && value == static_cast<uint32_t>(kModeBack)))
        {
            uint32_t playerTeam = 0;
            Cursor* const cursor = LiveCursor(self, playerTeam);
            // A stale loadout button never reaches the stock build command.
            if (!cursor)
            {
                if (stub >= 0)
                    LogDecision("button", "swallowed: no open loadout page");
                return stub >= 0;
            }
            const std::string unit = UnitKey(cursor->unitClass);
            if (value == static_cast<uint32_t>(kModeBack))
            {
                if (cursor->slot >= 0)
                    cursor->slot = -1;
                else
                    g_Cursors.erase(self);
                Refresh(self);
                return true;
            }
            if (stub >= kStubSlot0 && stub < kStubSlot0 + P::kMaxSlots)
            {
                if (StockWeaponClass(cursor->unitClass, stub - kStubSlot0) == 0)
                    return true;
                cursor->slot = stub - kStubSlot0;
                cursor->offset = 0;
                Refresh(self);
                return true;
            }
            if (stub == kStubMore)
            {
                if (cursor->slot >= 0)
                {
                    Offer offers[kMaxOffers];
                    const int count = ComposeChoices(cursor->unitClass, cursor->slot, playerTeam, offers, kMaxOffers);
                    cursor->offset = P::LayoutPage(count + 1, cursor->offset).nextOffset;
                    Refresh(self);
                }
                return true;
            }
            // Stock or a weapon choice: an edit.
            if (cursor->slot < 0)
                return true;
            if (UnitLocked(cursor->unitClass, self))
            {
                Refuse(unit, "loadout is locked while this unit is building");
                return true;
            }
            const int slot = cursor->slot;
            if (stub == kStubStock)
            {
                Loadout& loadout = g_Loadouts[unit];
                loadout.slots[slot] = SlotChoice{};
                if (!HasChoices(loadout))
                    g_Loadouts.erase(unit);
                Log(L"[LOADOUT] %hs slot %d set to stock\n", unit.c_str(), slot + 1);
            }
            else
            {
                const int k = stub - kStubChoice0;
                const uint32_t weaponClass = k >= 0 && k < P::kPagePositions ? g_ChoiceWeaponClass[k] : 0;
                if (weaponClass == 0)
                    return true;
                const std::string odf = WeaponOdf(weaponClass);
                const std::string name = WeaponName(weaponClass);
                if (odf.empty())
                    return true;
                SlotChoice choice;
                strncpy_s(choice.odf, odf.c_str(), _TRUNCATE);
                strncpy_s(choice.name, name.c_str(), _TRUNCATE);
                g_Loadouts[unit].slots[slot] = choice;
                Log(L"[LOADOUT] %hs slot %d set to %hs (%hs)\n", unit.c_str(), slot + 1, choice.odf, choice.name);
            }
            cursor->slot = -1;
            cursor->offset = 0;
            Refresh(self);
            return true;
        }

        // Alt+pick on a unit opens its loadout.
        if (value <= kModeLastNamed || IsProducerMenuStubMode(value) || !AltHeld())
            return false;
        if (!g_Active.load(std::memory_order_acquire))
        {
            LogDecision("alt-pick", "passed to stock: feature inactive");
            return false;
        }
        uint32_t playerTeam = 0;
        if (!ReadPlayerTeam(playerTeam) || !IsLiveOwnProducer(self, playerTeam))
        {
            LogDecision("alt-pick", "passed to stock: not the player's live Recycler/Factory");
            return false;
        }
        uint32_t state = 0;
        if (!ReadU32(reinterpret_cast<uintptr_t>(self) + kDeployStateOffset, state) || state != 2)
        {
            LogDecision("alt-pick", "passed to stock: producer not deployed");
            return false;
        }
        const std::string unit = UnitKey(value);
        if (ConfigurableSlotCount(value) == 0)
        {
            Refuse(unit, "the unit has no weapon slots");
            return true;
        }
        if (!EnsureStubs())
        {
            LogDecision("alt-pick", "passed to stock: no button memory");
            return false;
        }
        Cursor cursor;
        cursor.unitClass = value;
        cursor.team = playerTeam;
        g_Cursors[self] = cursor;
        LogDecision("alt-pick", "opens loadout pages");
        Log(L"[LOADOUT] opened %hs at producer 0x%08X\n", unit.c_str(),
            static_cast<uint32_t>(reinterpret_cast<uintptr_t>(self)));
        Refresh(self);
        return true;
    }

    void UnitLoadoutsForgetProducer(void* self)
    {
        if (!g_Cursors.empty())
            g_Cursors.erase(self);
    }

    // Game thread, after the stock FinishBuild. Fits the weapons that were
    // charged at StartBuild (the frozen quote), slot by slot.
    void UnitLoadoutsOnUnitBuilt(void* producer, void* built)
    {
        if (!g_CostDetourInstalled || g_Frozen.empty() || !producer)
            return;
        const auto found = g_Frozen.find(producer);
        if (found == g_Frozen.end())
            return;
        const bool live = FrozenIsLive(*found);
        const Quote quote = found->second.quote;
        g_Frozen.erase(found);
        if (!live)
        {
            LogDecision("swap", "skipped: stale frozen quote (producer handle no longer matches)");
            return;
        }
        bool anyChosen = false;
        for (int i = 0; i < P::kMaxSlots; ++i)
            anyChosen = anyChosen || (quote.verdicts[i] == P::ChoiceVerdict::Chosen && quote.weaponClasses[i] != 0);
        if (!anyChosen)
            return;
        uint32_t builtClass = 0;
        const bool quoteMatches = built && ReadU32(reinterpret_cast<uintptr_t>(built) + kObjectClassOffset, builtClass) &&
                                  builtClass == quote.unitClass;
        const std::string unit = UnitKey(quote.unitClass);
        bool fitted[P::kMaxSlots] = {};
        if (!quoteMatches)
        {
            LogDecision("swap " + unit, built ? "skipped: built unit is another class" : "skipped: nothing was built");
            CreditUnfitted(producer, unit, false, quote, fitted);
            return;
        }
        uint32_t carrier = 0;
        uint32_t mask = 0;
        if (built)
        {
            ReadU32(reinterpret_cast<uintptr_t>(built) + kCarrierOffset, carrier);
            if (carrier)
                ReadU32(carrier + kCarrierMaskOffset, mask);
        }
        for (int i = 0; i < P::kMaxSlots; ++i)
        {
            const bool chosen = quote.verdicts[i] == P::ChoiceVerdict::Chosen && quote.weaponClasses[i] != 0;
            if (!chosen)
                continue;
            uint32_t weapon = 0;
            uint32_t current = 0;
            uint32_t hardpoint = 0;
            uint32_t hardpointType = 0;
            uint32_t weaponType = 0;
            const bool holdsStock = carrier != 0 && (mask & (1u << i)) != 0 &&
                                    ReadU32(carrier + kCarrierWeaponsOffset + i * 4, weapon) && weapon != 0 &&
                                    ReadU32(weapon + kWeaponToClassOffset, current) &&
                                    current == StockWeaponClass(quote.unitClass, i);
            const bool hardpointMatches = carrier != 0 && ReadU32(carrier + kCarrierHardpointsOffset + i * 4, hardpoint) &&
                                          hardpoint != 0 && ReadU32(hardpoint + kHardpointTypeOffset, hardpointType) &&
                                          ReadCategory(quote.weaponClasses[i], weaponType) && hardpointType == weaponType;
            const P::SwapVerdict verdict = P::PlanSwap(quoteMatches, chosen, i, holdsStock, hardpointMatches);
            if (verdict != P::SwapVerdict::Swap)
            {
                LogDecision("swap " + unit + " slot" + std::to_string(i + 1),
                            std::string("skipped: ") + P::SwapVerdictName(verdict));
                continue;
            }
            bool result = false;
            const bool called = SafeGiveWeapon(built, quote.weaponClasses[i], i, result);
            fitted[i] = called && result;
            LogDecision("swap " + unit + " slot" + std::to_string(i + 1),
                        called ? (result ? "fitted" : "give-weapon returned false") : "give-weapon faulted");
            LogBudgeted(L"[LOADOUT] built %hs: slot %d %hs%hs\n", unit.c_str(), i + 1,
                        WeaponOdf(quote.weaponClasses[i]).c_str(),
                        called ? (result ? " fitted" : " NOT fitted (returned false)") : " NOT fitted (faulted)");
        }
        CreditUnfitted(producer, unit, true, quote, fitted);
    }
}
