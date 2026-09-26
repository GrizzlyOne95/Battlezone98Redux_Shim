// unit_vo.cpp
// BZR Open Shim - unit VO queue policy and its bridge accessors, split out
// of bzr_hooks.cpp. Installed and configured from there; shared helpers
// come from bzr_hooks_internal.h.
#include "bzr_hooks.h"
#include "bzr_hooks_internal.h"
#include "bzr_options_ui.h"
#include "hook_engine.h"
#include "patcher.h"
#include "shim_log.h"

#include <Windows.h>

#include <cstdint>
#include <cstdio>
#include <cstring>
#include <mutex>
#include <string>
#include <string_view>

namespace BZROpenShim
{
    namespace Hooks
    {
        // --- Unit VO queue policy ---------------------------------------------
        // This is the verified EXU Say -> QueueCB policy moved into OpenShim so
        // it also governs stock campaign and Instant Action. EXU can still layer
        // mission-specific overrides on top of these call sites.
        struct UnitVoQueueItem
        {
            char name[16];
            void* owner;
            void* sound;
            int priority;
            DWORD time;
            UnitVoQueueItem* next;
        };

        struct UnitVoQueueInspection
        {
            bool containsNonUnitVo = false;
            bool hasDuplicate = false;
            bool hasStale = false;
            size_t unitVoCount = 0;
        };

        struct UnitVoQueueDecision
        {
            bool drop = false;
            bool flushQueue = false;
        };

        using FnUnitVoQueue = int(__cdecl*)(const char* filename, void* owner, int priority);
        using FnUnitVoKillQueue = void(__cdecl*)(int);

        static constexpr bool kUnitVoFeedbackEnabledDefault = true;
        static constexpr uint32_t kUnitVoThrottleMsDefault = 0;
        static constexpr uint32_t kUnitVoQueueDepthDefault = 2;
        static constexpr uint32_t kUnitVoQueueStaleMsDefault = 2000;
        static constexpr uint32_t kUnitVoReducedThrottleMs = 2500;
        static constexpr uint32_t kUnitVoReducedQueueDepth = 1;
        static constexpr uint32_t kUnitVoReducedQueueStaleMs = 1500;
        static constexpr uint32_t kUnitVoThrottleMsMax = 60000;
        static constexpr uint32_t kUnitVoQueueDepthMax = 8;
        static constexpr uint32_t kUnitVoQueueStaleMsMax = 60000;

        static std::mutex g_UnitVoMutex;
        static DWORD g_UnitVoLastAttemptTick = 0;
        static bool g_UnitVoMuted = !kUnitVoFeedbackEnabledDefault;
        static uint32_t g_UnitVoThrottleMs = kUnitVoThrottleMsDefault;
        static uint32_t g_UnitVoQueueDepthLimit = kUnitVoQueueDepthDefault;
        static uint32_t g_UnitVoQueueStaleMs = kUnitVoQueueStaleMsDefault;
        bool g_UnitVoConfigInitialized = false;
        static bool g_UnitVoBaselineFeedbackEnabled = kUnitVoFeedbackEnabledDefault;
        static uint32_t g_UnitVoBaselineThrottleMs = kUnitVoThrottleMsDefault;
        static uint32_t g_UnitVoBaselineQueueDepth = kUnitVoQueueDepthDefault;
        static uint32_t g_UnitVoBaselineQueueStaleMs = kUnitVoQueueStaleMsDefault;
        static bool g_UnitVoHooksInstalled = false;
        static bool g_UnitVoHookFailureLogged = false;
        static uintptr_t g_UnitVoSayQueueCallSite = 0;
        static uintptr_t g_UnitVoRecycleQueueCallSite = 0;
        static uintptr_t g_UnitVoQueueListStorageAddress = 0;
        static FnUnitVoQueue g_BzrFn_UnitVoQueue = nullptr;
        static FnUnitVoKillQueue g_BzrFn_UnitVoKillQueue = nullptr;


        static bool UnitVoEndsWith(std::string_view value, std::string_view suffix)
        {
            return value.size() >= suffix.size() &&
                   value.substr(value.size() - suffix.size()) == suffix;
        }

