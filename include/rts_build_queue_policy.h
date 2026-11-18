// rts_build_queue_policy.h
// Pure decision rules for [Gameplay] RtsBuildQueue (src/patches/rts_build_queue.cpp,
// Docs/RTS_BUILD_QUEUE.md). No Windows or engine access, so the tests can
// include it: the queue storage and its caps, what a build pick does, the
// busy and can-afford decisions, and the badge text.
#pragma once

#include <cstddef>
#include <cstdint>
#include <cstring>

namespace BZROpenShim
{
    namespace RtsBuildQueuePolicy
    {
        // ---- Caps and timing ---------------------------------------------------
        constexpr int kMaxEntries = 10;            // queued items per producer
        constexpr int kMaxProducers = 16;          // producers with a queue at once
        constexpr uint64_t kDrainIntervalMs = 250; // 4 Hz drain
        constexpr uint64_t kIssueGapMs = 500;      // between two issues for one producer
        // After the last queued entry is issued the producer's +0x300 is set a
        // few frames later; picks in that window must not go stock.
        constexpr uint64_t kRecentIssueMs = 500;
        constexpr size_t kOdfChars = 8;            // GameObjectClass ODF name: char[8], class +0x30

        enum class ClearReason
        {
            Dead,
            Reset,
            OptionOff,
            Multiplayer,
            PlainOrder, // a non-build order (Stop, Go, ...) replaced the build
        };

        inline const char* ReasonName(ClearReason reason)
        {
            switch (reason)
            {
            case ClearReason::Dead:
                return "producer gone";
            case ClearReason::Reset:
                return "mission reset";
            case ClearReason::OptionOff:
                return "option off";
            case ClearReason::Multiplayer:
                return "multiplayer";
            case ClearReason::PlainOrder:
                return "plain order";
            }
            return "unknown";
        }

        // ---- Decisions ---------------------------------------------------------
        // Busy: the producer's build class (+0x300) is set, or it already
        // holds a queue (so the order of picks is kept), or its last queued
        // entry was issued a moment ago (+0x300 not set yet).
        inline bool IsBusy(uint32_t buildClass, int queuedDepth, bool recentlyIssued = false)
        {
            return buildClass != 0 || queuedDepth > 0 || recentlyIssued;
        }

        enum class PickAction
        {
            Stock,      // the stock pick runs
            Enqueue,    // append to the producer's queue
            Refuse,     // queue full: buzz, nothing else
            RemoveLast, // Shift: drop the last queued entry of this item
        };

        // active: option on, hooks bound, single player. shiftHeld: Shift
        // down and the stock multi-select modifier clear. hasMatch: the item
        // is in this producer's queue.
        inline PickAction PlanPick(bool active, bool shiftHeld, bool busy, int queuedDepth, bool hasMatch)
        {
            if (!active)
                return PickAction::Stock;
            if (shiftHeld)
                return hasMatch ? PickAction::RemoveLast : PickAction::Stock;
            if (!busy)
                return PickAction::Stock;
            return queuedDepth >= kMaxEntries ? PickAction::Refuse : PickAction::Enqueue;
        }

        // The stock StartBuild test (0x005AECB0): both costs must be covered.
        inline bool CanAfford(int scrapCost, int scrap, int pilotCost, int pilots)
        {
            return scrapCost <= scrap && pilotCost <= pilots;
        }

        // May the drain issue this producer's front entry now?
        inline bool DrainDue(int queuedDepth, uint32_t buildClass, bool affordable, bool hasIssued,
                             uint64_t lastIssueMs, uint64_t nowMs)
        {
            if (queuedDepth <= 0 || buildClass != 0 || !affordable)
                return false;
            return !hasIssued || nowMs - lastIssueMs >= kIssueGapMs;
        }

        // ---- Table -------------------------------------------------------------
        struct ProducerQueue
        {
            uint32_t handle = 0; // 0: free slot
            int count = 0;
            uint32_t classes[kMaxEntries] = {}; // GameObjectClass pointers, front first
            bool issued = false;
            uint64_t lastIssueMs = 0;
        };

