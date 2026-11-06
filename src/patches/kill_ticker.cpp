// kill_ticker.cpp
// BZR Open Shim - kill ticker ("-Tank" above the weapon list)
//
// Copyright (C) 2026 BZR Open Shim contributors
// SPDX-License-Identifier: MIT
//
// Detection: hud_feedback.cpp's four DamageAlloc wrappers hand every relevant
// damage application here with the victim's health ratio before and after
// the original call. A line is queued only when the local player's own hit
// took a live victim below zero (KillTicker::ConfirmsKill). In network games
// a victim this peer does not simulate is credited through the stricter
// RemoteCandidates rule in kill_ticker_policy.h.
//
// Naming: [GameObjectClass] unitName from the victim's ODF, read through the
// engine's own file read (the PathBlock::ReadFile resolve), so addon and
// packed ODFs resolve exactly as the game loaded them. The ODF name is the
// fallback. Names are cached per mission and only read on the frame thread,
// never inside a damage wrapper.
//
// Drawing: the shared gauge-draw overlay (hud_gauge_overlay.cpp), right
// aligned above the stock weapon-list backdrop when the contextual HUD's
// observer saw it this frame, else at a fixed lower-right fallback.

#include "kill_ticker.h"
#include "bzr_hooks_internal.h"
#include "bzr_object_layout.h"
#include "contextual_hud.h"
#include "hook_engine.h"
#include "hud_gauge_overlay.h"
#include "shim_log.h"

#include <Windows.h>

#include <atomic>
#include <cstdint>
#include <cstring>
#include <iterator>
#include <string>
#include <unordered_map>
#include <vector>

namespace BZROpenShim::KillTicker
{
    namespace
    {
        using ReadFileFn = int(__cdecl*)(const char* name, int* size, void* buffer, int capacity);

        // Warm amber text on the autosave notice's translucent black backing.
        constexpr uint32_t kTextColor = 0xFFFFD27Au;
        constexpr uint32_t kPanelColor = 0x8C000000u;
        // The weapon list draws every HUD frame; older than this means the
        // stock panel is not up and the fallback position is used.
        constexpr uint64_t kAnchorMaxAgeMs = 500;
        constexpr size_t kPendingCapacity = 16;
        constexpr int kOdfReadCapacity = 64 * 1024;
        constexpr int kOdfReadMax = 1024 * 1024;
        constexpr size_t kNameCacheMax = 256;
        // complete+0x200, the float GameObject::Save writes as "healthRatio"
        // and the four damage handlers test (see career_stats.cpp).
        constexpr size_t kHealthRatioOffset = 0x200;

        SRWLOCK g_lock = SRWLOCK_INIT;
        std::atomic<bool> g_enabled{false};
        Feed g_feed;                                            // g_lock
        RemoteCandidates g_remote;                              // g_lock
        ConfirmedKill g_pending[kPendingCapacity] = {};         // g_lock
        size_t g_pendingCount = 0;                              // g_lock
        std::unordered_map<std::string, std::string> g_names;  // g_lock
        ReadFileFn g_readFile = nullptr; // frame thread
        int g_readState = 0;             // 0 unresolved, 1 ready, -1 unavailable
        bool g_anchorLogged = false;
        LONG g_logBudget = 16;

        Probe ProbeVictim(int handle) noexcept
        {
            __try
            {
                void* object = GameObjectFromHandleGog(handle);
                if (!object)
                    return Probe::Gone;
                // Health only: the object-state 0x200 bit is also set by
                // plain removals (RemoteDelete), so it cannot prove a kill.
                const float health = *reinterpret_cast<const float*>(
                    static_cast<const uint8_t*>(object) + kHealthRatioOffset);
                return health < 0.0f ? Probe::Dead : Probe::Alive;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return Probe::Gone;
            }
        }