        static std::string NormalizeUnitVoFilename(const char* filename)
        {
            std::string normalized;
            if (!filename)
                return normalized;
            normalized.reserve(std::strlen(filename));
            for (const unsigned char c : std::string_view(filename))
                normalized.push_back(static_cast<char>(std::tolower(c)));
            return normalized;
        }

        static bool IsLikelyUnitVoFilename(std::string_view filename)
        {
            if (!UnitVoEndsWith(filename, ".wav"))
                return false;

            const std::string_view stem = filename.substr(0, filename.size() - 4);
            if (stem.size() < 5 || stem.size() > 12)
                return false;
            for (const unsigned char c : stem)
            {
                if (!std::isalnum(c))
                    return false;
            }

            const size_t voiceMarker = stem.rfind('v');
            if (voiceMarker == std::string_view::npos || voiceMarker < 2)
                return false;
            const size_t suffixLength = stem.size() - voiceMarker - 1;
            return suffixLength >= 1 && suffixLength <= 2;
        }

        static UnitVoQueueItem* GetUnitVoQueueHead()
        {
            if (!g_UnitVoQueueListStorageAddress)
                return nullptr;
            return *reinterpret_cast<UnitVoQueueItem**>(g_UnitVoQueueListStorageAddress);
        }

        static UnitVoQueueInspection InspectUnitVoQueueLocked(
            DWORD now,
            std::string_view duplicateCandidate)
        {
            UnitVoQueueInspection inspection;
            for (UnitVoQueueItem* item = GetUnitVoQueueHead(); item; item = item->next)
            {
                const std::string queuedName = NormalizeUnitVoFilename(item->name);
                if (!IsLikelyUnitVoFilename(queuedName))
                {
                    inspection.containsNonUnitVo = true;
                    continue;
                }

                ++inspection.unitVoCount;
                if (queuedName == duplicateCandidate)
                    inspection.hasDuplicate = true;
                if (g_UnitVoQueueStaleMs > 0 && now - item->time >= g_UnitVoQueueStaleMs)
                    inspection.hasStale = true;
            }
            return inspection;
        }

        static UnitVoQueueDecision PrepareUnitVoQueueDecision(const char* filename)
        {
            UnitVoQueueDecision decision;
            if (!filename)
                return decision;

            const std::string normalized = NormalizeUnitVoFilename(filename);
            if (!IsLikelyUnitVoFilename(normalized))
                return decision;

            const DWORD now = GetTickCount();
            std::lock_guard<std::mutex> lock(g_UnitVoMutex);
            if (g_UnitVoMuted)
            {
                decision.drop = true;
                return decision;
            }

            if (g_UnitVoThrottleMs > 0 && g_UnitVoLastAttemptTick != 0 &&
                now - g_UnitVoLastAttemptTick < g_UnitVoThrottleMs)
            {
                g_UnitVoLastAttemptTick = now;
                decision.drop = true;
                return decision;
            }
            g_UnitVoLastAttemptTick = now;

            const UnitVoQueueInspection inspection =
                InspectUnitVoQueueLocked(now, normalized);
            if (inspection.hasDuplicate)
            {
                decision.drop = true;
                return decision;
            }

            const bool depthExceeded =
                g_UnitVoQueueDepthLimit > 0 &&
                inspection.unitVoCount >= g_UnitVoQueueDepthLimit;
            if (inspection.hasStale || depthExceeded)
            {
                if (!inspection.containsNonUnitVo && g_BzrFn_UnitVoKillQueue)
                    decision.flushQueue = true;
                else
                    decision.drop = true;
            }
            return decision;
        }

        static bool ShouldTraceUnitVo()
        {
            static const bool enabled = EnvFlagEnabled("OPENSHIM_TRACE_UNIT_VO");
            return enabled;
        }

