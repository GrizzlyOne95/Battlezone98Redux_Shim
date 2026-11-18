// rts_order_queue_policy.h
// Pure decision rules for [Gameplay] RtsOrderQueue (src/patches/rts_order_queue.cpp,
// Docs/RTS_ORDER_QUEUE.md). No Windows or engine access, so the tests can
// include it: the queue storage and its caps, which commands queue, when a
// queued entry may be issued, the label text, and the per-unit plan of one
// Space/Alt press.
#pragma once

#include <cstddef>
#include <cstdint>
#include <cstring>

namespace BZROpenShim
{
    namespace RtsOrderQueuePolicy
    {
        // ---- Caps and timing ---------------------------------------------------
        constexpr int kMaxEntries = 8;           // queued orders per unit
        constexpr int kMaxUnits = 32;            // units with a queue at once
        constexpr uint64_t kPopGapMs = 500;      // between two pops of one unit
        constexpr uint64_t kDrainIntervalMs = 250; // 4 Hz drain
        constexpr size_t kLabelCapacity = 96;

        // ---- Commands ----------------------------------------------------------
        // AiCommand ids (names table 0x008E7A18; reverse_engineering/bsim/out/
        // object_model/enums.md).
        constexpr int kCmdSelect = 1;
        constexpr int kCmdStop = 2;
        constexpr int kCmdGo = 3;
        constexpr int kCmdAttack = 4;
        constexpr int kCmdFollow = 5;
        constexpr int kCmdPickup = 7;
        constexpr int kCmdDropoff = 8;
        constexpr int kCmdNoDropoff = 9;
        constexpr int kCmdGetRepair = 10;
        constexpr int kCmdGetReload = 11;
        constexpr int kCmdDefend = 15;
        constexpr int kCmdBuild = 21;

        // The commands the Space/Alt button can queue. Select (Ctrl+Space is
        // SelectAdd), No Dropoff, Stop, Build and everything else stay stock.
        inline bool IsQueueable(int cmd)
        {
            switch (cmd)
            {
            case kCmdGo:
            case kCmdAttack:
            case kCmdFollow:
            case kCmdPickup:
            case kCmdDropoff:
            case kCmdGetRepair:
            case kCmdGetReload:
            case kCmdDefend:
                return true;
            default:
                return false;
            }
        }

        // ---- Entries -----------------------------------------------------------
        enum class Kind : uint8_t
        {
            Object, // SetCommand(what, target): target is a handle
            Ground, // SetCommand(what, where, param)
        };

        struct Entry
        {
            int cmd = 0;
            Kind kind = Kind::Object;
            uint32_t target = 0; // object handle (Kind::Object)
            float where[3] = {}; // sim position (Kind::Ground)
            int param = 0;       // the stock broadcast's selectNum (Kind::Ground)
        };

        enum class ClearReason
        {
            Dead,
            PlainOrder,
            Reset,
            OptionOff,
            Multiplayer,
        };

        inline const char* ReasonName(ClearReason reason)
        {
            switch (reason)
            {
            case ClearReason::Dead:
                return "unit gone";
            case ClearReason::PlainOrder:
                return "plain order";
            case ClearReason::Reset:
                return "mission reset";
            case ClearReason::OptionOff:
                return "option off";
            case ClearReason::Multiplayer:
                return "multiplayer";
            }
            return "unknown";
        }

        struct UnitQueue
        {
            uint32_t handle = 0; // 0: free slot
            int count = 0;
            Entry entries[kMaxEntries];
            bool popped = false;
            uint64_t lastPopMs = 0;
        };

        // Fixed storage: kMaxUnits queues of kMaxEntries entries. Not thread
        // safe; the owner locks.
        class Table
        {
        public:
            // Queue depth of a unit (0: none).
            int Depth(uint32_t handle) const
            {
                const UnitQueue* q = Find(handle);
                return q ? q->count : 0;
            }

            // Room for one more entry for this unit (a free unit slot counts
            // when it has no queue yet).
            bool CanPush(uint32_t handle) const
            {
                if (handle == 0)
                    return false;
                if (const UnitQueue* q = Find(handle))
                    return q->count < kMaxEntries;
                return FreeSlot() != nullptr;
            }

            // Appends; the new depth, or 0 when refused.
            int Push(uint32_t handle, const Entry& entry)
            {
                if (!CanPush(handle))
                    return 0;
                UnitQueue* q = FindMutable(handle);
                if (!q)
                {
                    q = FreeSlot();
                    *q = UnitQueue();
                    q->handle = handle;
                }
                q->entries[q->count++] = entry;
                return q->count;
            }

            // May the unit's next entry be issued now? It needs an entry and
            // (the caller's idle read) to be idle, and kPopGapMs since its
            // last pop.
            bool PopDue(uint32_t handle, bool idle, uint64_t nowMs) const
            {
                const UnitQueue* q = Find(handle);
                if (!q || q->count == 0 || !idle)
                    return false;
                return !q->popped || nowMs - q->lastPopMs >= kPopGapMs;
            }

