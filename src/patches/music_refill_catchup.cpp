// music_refill_catchup.cpp
// BZR Open Shim - keep the music stream's writer level with the play cursor
//
// Copyright (C) 2026 BZR Open Shim contributors
// SPDX-License-Identifier: MIT
//
// Music plays from a 3 s DirectSound ring split into 16 chunks (GOG 0x0043EC90
// sizes it; one notification per chunk, all on one auto-reset event created
// at 0x0043E980). The "OggDecoder" thread (0x0043E8A0) waits on that event
// and, under the stream lock, calls StreamingOggSound::Refill (0x00416AA0),
// which decodes exactly one chunk at the write cursor (+0x20) and advances it
// by one chunk modulo the ring size (+0x08). The write cursor is never
// compared with the play cursor. When two notifications fire before the
// thread wakes, the auto-reset event delivers one wake, so the writer falls a
// chunk behind for the rest of the track. After enough misses the play cursor
// reaches chunks that were never refilled and replays stale audio: the
// "scratched CD" skip. A stale signal can also wake the thread right after a
// Play reset, when the chunk at the write cursor is the one now playing.
//
// The decoder's call to Refill is redirected here. A wake whose play cursor
// is still inside the first half of the chunk at the write cursor is stale
// and skipped (a real notification fires at the chunk's last byte). After a
// real refill, Refill runs again while a whole played chunk still lies
// between the write cursor and the play cursor, so missed notifications are
// made up on the next wake. A lost or stopped buffer, a refill that did not
// advance the write cursor by one chunk, or a writer already ahead of play
// gets the stock single call and no catch-up.

#include "music_refill_catchup.h"

#include "bzr_hooks_internal.h"
#include "hook_engine.h"
#include "shim_log.h"

#include <atomic>
#include <cstdint>

namespace BZROpenShim
{
    namespace
    {
        constexpr const char* kComponent = "music";

        // StreamingOggSound fields used by Refill (0x00416AA0).
        constexpr uintptr_t kBufferHolderOffset = 0x04; // -> IDirectSoundBuffer*
        constexpr uintptr_t kRingBytesOffset = 0x08;
        constexpr uintptr_t kChunkBytesOffset = 0x1C;
        constexpr uintptr_t kWriteCursorOffset = 0x20;

        // IDirectSoundBuffer vtable slots.
        constexpr size_t kGetCurrentPositionSlot = 4; // +0x10
        constexpr size_t kGetStatusSlot = 9;          // +0x24
        constexpr uint32_t kStatusPlaying = 0x1;      // DSBSTATUS_PLAYING
        constexpr uint32_t kStatusBufferLost = 0x2;   // DSBSTATUS_BUFFERLOST

        // The ring has 16 chunks; one wake may make up all but the one playing.
        constexpr int kMaxExtraRefills = 15;
        // Log the first few events of each kind, then every Nth.
        constexpr uint32_t kLogFirst = 10;
        constexpr uint32_t kLogEvery = 100;

        using RefillFn = int(__thiscall*)(void* sound, uint32_t loop);
        using GetCurrentPositionFn = long(__stdcall*)(void* buffer, uint32_t* play, uint32_t* write);
        using GetStatusFn = long(__stdcall*)(void* buffer, uint32_t* status);

        RefillFn g_Refill = nullptr;
        std::atomic<uint32_t> g_CatchUps{0};
        std::atomic<uint32_t> g_ChunksMadeUp{0};
        std::atomic<uint32_t> g_StaleWakes{0};

        bool ShouldLog(uint32_t count)
        {
            return count <= kLogFirst || count % kLogEvery == 0;
        }

        void* BufferOf(void* sound)
        {
            auto* holder = *reinterpret_cast<void***>(static_cast<uint8_t*>(sound) + kBufferHolderOffset);
            return holder ? *holder : nullptr;
        }

        template <typename Fn>
        Fn Slot(void* com, size_t slot)
        {
            return reinterpret_cast<Fn>((*reinterpret_cast<void***>(com))[slot]);
        }

        uint32_t Field(void* sound, uintptr_t offset)
        {
            return *reinterpret_cast<uint32_t*>(static_cast<uint8_t*>(sound) + offset);
        }