        static int __cdecl UnitVoQueueIntercept(const char* filename, void* owner, int priority)
        {
            if (!g_BzrFn_UnitVoQueue)
                return 0;

            const UnitVoQueueDecision decision = PrepareUnitVoQueueDecision(filename);
            if (ShouldTraceUnitVo())
            {
                Log(L"[UNITVO] filename=%hs owner=0x%08X priority=%d action=%hs\n",
                    filename ? filename : "<null>",
                    static_cast<uint32_t>(reinterpret_cast<uintptr_t>(owner)),
                    priority,
                    decision.drop ? "drop" : (decision.flushQueue ? "flush+queue" : "queue"));
            }
            if (decision.drop)
                return 0;
            if (decision.flushQueue && g_BzrFn_UnitVoKillQueue)
                g_BzrFn_UnitVoKillQueue(0);
            return g_BzrFn_UnitVoQueue(filename, owner, priority);
        }

        static uintptr_t ResolveUnitVoQueueListStorage(uintptr_t queueAddress)
        {
            const auto* queue = reinterpret_cast<const uint8_t*>(queueAddress);
            if (!queue)
                return 0;
            constexpr size_t kScanWindow = 0x30;
            for (size_t offset = 0; offset + 7 <= kScanWindow; ++offset)
            {
                if (queue[offset] != 0x83 || queue[offset + 1] != 0x3D ||
                    queue[offset + 6] != 0x00)
                    continue;
                uint32_t noMoreCbAddress = 0;
                std::memcpy(&noMoreCbAddress, queue + offset + 2, sizeof(noMoreCbAddress));
                return static_cast<uintptr_t>(noMoreCbAddress) - sizeof(uint32_t);
            }
            return 0;
        }

        static bool LooksLikeUnitVoKillQueue(uintptr_t target, uintptr_t queueListAddress)
        {
            if (!target || !queueListAddress)
                return false;
            const auto* bytes = reinterpret_cast<const uint8_t*>(target);
            if (bytes[0] != 0x55 || bytes[1] != 0x8B || bytes[2] != 0xEC ||
                bytes[3] != 0x51 || bytes[4] != 0xA1)
                return false;
            uint32_t headAddress = 0;
            std::memcpy(&headAddress, bytes + 5, sizeof(headAddress));
            return headAddress == queueListAddress;
        }

        static FnUnitVoKillQueue ResolveUnitVoKillQueue(
            uintptr_t queueAddress,
            uintptr_t queueListAddress)
        {
            if (!queueAddress || !queueListAddress)
                return nullptr;
            const auto* queue = reinterpret_cast<const uint8_t*>(queueAddress);
            constexpr size_t kScanWindow = 0x180;
            for (size_t offset = 0; offset + 7 <= kScanWindow; ++offset)
            {
                if (queue[offset] != 0x6A || queue[offset + 1] != 0x00 ||
                    queue[offset + 2] != 0xE8)
                    continue;
                int32_t displacement = 0;
                std::memcpy(&displacement, queue + offset + 3, sizeof(displacement));
                const uintptr_t callSite = queueAddress + offset + 2;
                const uintptr_t target = callSite + 5 + static_cast<intptr_t>(displacement);
                if (LooksLikeUnitVoKillQueue(target, queueListAddress))
                    return reinterpret_cast<FnUnitVoKillQueue>(target);
            }
            return nullptr;
        }

        static bool WriteUnitVoQueueCall(uintptr_t callSite)
        {
            uint8_t patch[5] = { 0xE8, 0, 0, 0, 0 };
            const int32_t relative =
                static_cast<int32_t>(reinterpret_cast<uintptr_t>(UnitVoQueueIntercept)) -
                static_cast<int32_t>(callSite + 5);
            std::memcpy(patch + 1, &relative, sizeof(relative));
            return WritePatchBytes(callSite, patch, sizeof(patch));
        }