        // Fixed storage. Not thread safe; the owner locks.
        class Table
        {
        public:
            int Depth(uint32_t handle) const
            {
                const ProducerQueue* q = Find(handle);
                return q ? q->count : 0;
            }

            bool Contains(uint32_t handle, uint32_t cls) const
            {
                const ProducerQueue* q = Find(handle);
                if (!q)
                    return false;
                for (int i = 0; i < q->count; ++i)
                    if (q->classes[i] == cls)
                        return true;
                return false;
            }

            // Appends; the new depth, or 0 when refused (full or no slot).
            int Push(uint32_t handle, uint32_t cls)
            {
                if (handle == 0 || cls == 0)
                    return 0;
                ProducerQueue* q = FindMutable(handle);
                if (!q)
                {
                    q = FreeSlot();
                    if (!q)
                        return 0;
                    *q = ProducerQueue();
                    q->handle = handle;
                    // Keep the issue gap after an emptied queue's last pop.
                    if (const RecentIssue* r = FindRecent(handle))
                    {
                        q->issued = true;
                        q->lastIssueMs = r->ms;
                    }
                }
                if (q->count >= kMaxEntries)
                    return 0;
                q->classes[q->count++] = cls;
                return q->count;
            }

            // Removes the last entry of this class; the new depth, or -1 when
            // the class is not queued. An emptied queue frees its slot.
            int RemoveLast(uint32_t handle, uint32_t cls)
            {
                ProducerQueue* q = FindMutable(handle);
                if (!q)
                    return -1;
                for (int i = q->count - 1; i >= 0; --i)
                {
                    if (q->classes[i] != cls)
                        continue;
                    for (int j = i + 1; j < q->count; ++j)
                        q->classes[j - 1] = q->classes[j];
                    --q->count;
                    const int left = q->count;
                    if (left == 0)
                        *q = ProducerQueue();
                    return left;
                }
                return -1;
            }

            uint32_t Front(uint32_t handle) const
            {
                const ProducerQueue* q = Find(handle);
                return (q && q->count > 0) ? q->classes[0] : 0;
            }

            // Removes the front entry. An emptied queue frees its slot; its
            // issue time moves to the recent-issue record (RecentlyIssued).
            bool PopFront(uint32_t handle, uint64_t nowMs)
            {
                ProducerQueue* q = FindMutable(handle);
                if (!q || q->count == 0)
                    return false;
                for (int i = 1; i < q->count; ++i)
                    q->classes[i - 1] = q->classes[i];
                --q->count;
                NoteRecent(handle, nowMs);
                if (q->count == 0)
                    *q = ProducerQueue();
                else
                {
                    q->issued = true;
                    q->lastIssueMs = nowMs;
                }
                return true;
            }

            // True when an entry of this producer was issued less than
            // kRecentIssueMs ago, even if its queue is gone since.
            bool RecentlyIssued(uint32_t handle, uint64_t nowMs) const
            {
                const RecentIssue* r = FindRecent(handle);
                return r && nowMs >= r->ms && nowMs - r->ms < kRecentIssueMs;
            }

            bool Issued(uint32_t handle, uint64_t& lastIssueMs) const
            {
                const ProducerQueue* q = Find(handle);
                if (!q || !q->issued)
                    return false;
                lastIssueMs = q->lastIssueMs;
                return true;
            }

            int Clear(uint32_t handle)
            {
                ProducerQueue* q = FindMutable(handle);
                if (!q)
                    return 0;
                const int dropped = q->count;
                *q = ProducerQueue();
                return dropped;
            }

            int ClearAll()
            {
                int dropped = 0;
                for (ProducerQueue& q : m_producers)
                {
                    if (q.handle != 0)
                        dropped += q.count;
                    q = ProducerQueue();
                }
                for (RecentIssue& r : m_recent)
                    r = RecentIssue();
                return dropped;
            }

