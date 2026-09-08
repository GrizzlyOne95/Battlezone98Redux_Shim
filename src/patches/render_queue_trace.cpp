#include "render_queue_trace.h"

#include "bzr_options_ui.h"
#include "ogre_runtime.h"
#include "shim_log.h"

#include <windows.h>

#include <atomic>
#include <cstdint>
#include <cstdlib>
#include <string>

namespace BZROpenShim
{
    namespace
    {
        constexpr const char* kComponent = "renderqueue";

        // Enough frames to see the steady-state sequence and any per-camera
        // repetition, without filling the log.
        constexpr int kFrameBudget = 6;

        using FnAddRenderQueueListener = void(__thiscall*)(void* sceneManager, void* listener);
        using FnRemoveRenderQueueListener = void(__thiscall*)(void* sceneManager, void* listener);

        // Ogre::RenderQueueListener is a pure interface, so its vtable layout is
        // the whole contract. Rather than inherit from the repo's copy of the
        // 1.10 header and trust the compiler to agree with the shipped
        // OgreMain, the vtable is built by hand: the assumption is then explicit
        // and every slot logs which slot it is, so an ABI that does not match
        // shows up as a wrong-looking trace rather than as a silent crash.
        //
        // Expected MSVC x86 layout, from OgreRenderQueueListener.h:
        //   [0] scalar deleting destructor
        //   [1] preRenderQueues()
        //   [2] postRenderQueues()
        //   [3] renderQueueStarted(uint8, const String&, bool&)
        //   [4] renderQueueEnded(uint8, const String&, bool&)
        //
        // __thiscall is emulated with __fastcall plus an unused second
        // parameter: that puts `this` in ECX, leaves EDX dead, passes the
        // remaining arguments on the stack, and keeps callee cleanup, which is
        // exactly __thiscall's contract on this target.
        struct ListenerVtable
        {
            void*(__fastcall* destructor)(void* self, void* unused, unsigned flags);
            void(__fastcall* preRenderQueues)(void* self, void* unused);
            void(__fastcall* postRenderQueues)(void* self, void* unused);
            void(__fastcall* renderQueueStarted)(
                void* self, void* unused, std::uint8_t group, const std::string* invocation, bool* skip);
            void(__fastcall* renderQueueEnded)(
                void* self, void* unused, std::uint8_t group, const std::string* invocation, bool* repeat);
        };

        struct Listener
        {
            const ListenerVtable* vtable = nullptr;
        };

        std::atomic<bool> g_Enabled{false};
        std::atomic<bool> g_ConfigLoaded{false};

        // -1 disables. Any other value suppresses that queue group in the
        // default (non-shadow) invocation, so what disappears from the frame
        // identifies what the group draws. Shadow invocations are left alone:
        // suppressing a group there changes shadow content, not the visible
        // frame, and would confuse the reading.
        int g_SkipGroup = -1;

        Listener g_Listener;
        void* g_AttachedTo = nullptr;
        int g_FramesLeft = kFrameBudget;
        int g_Frame = 0;
        int g_StepInFrame = 0;

        bool ReadEnabledSetting()
        {
            bool enabled = false;
            if (TryGetUserConfigBool("Diagnostics", "TraceRenderQueues", enabled) && enabled)
                return true;
            return EnvFlagEnabled("OPENSHIM_TRACE_RENDER_QUEUES");
        }

        void ReadSkipGroupSetting()
        {
            std::string value;
            if (!TryGetUserConfigString("Diagnostics", "SkipRenderQueueGroup", value))
                return;
            value = TrimAsciiCopy(value);
            if (value.empty())
                return;
            char* end = nullptr;
            const long parsed = std::strtol(value.c_str(), &end, 10);
            if (end == value.c_str() || parsed < 0 || parsed > 255)
                return;
            g_SkipGroup = static_cast<int>(parsed);
            LogShimA(LogLevel::Info, kComponent,
                "[RQTRACE] suppressing queue group %ld in the default invocation", parsed);
        }

        bool Enabled()
        {
            if (!g_ConfigLoaded.load(std::memory_order_acquire))
            {
                g_Enabled.store(ReadEnabledSetting(), std::memory_order_relaxed);
                g_ConfigLoaded.store(true, std::memory_order_release);
            }
            return g_Enabled.load(std::memory_order_relaxed);
        }

        // The invocation name is an Ogre::String passed by reference. Reading it
        // is the one place this probe touches engine-owned memory, so it is
        // guarded and length-capped rather than trusted.
        const char* SafeInvocation(const std::string* invocation, char (&scratch)[64])
        {
            scratch[0] = '\0';
            __try
            {
                if (invocation == nullptr)
                    return "<null>";
                const char* text = invocation->c_str();
                if (text == nullptr)
                    return "<null-data>";
                if (text[0] == '\0')
                    return "<default>";
                size_t i = 0;
                for (; i < sizeof(scratch) - 1 && text[i] != '\0'; ++i)
                    scratch[i] = text[i];
                scratch[i] = '\0';
                return scratch;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return "<unreadable>";
            }
        }