        // Bytes the play cursor is past the write cursor, or false when the
        // buffer is not a healthy playing ring (stock handles those).
        bool TryPlayedAhead(void* sound, uint32_t& ahead, uint32_t& chunk)
        {
            void* buffer = BufferOf(sound);
            if (!buffer)
                return false;
            uint32_t status = 0;
            if (Slot<GetStatusFn>(buffer, kGetStatusSlot)(buffer, &status) < 0 ||
                (status & kStatusBufferLost) != 0 || (status & kStatusPlaying) == 0)
                return false;
            const uint32_t ring = Field(sound, kRingBytesOffset);
            chunk = Field(sound, kChunkBytesOffset);
            const uint32_t write = Field(sound, kWriteCursorOffset);
            if (ring == 0 || chunk == 0 || chunk > ring || write >= ring)
                return false;
            uint32_t play = 0;
            uint32_t ignored = 0;
            if (Slot<GetCurrentPositionFn>(buffer, kGetCurrentPositionSlot)(buffer, &play, &ignored) < 0 ||
                play >= ring)
                return false;
            ahead = (play + ring - write) % ring;
            return true;
        }

        // Replaces the decoder thread's `call Refill` (ecx = sound, one stack
        // argument, callee pops it): __fastcall with an unused edx matches.
        int __fastcall RefillCatchUp(void* sound, void* /*edx*/, uint32_t loop)
        {
            uint32_t ahead = 0;
            uint32_t chunk = 0;
            const bool healthy = TryPlayedAhead(sound, ahead, chunk);
            if (healthy && ahead < chunk / 2)
            {
                const uint32_t n = g_StaleWakes.fetch_add(1, std::memory_order_relaxed) + 1;
                if (ShouldLog(n))
                    LogShimA(LogLevel::Info, kComponent,
                             "[MusicRefillCatchUp] stale wake skipped (play %u bytes into the chunk at the write cursor; #%u)",
                             ahead, n);
                return 0;
            }

            const uint32_t writeBefore = Field(sound, kWriteCursorOffset);
            int result = g_Refill(sound, loop);
            // Catch up only after a normal one-chunk refill of a healthy ring:
            // a lost-buffer restore refills the whole ring without moving the
            // write cursor, and that audio has not played yet.
            const uint32_t ring = Field(sound, kRingBytesOffset);
            const bool normalRefill =
                healthy && ring != 0 && Field(sound, kWriteCursorOffset) == (writeBefore + chunk) % ring;
            int extra = 0;
            // ahead > ring - chunk means the writer is ahead of play, not a
            // whole ring behind; refilling then would overwrite unplayed audio.
            while (normalRefill && result >= 0 && extra < kMaxExtraRefills &&
                   TryPlayedAhead(sound, ahead, chunk) && ahead >= chunk && ahead <= ring - chunk)
            {
                result = g_Refill(sound, loop);
                ++extra;
            }
            if (extra > 0)
            {
                const uint32_t n = g_CatchUps.fetch_add(1, std::memory_order_relaxed) + 1;
                const uint32_t total =
                    g_ChunksMadeUp.fetch_add(static_cast<uint32_t>(extra), std::memory_order_relaxed) + extra;
                if (ShouldLog(n))
                    LogShimA(LogLevel::Info, kComponent,
                             "[MusicRefillCatchUp] writer was %d chunk(s) behind the play cursor; refilled (#%u, %u chunks total)",
                             extra, n, total);
            }
            return result;
        }

        // [Fixes] MusicRefillCatchUp, default ON. The kill-switch name maps
        // to the inverted ini key in openshim_env_mapping.cpp.
        bool ReadEnabledSetting()
        {
            return !EnvFlagEnabled("OPENSHIM_DISABLE_MUSIC_REFILL_CATCHUP");
        }
    }

    void InitializeMusicRefillCatchUp()
    {
        if (!ReadEnabledSetting())
        {
            LogShimA(LogLevel::Info, kComponent, "[MusicRefillCatchUp] disabled by [Fixes] MusicRefillCatchUp = 0");
            return;
        }

        const uint32_t callSite = HookEngine::ResolveNamedAddress("OggDecoder::RefillCall");
        const uint32_t target = HookEngine::ResolveNamedAddress("StreamingOggSound::Refill");
        if (callSite == 0 || target == 0)
        {
            LogShimA(LogLevel::Warn, kComponent,
                     "[MusicRefillCatchUp] stands down: call site 0x%08X target 0x%08X", callSite, target);
            return;
        }

        g_Refill = reinterpret_cast<RefillFn>(static_cast<uintptr_t>(target));
        if (!Hooks::RedirectCallTarget(callSite, target, reinterpret_cast<uintptr_t>(&RefillCatchUp)))
        {
            g_Refill = nullptr;
            LogShimA(LogLevel::Warn, kComponent,
                     "[MusicRefillCatchUp] stands down: 0x%08X is not a call to 0x%08X", callSite, target);
            return;
        }
        LogShimA(LogLevel::Info, kComponent,
                 "[MusicRefillCatchUp] enabled: decoder refill at 0x%08X catches up to the play cursor", callSite);
    }
}
