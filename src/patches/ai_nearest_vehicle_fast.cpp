#include "bzr_hooks_internal.h"
#include "hook_engine.h"
#include "nearest_vehicle_scan.h"
#include "patcher.h"
#include <Windows.h>
#include <cstdint>
#include <cstring>

// UnitTask::NearestVehicle (0x00463FC0) is the scan AttackTask::DoState runs
// on every call: 0.27 ms a frame at 80 craft. Most of that is call overhead in
// the stock build, not work: four out-of-line iterator calls per object, a
// cargo getter, and a Dist3D_Squared that copies two Vectors by value through
// a Vector subtract, both with stack-cookie frames.
//
// OPENSHIM_AI_FAST_NEAREST=1 replaces the function body with
// NearestVehicleScan::Scan (include/nearest_vehicle_scan.h): the same list,
// the same filters in the same order, the same virtual calls on the same
// objects, and the same float arithmetic, so it returns the same object. It
// keeps no state between calls, so it needs no claim about when objects move.
// Being exact, it runs in every session, network games included.
//
// OPENSHIM_AI_FAST_NEAREST=verify runs the fast scan, then the stock body
// through the trampoline, returns the stock answer and counts differences.
//
// It fails closed: the install checks the patches.json row and fingerprints
// the stock body and every helper it calls, and keeps stock on any mismatch.
// The lazy NearestVehicle (OPENSHIM_AI_LAZY_NEAREST) calls 0x00463FC0, so
// with both on, the scans it still runs go through this body.
namespace BZROpenShim::Hooks
{
    namespace
    {
        using FnNearestVehicle = void*(__cdecl*)(void* craft, const void* position);
        using FnVirtualGetter = const void*(__thiscall*)(void* self);

        enum class FastNearestMode
        {
            Off,
            Fast,
            Verify,
        };

        constexpr uint32_t kNearestVehicleAddr = 0x00463FC0u;
        constexpr size_t kDetourLen = 6;
        // push ebp; mov ebp,esp; sub esp,0x28
        const uint8_t kEntryBytes[kDetourLen] = { 0x55, 0x8B, 0xEC, 0x83, 0xEC, 0x28 };
        // mov eax,[objectList] at +0x1A; the operand is the list global.
        constexpr size_t kObjectListOperandOffset = 0x1B;
        constexpr ULONGLONG kReportIntervalMs = 5000;

        // FNV-1a 64 of each stock range the replacement stands in for (GOG,
        // read from the exe image). NearestVehicle reaches the rest through
        // rel32 calls, so a matching body also fixes their addresses.
        struct CodeFingerprint
        {
            uint32_t address;
            uint32_t length;
            uint64_t fnv;
        };
        const CodeFingerprint kFingerprints[] = {
            { 0x00463FC0u, 0x175u, 0xFB3A103397951F95ull }, // UnitTask::NearestVehicle
            { 0x0045BBC0u, 0x14u, 0x6A9B8C257D3F48EEull },  // GameObject::IsCargo: byte [this+0x9C]
            { 0x004620B0u, 0xA7u, 0xC0BA08DD71876DB6ull },  // Dist3D_Squared
            { 0x004401A0u, 0x62u, 0x98C419FEBF6594CEull },  // Vector operator-
            { 0x0041FBD0u, 0x22u, 0x1F86B87CD8CFA464ull },  // vector::begin: [this+0]
            { 0x0041FC30u, 0x23u, 0xCA2A30CE3DB24813ull },  // vector::end: [this+4]
            { 0x004230C0u, 0x20u, 0x5648A9D1981860E1ull },  // iterator ctor
            { 0x00423970u, 0x24u, 0x1D5519F56F2370BCull },  // iterator ctor body
            { 0x004178A0u, 0x0Du, 0x2E879628C8C77447ull },  // iterator container check (no-op)
            { 0x00421F00u, 0x35u, 0x01763DE2D3FF5513ull },  // iterator !=
            { 0x004237F0u, 0x3Au, 0xBA46C2478ECB17FBull },  // iterator ==
            { 0x00421EC0u, 0x13u, 0x995FD4B966DCA920ull },  // iterator *
            { 0x00416400u, 0x10u, 0xD6CE18308AA913FFull },  // iterator * body
            { 0x0046B260u, 0x2Au, 0xFBE3FA76612E9E4Aull },  // iterator post-++
            { 0x00421EE0u, 0x16u, 0x5DB9CC309C803703ull },  // iterator pre-++
            { 0x00421F70u, 0x1Bu, 0xA6E747A3D181DE24ull },  // iterator pre-++ body: +4
        };