        bool SafeReadFile(const char* name, int& size, void* buffer, int capacity) noexcept
        {
            __try
            {
                return g_readFile(name, &size, buffer, capacity) != 0;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        // Same two-attempt contract as path_block.cpp's ReadGameFile: a loose
        // file reports its size before failing on a short buffer; a packed
        // record fails without one.
        bool ReadOdfText(const std::string& file, std::string& out)
        {
            out.clear();
            if (g_readState == 0)
            {
                g_readFile = reinterpret_cast<ReadFileFn>(
                    static_cast<uintptr_t>(HookEngine::ResolveNamedAddress("PathBlock::ReadFile")));
                g_readState = g_readFile ? 1 : -1;
                if (!g_readFile)
                    LogShimA(LogLevel::Info, "killticker", "engine file read unresolved; lines use ODF names");
            }
            if (g_readState < 0)
                return false;
            std::vector<char> buffer(static_cast<size_t>(kOdfReadCapacity));
            for (int attempt = 0; attempt < 2; ++attempt)
            {
                int size = 0;
                if (SafeReadFile(file.c_str(), size, buffer.data(), static_cast<int>(buffer.size())) &&
                    size > 0 && static_cast<size_t>(size) <= buffer.size())
                {
                    out.assign(buffer.data(), static_cast<size_t>(size));
                    return true;
                }
                const int retry = size > static_cast<int>(buffer.size()) ? size : 0;
                if (attempt > 0 || retry <= 0 || retry > kOdfReadMax)
                    break;
                buffer.resize(static_cast<size_t>(retry));
            }
            return false;
        }

        std::string ResolveName(const char* odf)
        {
            std::string key;
            for (size_t i = 0; odf && i < kOdfChars && odf[i]; ++i)
            {
                char c = odf[i];
                if (c >= 'A' && c <= 'Z') c = static_cast<char>(c - 'A' + 'a');
                key.push_back(c);
            }
            if (key.empty())
                return "Unit";

            AcquireSRWLockShared(&g_lock);
            const auto found = g_names.find(key);
            const bool cached = found != g_names.end();
            std::string name = cached ? found->second : std::string();
            ReleaseSRWLockShared(&g_lock);
            if (cached)
                return name;

            std::string text, unitName;
            if (ReadOdfText(key + ".odf", text))
                unitName = ParseUnitName(text);
            name = DisplayName(unitName, odf);
            if (name.empty())
                name = "Unit";

            AcquireSRWLockExclusive(&g_lock);
            if (g_names.size() >= kNameCacheMax)
                g_names.clear();
            g_names.emplace(key, name);
            ReleaseSRWLockExclusive(&g_lock);
            return name;
        }

        bool Measure(const HudGaugeOverlay::Frame& frame, const char* text, float& w, float& h) noexcept
        {
            __try
            {
                frame.measure(frame.style, text, &w, &h);
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        // Gauge-draw overlay painter, frame thread, inside the HUD pass.
        bool Paint(const HudGaugeOverlay::Frame& frame) noexcept
        {
            if (!g_enabled.load(std::memory_order_relaxed))
                return true;
            const uint64_t now = GetTickCount64();
            Line lines[kMaxLines];
            size_t count = 0;
            AcquireSRWLockExclusive(&g_lock);
            g_feed.Expire(now);
            g_feed.MarkShown(now);
            count = g_feed.Count();
            for (size_t i = 0; i < count; ++i)
                lines[i] = g_feed.At(i);
            ReleaseSRWLockExclusive(&g_lock);
            if (!count)
                return true;

            Anchor anchor;
            anchor.valid = ContextualHud::WeaponListRect(kAnchorMaxAgeMs, anchor.x, anchor.y, anchor.w, anchor.h);
            // Newest line sits directly above the weapon list; older lines stack upward.
            for (size_t fromBottom = 0; fromBottom < count; ++fromBottom)
            {
                const Line& line = lines[count - 1 - fromBottom];
                char text[kNameChars + 16] = {};
                FormatLine(line, text, sizeof(text));
                float textW = 0.0f, textH = 0.0f;
                if (!Measure(frame, text, textW, textH))
                    return false;
                LineRect rect;
                if (!ComputeLine(frame.viewW, frame.viewH, anchor, textW, textH, fromBottom, rect))
                    break;
                const float opacity = Feed::Opacity(line, now);
                if (!HudGaugeOverlay::DrawPanelText(frame, rect.x1, rect.y1, rect.x2, rect.y2,
                                                    WithOpacity(kPanelColor, opacity),
                                                    rect.textLeft, rect.textTop, text,
                                                    WithOpacity(kTextColor, opacity), 0))
                    return false;
            }
            return true;
        }
    }

    bool Enabled() noexcept
    {
        return g_enabled.load(std::memory_order_relaxed);
    }

    bool Configure(bool enabled)
    {
        if (!enabled)
        {
            if (g_enabled.exchange(false, std::memory_order_relaxed))
                LogShimA(LogLevel::Info, "killticker", "kill ticker disabled");
            HudGaugeOverlay::SetPainter(HudGaugeOverlay::Slot::KillTicker, nullptr);
            ResetMission();
            return true;
        }
        const bool overlay = HudGaugeOverlay::Ensure();
        if (overlay)
            HudGaugeOverlay::SetPainter(HudGaugeOverlay::Slot::KillTicker, &Paint);
        // Optional: without the weapon-list rectangle the feed uses its
        // fixed lower-right position.
        if (!ContextualHud::InstallWeaponListAnchor() && !g_anchorLogged)
        {
            g_anchorLogged = true;
            LogShimA(LogLevel::Info, "killticker", "weapon-list anchor unavailable; using the fixed lower-right position");
        }
        if (!g_enabled.exchange(overlay, std::memory_order_relaxed) && overlay)
            LogShimA(LogLevel::Info, "killticker", "kill ticker enabled");
        return overlay;
    }

    void NoteDamage(const KillSample& sample, const char* odf, bool singlePlayer) noexcept
    {
        if (!g_enabled.load(std::memory_order_relaxed))
            return;
        if (ConfirmsKill(sample))
        {
            AcquireSRWLockExclusive(&g_lock);
            if (g_pendingCount < kPendingCapacity)
            {
                ConfirmedKill& kill = g_pending[g_pendingCount++];
                kill.victim = sample.victim;
                CopyOdf(kill.odf, odf);
            }
            g_remote.Forget(sample.victim);
            ReleaseSRWLockExclusive(&g_lock);
            return;
        }
        // Single player simulates every victim locally; the exact rule above
        // is the only one that may credit a kill there.
        if (singlePlayer)
            return;
        const uint64_t now = GetTickCount64();
        AcquireSRWLockExclusive(&g_lock);
        g_remote.NoteDamage(sample, odf, now);
        ReleaseSRWLockExclusive(&g_lock);
    }

    void Tick()
    {
        if (!g_enabled.load(std::memory_order_relaxed))
            return;
        const uint64_t now = GetTickCount64();
        const bool singlePlayer = Hooks::IsSinglePlayerSession();

        ConfirmedKill kills[kPendingCapacity + kRemoteCapacity];
        size_t exact = 0, total = 0;
        AcquireSRWLockExclusive(&g_lock);
        for (size_t i = 0; i < g_pendingCount; ++i)
            kills[total++] = g_pending[i];
        exact = total;
        g_pendingCount = 0;
        if (singlePlayer)
            g_remote.Reset();
        else
            total += g_remote.Resolve(now, [](int victim) { return ProbeVictim(victim); },
                                      kills + total, std::size(kills) - total);
        ReleaseSRWLockExclusive(&g_lock);

        for (size_t i = 0; i < total; ++i)
        {
            const std::string name = ResolveName(kills[i].odf);
            AcquireSRWLockExclusive(&g_lock);
            g_feed.Push(name, now);
            ReleaseSRWLockExclusive(&g_lock);
            if (InterlockedDecrement(&g_logBudget) >= 0)
                LogShimA(LogLevel::Info, "killticker", "verified kill victim=%d odf=%s name=%s path=%s",
                         kills[i].victim, kills[i].odf, name.c_str(), i < exact ? "exact" : "network");
        }

        AcquireSRWLockExclusive(&g_lock);
        g_feed.Expire(now);
        ReleaseSRWLockExclusive(&g_lock);
    }

    void ResetMission() noexcept
    {
        AcquireSRWLockExclusive(&g_lock);
        g_feed.Reset();
        g_remote.Reset();
        g_pendingCount = 0;
        g_names.clear();
        ReleaseSRWLockExclusive(&g_lock);
        InterlockedExchange(&g_logBudget, 16);
    }
}