        void InstallUnitVoQueueHooksIfPossible()
        {
            if (g_UnitVoHooksInstalled)
                return;

            // Both call sites come from the "resolves" array in
            // scripts/patches.json, which anchors each entry on the CALL
            // itself. The signature only nominates them; identity is settled
            // below, where the two must resolve to one QueueCB that then
            // passes the queue-list layout probe.
            const uint32_t sayCallSite =
                HookEngine::ResolveNamedAddress("UnitVo::SayQueueCallSite");
            const uint32_t recycleCallSite =
                HookEngine::ResolveNamedAddress("UnitVo::RecycleQueueCallSite");
            if (sayCallSite == 0 || recycleCallSite == 0)
            {
                if (!g_UnitVoHookFailureLogged)
                {
                    g_UnitVoHookFailureLogged = true;
                    Log(L"[UNITVO] Say -> QueueCB signatures not ready; deferring hooks\n");
                }
                return;
            }

            g_UnitVoSayQueueCallSite = static_cast<uintptr_t>(sayCallSite);
            g_UnitVoRecycleQueueCallSite = static_cast<uintptr_t>(recycleCallSite);
            const uintptr_t sayTarget = ResolveRel32Target(
                reinterpret_cast<uint8_t*>(g_UnitVoSayQueueCallSite));
            const uintptr_t recycleTarget = ResolveRel32Target(
                reinterpret_cast<uint8_t*>(g_UnitVoRecycleQueueCallSite));
            if (!sayTarget || sayTarget != recycleTarget)
            {
                Log(L"[UNITVO] QueueCB targets missing or inconsistent; hooks disabled\n");
                return;
            }

            g_BzrFn_UnitVoQueue = reinterpret_cast<FnUnitVoQueue>(sayTarget);
            g_UnitVoQueueListStorageAddress = ResolveUnitVoQueueListStorage(sayTarget);
            g_BzrFn_UnitVoKillQueue = ResolveUnitVoKillQueue(
                sayTarget,
                g_UnitVoQueueListStorageAddress);
            if (!g_UnitVoQueueListStorageAddress || !g_BzrFn_UnitVoKillQueue)
            {
                Log(L"[UNITVO] QueueCB layout validation failed; hooks disabled\n");
                g_BzrFn_UnitVoQueue = nullptr;
                return;
            }

            if (!WriteUnitVoQueueCall(g_UnitVoSayQueueCallSite) ||
                !WriteUnitVoQueueCall(g_UnitVoRecycleQueueCallSite))
            {
                Log(L"[UNITVO] Failed patching Say -> QueueCB call sites\n");
                return;
            }

            g_UnitVoHooksInstalled = true;
            g_UnitVoHookFailureLogged = false;
            Log(L"[UNITVO] Installed global queue policy say=0x%08X recycle=0x%08X queue=0x%08X list=0x%08X kill=0x%08X\n",
                static_cast<uint32_t>(g_UnitVoSayQueueCallSite),
                static_cast<uint32_t>(g_UnitVoRecycleQueueCallSite),
                static_cast<uint32_t>(sayTarget),
                static_cast<uint32_t>(g_UnitVoQueueListStorageAddress),
                static_cast<uint32_t>(reinterpret_cast<uintptr_t>(g_BzrFn_UnitVoKillQueue)));
        }

        void InitializeUnitVoConfig()
        {
            if (g_UnitVoConfigInitialized)
                return;
            g_UnitVoConfigInitialized = true;

            bool feedbackEnabled = kUnitVoFeedbackEnabledDefault;
            uint32_t throttleMs = kUnitVoThrottleMsDefault;
            uint32_t queueDepth = kUnitVoQueueDepthDefault;
            uint32_t queueStaleMs = kUnitVoQueueStaleMsDefault;

            std::string configuredMode;
            if (TryGetUserConfigString(kUserConfigDisplaySection, "UnitVoFeedback", configuredMode))
            {
                std::string normalized;
                normalized.reserve(configuredMode.size());
                for (char ch : configuredMode)
                {
                    if (ch == ' ' || ch == '\t' || ch == '_' || ch == '-')
                        continue;
                    normalized.push_back(static_cast<char>(std::tolower(static_cast<unsigned char>(ch))));
                }

                if (normalized == "reduced" || normalized == "minimal")
                {
                    feedbackEnabled = true;
                    throttleMs = kUnitVoReducedThrottleMs;
                    queueDepth = kUnitVoReducedQueueDepth;
                    queueStaleMs = kUnitVoReducedQueueStaleMs;
                }
                else if (normalized == "none" || normalized == "off" || normalized == "0" ||
                         normalized == "false" || normalized == "no" || normalized == "disabled")
                {
                    feedbackEnabled = false;
                }
                else if (normalized == "normal" || normalized == "on" || normalized == "1" ||
                         normalized == "true" || normalized == "yes" || normalized == "enabled")
                {
                    feedbackEnabled = true;
                }
            }

            std::lock_guard<std::mutex> lock(g_UnitVoMutex);
            g_UnitVoBaselineFeedbackEnabled = feedbackEnabled;
            g_UnitVoBaselineThrottleMs = throttleMs;
            g_UnitVoBaselineQueueDepth = queueDepth;
            g_UnitVoBaselineQueueStaleMs = queueStaleMs;
            g_UnitVoMuted = !feedbackEnabled;
            g_UnitVoThrottleMs = throttleMs;
            g_UnitVoQueueDepthLimit = queueDepth;
            g_UnitVoQueueStaleMs = queueStaleMs;
            g_UnitVoLastAttemptTick = 0;
            Log(L"[UNITVO] Feedback baseline=%hs depth=%u stale=%ums throttle=%ums\n",
                feedbackEnabled ? "enabled" : "disabled",
                g_UnitVoQueueDepthLimit,
                g_UnitVoQueueStaleMs,
                g_UnitVoThrottleMs);
        }