        FastNearestMode g_Mode = FastNearestMode::Off;
        InlineDetour32 g_Detour = {};
        FnNearestVehicle g_StockNearest = nullptr;
        // GameObject::objectList, a std::vector<GameObject*>* (0x00917A74).
        void* const* g_ObjectListGlobal = nullptr;

        struct Counters
        {
            unsigned long calls;
            unsigned long mismatches;
        };
        Counters g_Counters = {};
        ULONGLONG g_WindowStartMs = 0;
        unsigned g_MismatchLines = 0;

        uint64_t Fnv1a64(const uint8_t* bytes, size_t length)
        {
            uint64_t hash = 0xCBF29CE484222325ull;
            for (size_t i = 0; i < length; ++i)
                hash = (hash ^ bytes[i]) * 0x100000001B3ull;
            return hash;
        }

        struct GameEngine
        {
            const uint8_t* list;

            void* const* Begin() const
            {
                void* const* slot;
                std::memcpy(&slot, list, sizeof(slot));
                return slot;
            }
            void* const* End() const
            {
                void* const* slot;
                std::memcpy(&slot, list + 4, sizeof(slot));
                return slot;
            }
            static bool IsCargo(void* obj)
            {
                return static_cast<const uint8_t*>(obj)[0x9C] != 0;
            }
            static const uint8_t* ClassOf(void* obj)
            {
                // (obj+0x18)->vtbl[0](), thiscall on the +0x18 sub-object.
                void* const self = static_cast<uint8_t*>(obj) + 0x18;
                const FnVirtualGetter* const vtbl = *static_cast<FnVirtualGetter* const*>(self);
                return static_cast<const uint8_t*>(vtbl[0](self));
            }
            static uint32_t ReadU32(const uint8_t* p)
            {
                uint32_t v;
                std::memcpy(&v, p, sizeof(v));
                return v;
            }
            static uint32_t ClassSig(void* obj) { return ReadU32(ClassOf(obj) + 0x14); }
            static uint32_t ClassLabel(void* obj) { return ReadU32(ClassOf(obj) + 0x1C); }
            static const NearestVehicleScan::Vec3* Position(void* obj)
            {
                void* const self = static_cast<uint8_t*>(obj) + 0x18;
                const FnVirtualGetter* const vtbl = *static_cast<FnVirtualGetter* const*>(self);
                return static_cast<const NearestVehicleScan::Vec3*>(vtbl[3](self));
            }
        };

        void* FastScan(void* craft, const void* position)
        {
            GameEngine engine = { static_cast<const uint8_t*>(*g_ObjectListGlobal) };
            return NearestVehicleScan::Scan(engine, craft,
                                            static_cast<const NearestVehicleScan::Vec3*>(position));
        }

        void MaybeReport()
        {
            const ULONGLONG now = GetTickCount64();
            if (!g_WindowStartMs)
                g_WindowStartMs = now;
            if (now - g_WindowStartMs < kReportIntervalMs)
                return;
            if (g_Mode == FastNearestMode::Verify)
                Log(L"[AINEAREST] verify window=%llums checks=%lu mismatches=%lu\n",
                    now - g_WindowStartMs, g_Counters.calls, g_Counters.mismatches);
            else
                Log(L"[AINEAREST] window=%llums calls=%lu\n", now - g_WindowStartMs, g_Counters.calls);
            g_Counters = {};
            g_WindowStartMs = now;
        }

