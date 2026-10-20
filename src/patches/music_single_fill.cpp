// music_single_fill.cpp
// BZR Open Shim - decode each new music track's first buffer once
//
// Copyright (C) 2026 BZR Open Shim contributors
// SPDX-License-Identifier: MIT
//
// Music track start (GOG 0x004378F0) runs on the main thread when a track
// ends (0x00437B00) or a mission starts. It reads the whole .ogg into the
// resource cache, then OggManager setup (0x0043F050) builds the streaming
// sound, whose constructor (0x00416830) calls FillBufferWithSound
// (0x00416E10) to decode a 3 s buffer. Every path that makes the track
// audible then calls OggManager::Play (0x0043F320), which under the ogg lock
// runs Reset (0x00416CF0: ov_raw_seek to 0, all stream positions zeroed) and
// FillBufferWithSound again. The constructor's decode is overwritten before it
// is heard. The call is __thiscall with two stack arguments and an unused
// result, so it becomes `add esp,8` plus NOPs.
// See reverse_engineering/frame_hitch_va_measurement_20261020.md.

#include "music_single_fill.h"

#include "bzr_hooks_internal.h"
#include "bzr_options_ui.h"
#include "hook_engine.h"
#include "shim_log.h"

#include <cstdint>
#include <cstring>

namespace BZROpenShim
{
    namespace
    {
        constexpr const char* kComponent = "music";

        // [Fixes] MusicSingleFill, default ON. The kill-switch name maps to
        // the inverted ini key in openshim_env_mapping.cpp.
        bool ReadEnabledSetting()
        {
            return !EnvFlagEnabled("OPENSHIM_DISABLE_MUSIC_SINGLE_FILL");
        }
    }

    void InitializeMusicSingleFill()
    {
        if (!ReadEnabledSetting())
        {
            LogShimA(LogLevel::Info, kComponent, "[MusicSingleFill] disabled by [Fixes] MusicSingleFill = 0");
            return;
        }

        const uint32_t callSite = HookEngine::ResolveNamedAddress("StreamingOggSound::CtorFillCall");
        const uint32_t target = HookEngine::ResolveNamedAddress("StreamingOggSound::FillBufferWithSound");
        if (callSite == 0 || target == 0)
        {
            LogShimA(LogLevel::Warn, kComponent,
                     "[MusicSingleFill] stands down: call site 0x%08X target 0x%08X", callSite, target);
            return;
        }

        auto* call = reinterpret_cast<uint8_t*>(static_cast<uintptr_t>(callSite));
        if (Hooks::ResolveRel32Target(call) != target)
        {
            LogShimA(LogLevel::Warn, kComponent,
                     "[MusicSingleFill] stands down: 0x%08X is not a call to 0x%08X", callSite, target);
            return;
        }

        // add esp,8 ; nop ; nop  -- pops the two arguments the callee would have.
        static const uint8_t kPatch[5] = { 0x83, 0xC4, 0x08, 0x90, 0x90 };
        if (!Hooks::WritePatchBytes(callSite, kPatch, sizeof(kPatch)))
        {
            LogShimA(LogLevel::Warn, kComponent,
                     "[MusicSingleFill] stands down: could not write 0x%08X", callSite);
            return;
        }
        LogShimA(LogLevel::Info, kComponent,
                 "[MusicSingleFill] enabled: constructor fill at 0x%08X skipped; Play fills the buffer", callSite);
    }
}