        void __fastcall OnRenderQueueStarted(
            void* /*self*/, void* /*unused*/, std::uint8_t group, const std::string* invocation, bool* skip)
        {
            char scratch[64];
            const char* name = SafeInvocation(invocation, scratch);
            const bool isDefaultInvocation = (name != nullptr) && (name[0] == '<');

            if (g_SkipGroup >= 0 && static_cast<int>(group) == g_SkipGroup
                && isDefaultInvocation && skip != nullptr)
            {
                *skip = true;
            }

            if (g_FramesLeft <= 0)
                return;
            LogShimA(LogLevel::Info, kComponent,
                "[RQTRACE] frame=%d step=%d slot=3 queueStarted group=%u invocation=%s%s",
                g_Frame, g_StepInFrame++, static_cast<unsigned>(group), name,
                (g_SkipGroup >= 0 && static_cast<int>(group) == g_SkipGroup && isDefaultInvocation)
                    ? " [SKIPPED]" : "");
        }

        void __fastcall OnRenderQueueEnded(
            void* /*self*/, void* /*unused*/, std::uint8_t group, const std::string* invocation, bool* /*repeat*/)
        {
            if (g_FramesLeft <= 0)
                return;
            char scratch[64];
            LogShimA(LogLevel::Info, kComponent,
                "[RQTRACE] frame=%d step=%d slot=4 queueEnded   group=%u invocation=%s",
                g_Frame, g_StepInFrame++, static_cast<unsigned>(group),
                SafeInvocation(invocation, scratch));
        }

        void __fastcall OnPreRenderQueues(void* /*self*/, void* /*unused*/)
        {
            if (g_FramesLeft <= 0)
                return;
            g_StepInFrame = 0;
            LogShimA(LogLevel::Info, kComponent,
                "[RQTRACE] frame=%d slot=1 preRenderQueues", g_Frame);
        }

        void __fastcall OnPostRenderQueues(void* /*self*/, void* /*unused*/)
        {
            if (g_FramesLeft <= 0)
                return;
            LogShimA(LogLevel::Info, kComponent,
                "[RQTRACE] frame=%d slot=2 postRenderQueues (end of this camera's queues)",
                g_Frame);
            ++g_Frame;
            --g_FramesLeft;
            if (g_FramesLeft == 0)
            {
                LogShimA(LogLevel::Info, kComponent,
                    "[RQTRACE] budget spent after %d frames; listener stays attached but silent",
                    kFrameBudget);
            }
        }

        // Never invoked: the listener is a static, and nothing in Ogre deletes a
        // registered listener. Present only so the slot is not garbage if the
        // engine ever reaches it.
        void* __fastcall OnDestroy(void* self, void* /*unused*/, unsigned /*flags*/)
        {
            LogShimA(LogLevel::Warn, kComponent,
                "[RQTRACE] slot=0 destructor reached unexpectedly; not freeing");
            return self;
        }

        const ListenerVtable kVtable = {
            &OnDestroy,
            &OnPreRenderQueues,
            &OnPostRenderQueues,
            &OnRenderQueueStarted,
            &OnRenderQueueEnded,
        };
    }

    void RenderQueueTraceTick(void* sceneManager)
    {
        if (!Enabled() || sceneManager == nullptr || g_AttachedTo != nullptr)
            return;

        const auto add = reinterpret_cast<FnAddRenderQueueListener>(
            OgreRuntime::ResolveExport(
                "?addRenderQueueListener@SceneManager@Ogre@@UAEXPAVRenderQueueListener@2@@Z"));
        if (add == nullptr)
        {
            // Fail closed and stop asking: a missing export is a build fact, not
            // a transient condition.
            g_Enabled.store(false, std::memory_order_relaxed);
            LogShimA(LogLevel::Warn, kComponent,
                "[RQTRACE] addRenderQueueListener not exported; trace stood down");
            return;
        }

        g_Listener.vtable = &kVtable;
        __try
        {
            add(sceneManager, &g_Listener);
            g_AttachedTo = sceneManager;
            ReadSkipGroupSetting();
            LogShimA(LogLevel::Info, kComponent,
                "[RQTRACE] listener attached sceneManager=%p budget=%d frames skipGroup=%d",
                sceneManager, kFrameBudget, g_SkipGroup);
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            g_Enabled.store(false, std::memory_order_relaxed);
            LogShimA(LogLevel::Warn, kComponent,
                "[RQTRACE] addRenderQueueListener crashed code=0x%08X; trace stood down",
                GetExceptionCode());
        }
    }

    void RenderQueueTraceShutdown()
    {
        if (g_AttachedTo == nullptr)
            return;

        const auto remove = reinterpret_cast<FnRemoveRenderQueueListener>(
            OgreRuntime::ResolveExport(
                "?removeRenderQueueListener@SceneManager@Ogre@@UAEXPAVRenderQueueListener@2@@Z"));
        void* attached = g_AttachedTo;
        g_AttachedTo = nullptr;
        if (remove == nullptr)
            return;

        __try
        {
            remove(attached, &g_Listener);
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            LogShimA(LogLevel::Warn, kComponent,
                "[RQTRACE] removeRenderQueueListener crashed code=0x%08X", GetExceptionCode());
        }
    }
}
