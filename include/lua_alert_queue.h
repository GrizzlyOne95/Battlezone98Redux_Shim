// lua_alert_queue.h
// BZR Open Shim - queue of Lua callback error alerts held until the frame ends
// ([Fixes] DeferLuaCallbackAlert). Engine-independent so it can be unit tested.
//
// Copyright (C) 2026 BZR Open Shim contributors
// SPDX-License-Identifier: MIT
#pragma once

#include <cstddef>
#include <cstdint>
#include <string>
#include <utility>
#include <vector>

namespace BZROpenShim
{
    namespace LuaAlertQueue
    {
        // `format` is the engine's own constant ("Lua script DeleteObject error:\n%s"),
        // compared by pointer: every dispatch passes its own string literal.
        struct Entry
        {
            const char* format = nullptr;
            std::string message;
            uint32_t count = 0;
        };

        enum class PushResult
        {
            Added,   // a new alert
            Merged,  // same format and message as a queued one; its count went up
            Dropped, // the queue is full; logged only
        };

        class Queue
        {
        public:
            // A frame that raises more distinct errors than this shows only the
            // first ones; the rest are still in the engine log.
            static constexpr size_t kMaxEntries = 4;
            // The engine formats into a 1024-byte buffer and indexes it with
            // _vsnprintf's result, which is -1 on truncation. Keep the message,
            // the longest dispatch prefix and the repeat note well under that.
            static constexpr size_t kMaxMessageChars = 900;

            PushResult Push(const char* format, const char* message)
            {
                std::string text = message ? message : "(null)";
                if (text.size() > kMaxMessageChars)
                {
                    // Cut before a UTF-8 lead byte so no sequence is split.
                    size_t cut = kMaxMessageChars;
                    while (cut > 0 && (static_cast<unsigned char>(text[cut]) & 0xC0) == 0x80)
                        --cut;
                    text.resize(cut);
                }
                for (Entry& e : m_entries)
                {
                    if (e.format == format && e.message == text)
                    {
                        if (e.count < UINT32_MAX)
                            ++e.count;
                        return PushResult::Merged;
                    }
                }
                if (m_entries.size() >= kMaxEntries)
                {
                    if (m_dropped < UINT32_MAX)
                        ++m_dropped;
                    return PushResult::Dropped;
                }
                m_entries.push_back(Entry{format, std::move(text), 1});
                return PushResult::Added;
            }

            bool Empty() const { return m_entries.empty() && m_dropped == 0; }
            size_t Size() const { return m_entries.size(); }
            uint32_t Dropped() const { return m_dropped; }

            // Hands back the queued alerts in arrival order and empties the
            // queue, so an alert raised while these are shown starts a new batch.
            std::vector<Entry> Drain(uint32_t* droppedOut = nullptr)
            {
                if (droppedOut)
                    *droppedOut = m_dropped;
                m_dropped = 0;
                std::vector<Entry> out;
                out.swap(m_entries);
                return out;
            }

        private:
            std::vector<Entry> m_entries;
            uint32_t m_dropped = 0;
        };

        // The text shown for an entry: the message, plus a repeat note when the
        // same error came more than once in the frame.
        inline std::string DisplayMessage(const Entry& e)
        {
            if (e.count <= 1)
                return e.message;
            return e.message + "\n(repeated " + std::to_string(e.count) + " times this frame)";
        }
    }
}