            int ProducerCount() const
            {
                int n = 0;
                for (const ProducerQueue& q : m_producers)
                    if (q.handle != 0)
                        ++n;
                return n;
            }

            // The handle of the i-th producer with a queue (0 past the end).
            uint32_t HandleAt(int index) const
            {
                int n = 0;
                for (const ProducerQueue& q : m_producers)
                {
                    if (q.handle == 0)
                        continue;
                    if (n++ == index)
                        return q.handle;
                }
                return 0;
            }

        private:
            struct RecentIssue
            {
                uint32_t handle = 0;
                uint64_t ms = 0;
            };

            const RecentIssue* FindRecent(uint32_t handle) const
            {
                if (handle == 0)
                    return nullptr;
                for (const RecentIssue& r : m_recent)
                    if (r.handle == handle)
                        return &r;
                return nullptr;
            }
            void NoteRecent(uint32_t handle, uint64_t nowMs)
            {
                RecentIssue* slot = const_cast<RecentIssue*>(FindRecent(handle));
                if (!slot)
                {
                    slot = &m_recent[m_recentNext];
                    m_recentNext = (m_recentNext + 1) % kMaxProducers;
                }
                slot->handle = handle;
                slot->ms = nowMs;
            }

            const ProducerQueue* Find(uint32_t handle) const
            {
                if (handle == 0)
                    return nullptr;
                for (const ProducerQueue& q : m_producers)
                    if (q.handle == handle)
                        return &q;
                return nullptr;
            }
            ProducerQueue* FindMutable(uint32_t handle)
            {
                return const_cast<ProducerQueue*>(Find(handle));
            }
            ProducerQueue* FreeSlot()
            {
                for (ProducerQueue& q : m_producers)
                    if (q.handle == 0)
                        return &q;
                return nullptr;
            }

            ProducerQueue m_producers[kMaxProducers];
            RecentIssue m_recent[kMaxProducers];
            int m_recentNext = 0;
        };

        // ---- Badges ------------------------------------------------------------
        // What the badge painter reads about one producer (see
        // RtsBuildQueueBadgeQuery in rts_build_queue.cpp).
        struct BadgeInfo
        {
            int queued = 0;       // entries in the queue
            bool waiting = false; // idle, queue non-empty, next entry not affordable
            char nextOdf[kOdfChars + 1] = {};
        };

        // Appends " +N" to text (NUL-terminated, capacity size) when N > 0;
        // the base text is cut first if it does not fit.
        inline void AppendQueuedSuffix(char* text, size_t size, int queued)
        {
            if (!text || size == 0 || queued <= 0)
                return;
            char tail[8];
            size_t t = 0;
            tail[t++] = ' ';
            tail[t++] = '+';
            if (queued > 99)
                queued = 99;
            if (queued >= 10)
                tail[t++] = static_cast<char>('0' + queued / 10);
            tail[t++] = static_cast<char>('0' + queued % 10);
            size_t len = std::strlen(text);
            if (len >= size)
                len = size - 1;
            const size_t room = size - 1;
            if (room < t)
                return;
            if (len + t > room)
                len = room - t;
            std::memcpy(text + len, tail, t);
            text[len + t] = '\0';
        }

        // "<label> <phrase>" (e.g. "Tank waiting for scrap"); false when it
        // does not fit or either part is empty.
        inline bool FormatWaitingText(const char* label, const char* phrase, char* out, size_t capacity)
        {
            if (!label || !phrase || !out || capacity == 0 || label[0] == '\0' || phrase[0] == '\0')
                return false;
            const size_t a = std::strlen(label);
            const size_t b = std::strlen(phrase);
            if (a + 1 + b + 1 > capacity)
                return false;
            std::memcpy(out, label, a);
            out[a] = ' ';
            std::memcpy(out + a + 1, phrase, b);
            out[a + 1 + b] = '\0';
            return true;
        }
    }
}