            // Removes and returns the front entry. False when empty. An
            // emptied queue frees its slot.
            bool PopFront(uint32_t handle, Entry& out)
            {
                UnitQueue* q = FindMutable(handle);
                if (!q || q->count == 0)
                    return false;
                out = q->entries[0];
                for (int i = 1; i < q->count; ++i)
                    q->entries[i - 1] = q->entries[i];
                --q->count;
                if (q->count == 0)
                    q->handle = 0;
                return true;
            }

            // Stamps the pop time for the gap rule; call after PopFront when
            // an entry was actually issued. A queue emptied by PopFront has
            // no slot left, so the stamp is kept only while entries remain.
            void NoteIssued(uint32_t handle, uint64_t nowMs)
            {
                if (UnitQueue* q = FindMutable(handle))
                {
                    q->popped = true;
                    q->lastPopMs = nowMs;
                }
            }

            // Drops a unit's whole queue; the number of entries dropped.
            int Clear(uint32_t handle)
            {
                UnitQueue* q = FindMutable(handle);
                if (!q)
                    return 0;
                const int dropped = q->count;
                *q = UnitQueue();
                return dropped;
            }

            int ClearAll()
            {
                int dropped = 0;
                for (UnitQueue& q : m_units)
                {
                    if (q.handle != 0)
                        dropped += q.count;
                    q = UnitQueue();
                }
                return dropped;
            }

            int UnitCount() const
            {
                int n = 0;
                for (const UnitQueue& q : m_units)
                    if (q.handle != 0)
                        ++n;
                return n;
            }

            // The handle of the i-th unit with a queue (0 past the end).
            uint32_t HandleAt(int index) const
            {
                int n = 0;
                for (const UnitQueue& q : m_units)
                {
                    if (q.handle == 0)
                        continue;
                    if (n++ == index)
                        return q.handle;
                }
                return 0;
            }

            // Copies a unit's entries in order; the count copied.
            int Snapshot(uint32_t handle, Entry* out, int capacity) const
            {
                const UnitQueue* q = Find(handle);
                if (!q)
                    return 0;
                int n = 0;
                for (; n < q->count && n < capacity; ++n)
                    out[n] = q->entries[n];
                return n;
            }

        private:
            const UnitQueue* Find(uint32_t handle) const
            {
                if (handle == 0)
                    return nullptr;
                for (const UnitQueue& q : m_units)
                    if (q.handle == handle)
                        return &q;
                return nullptr;
            }
            UnitQueue* FindMutable(uint32_t handle)
            {
                return const_cast<UnitQueue*>(Find(handle));
            }
            UnitQueue* FreeSlot()
            {
                for (UnitQueue& q : m_units)
                    if (q.handle == 0)
                        return &q;
                return nullptr;
            }
            const UnitQueue* FreeSlot() const
            {
                for (const UnitQueue& q : m_units)
                    if (q.handle == 0)
                        return &q;
                return nullptr;
            }

            UnitQueue m_units[kMaxUnits];
        };

        // ---- One press ---------------------------------------------------------
        // Shared by the label and the press hook: the option is active (on,
        // hooks bound, single player), Shift is held (Ctrl is not),
        // something is selected and the context command queues.
        inline bool QueueArmed(bool active, bool modifierHeld, int selectNum, int cmd)
        {
            return active && modifierHeld && selectNum > 0 && IsQueueable(cmd);
        }

        // The press hook queues instead of calling the stock broadcast. The
        // rally confirm (set mode armed) keeps priority and stays stock.
        inline bool ShouldQueuePress(bool active, bool modifierHeld, int selectNum, int cmd, bool rallyConfirmPending,
                                     bool haveTarget)
        {
            return QueueArmed(active, modifierHeld, selectNum, cmd) && !rallyConfirmPending && haveTarget;
        }

        enum class UnitAction
        {
            Skip,     // not an own commandable unit
            IssueNow, // idle and nothing queued: the order goes out at once
            Append,   // busy, or already holds a queue: end of its queue
        };

        inline UnitAction PlanUnit(bool eligible, int queuedDepth, bool idle)
        {
            if (!eligible)
                return UnitAction::Skip;
            return (queuedDepth == 0 && idle) ? UnitAction::IssueNow : UnitAction::Append;
        }

        // ---- Label -------------------------------------------------------------
        // "<prefix> <stock>"; false (out untouched past index 0) when either
        // is empty or the result does not fit.
        inline bool FormatQueueLabel(const char* prefix, const char* stock, char* out, size_t capacity)
        {
            if (!prefix || !stock || !out || capacity == 0 || prefix[0] == '\0' || stock[0] == '\0')
                return false;
            const size_t a = std::strlen(prefix);
            const size_t b = std::strlen(stock);
            if (a + 1 + b + 1 > capacity)
                return false;
            std::memcpy(out, prefix, a);
            out[a] = ' ';
            std::memcpy(out + a + 1, stock, b);
            out[a + 1 + b] = '\0';
            return true;
        }

        // ---- Drawing -----------------------------------------------------------
        // Amber, apart from the stock waypoint colours (green go, red attack,
        // blue follow/defend, yellow other).
        struct LineColour
        {
            float r, g, b, a;
        };
        constexpr LineColour kQueueColour = {1.00f, 0.55f, 0.05f, 0.80f};
    }
}