        void RevertUnitVoToBaseline()
        {
            InitializeUnitVoConfig();
            std::lock_guard<std::mutex> lock(g_UnitVoMutex);
            g_UnitVoMuted = !g_UnitVoBaselineFeedbackEnabled;
            g_UnitVoThrottleMs = g_UnitVoBaselineThrottleMs;
            g_UnitVoQueueDepthLimit = g_UnitVoBaselineQueueDepth;
            g_UnitVoQueueStaleMs = g_UnitVoBaselineQueueStaleMs;
            g_UnitVoLastAttemptTick = 0;
        }
    }

    using namespace Hooks;

    uint32_t GetUnitVoThrottleFromBridge()
    {
        std::lock_guard<std::mutex> lock(g_UnitVoMutex);
        return g_UnitVoThrottleMs;
    }

    bool SetUnitVoThrottleFromBridge(uint32_t milliseconds)
    {
        if (milliseconds > kUnitVoThrottleMsMax)
            return false;
        std::lock_guard<std::mutex> lock(g_UnitVoMutex);
        g_UnitVoThrottleMs = milliseconds;
        g_UnitVoLastAttemptTick = 0;
        return true;
    }

    uint32_t GetUnitVoQueueDepthFromBridge()
    {
        std::lock_guard<std::mutex> lock(g_UnitVoMutex);
        return g_UnitVoQueueDepthLimit;
    }

    bool SetUnitVoQueueDepthFromBridge(uint32_t depth)
    {
        if (depth > kUnitVoQueueDepthMax)
            return false;
        std::lock_guard<std::mutex> lock(g_UnitVoMutex);
        g_UnitVoQueueDepthLimit = depth;
        return true;
    }

    uint32_t GetUnitVoQueueStaleMsFromBridge()
    {
        std::lock_guard<std::mutex> lock(g_UnitVoMutex);
        return g_UnitVoQueueStaleMs;
    }

    bool SetUnitVoQueueStaleMsFromBridge(uint32_t milliseconds)
    {
        if (milliseconds > kUnitVoQueueStaleMsMax)
            return false;
        std::lock_guard<std::mutex> lock(g_UnitVoMutex);
        g_UnitVoQueueStaleMs = milliseconds;
        return true;
    }

    bool GetUnitVoMutedFromBridge()
    {
        std::lock_guard<std::mutex> lock(g_UnitVoMutex);
        return g_UnitVoMuted;
    }

    bool SetUnitVoMutedFromBridge(bool muted)
    {
        std::lock_guard<std::mutex> lock(g_UnitVoMutex);
        g_UnitVoMuted = muted;
        g_UnitVoLastAttemptTick = 0;
        Log(L"[MISSIONHOOK] unit VO feedback %hs\n", muted ? "disabled" : "enabled");
        return true;
    }
}