        void* __cdecl FastNearestVehicle(void* craft, const void* position)
        {
            // Only the sim thread calls this (as with the lazy patch), so the
            // counters are plain globals. Read the clock every 256 calls.
            if ((++g_Counters.calls & 0xFFu) == 0)
                MaybeReport();
            void* const fast = FastScan(craft, position);
            if (g_Mode != FastNearestMode::Verify)
                return fast;
            void* const stock = g_StockNearest(craft, position);
            if (fast != stock)
            {
                ++g_Counters.mismatches;
                if (g_MismatchLines < 20)
                {
                    ++g_MismatchLines;
                    Log(L"[AINEAREST] mismatch craft=0x%08X fast=0x%08X stock=0x%08X\n",
                        static_cast<uint32_t>(reinterpret_cast<uintptr_t>(craft)),
                        static_cast<uint32_t>(reinterpret_cast<uintptr_t>(fast)),
                        static_cast<uint32_t>(reinterpret_cast<uintptr_t>(stock)));
                }
            }
            return stock;
        }

        FastNearestMode ReadMode()
        {
            char value[16] = {};
            const DWORD len = GetEnvironmentVariableA("OPENSHIM_AI_FAST_NEAREST", value, sizeof(value));
            if (len == 0 || len >= sizeof(value))
                return FastNearestMode::Off;
            if (_stricmp(value, "verify") == 0)
                return FastNearestMode::Verify;
            if (strcmp(value, "1") == 0 || _stricmp(value, "on") == 0 || _stricmp(value, "true") == 0)
                return FastNearestMode::Fast;
            return FastNearestMode::Off;
        }

        bool StockCodeMatches()
        {
            for (const CodeFingerprint& f : kFingerprints)
            {
                const uint8_t* const code = reinterpret_cast<const uint8_t*>(static_cast<uintptr_t>(f.address));
                if (IsBadReadPtr(code, f.length) || Fnv1a64(code, f.length) != f.fnv)
                {
                    Log(L"[AINEAREST] stock code at 0x%08X does not match; stock kept\n", f.address);
                    return false;
                }
            }
            return true;
        }
    }

    void InstallAiFastNearestIfRequested()
    {
        static bool s_done = false;
        if (s_done)
            return;
        s_done = true;
        g_Mode = ReadMode();
        if (g_Mode == FastNearestMode::Off)
            return;

        uint32_t nearest = 0;
        const HookEngine::EngineRow rows[] = {
            { "UnitTaskNearestVehicle", &nearest },
        };
        if (!HookEngine::BindEngineRows("AI fast NearestVehicle", rows))
            return;
        // The fingerprints are absolute GOG addresses, so the row must name
        // the same function.
        if (nearest != kNearestVehicleAddr || !StockCodeMatches())
        {
            Log(L"[AINEAREST] NearestVehicle row=0x%08X is not the fingerprinted build; stock kept\n", nearest);
            return;
        }
        uint32_t listGlobal = 0;
        std::memcpy(&listGlobal, reinterpret_cast<const void*>(static_cast<uintptr_t>(nearest + kObjectListOperandOffset)),
                    sizeof(listGlobal));
        g_ObjectListGlobal = reinterpret_cast<void* const*>(static_cast<uintptr_t>(listGlobal));

        if (!InstallInlineDetour32(g_Detour, nearest, reinterpret_cast<void*>(&FastNearestVehicle),
                                   kDetourLen, kEntryBytes, sizeof(kEntryBytes)))
        {
            Log(L"[AINEAREST] detour at 0x%08X failed; stock kept\n", nearest);
            return;
        }
        g_StockNearest = reinterpret_cast<FnNearestVehicle>(g_Detour.trampoline);
        Log(L"[AINEAREST] UnitTask::NearestVehicle: %hs (list global 0x%08X)\n",
            g_Mode == FastNearestMode::Verify ? "verify (fast and stock, stock answer kept)" : "fast",
            listGlobal);
    }
}
