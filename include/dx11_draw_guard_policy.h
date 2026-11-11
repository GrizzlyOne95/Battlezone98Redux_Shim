// dx11_draw_guard_policy.h
//
// Pure bookkeeping for the DX11 draw-time shaderless guard ([Fixes]
// DX11ShaderlessDrawGuard; Docs/DX11_LEGACY_MATERIAL_COMPATIBILITY.md, "Level
// 5 - shaderless-draw guard"). The runtime in src/patches/ogre_render_profile.cpp
// detours Ogre::SceneManager::renderSingleObject and skips a draw whose pass
// lacks a vertex or fragment program, because D3D11RenderSystem::_render would
// throw on it and unwind the rest of the render queue. This header decides,
// per skipped draw, whether the material is new (log it, queue one compat
// attempt) or already known (skip silently).
//
// A key is (Resource handle, Resource state count). Handles are never reused,
// and Ogre bumps the state count on every load, so a material that is reloaded
// or re-parsed is a new key and gets one fresh attempt.
//
// No Win32, no Ogre. Host-tested in tests/dx11_draw_guard_policy_tests.cpp.
#pragma once

#include <cstddef>
#include <cstdint>
#include <string_view>
#include <unordered_set>

namespace BZROpenShim::RenderProfiles::Dx11Compat
{
    struct DrawGuardKey
    {
        uint64_t handle = 0;
        uint32_t stateCount = 0;

        bool operator==(const DrawGuardKey& other) const noexcept
        {
            return handle == other.handle && stateCount == other.stateCount;
        }
    };

    struct DrawGuardKeyHash
    {
        size_t operator()(const DrawGuardKey& key) const noexcept
        {
            const uint64_t mixed = key.handle * 0x9E3779B97F4A7C15ull ^ key.stateCount;
            return static_cast<size_t>(mixed ^ (mixed >> 32));
        }
    };

    // What the runtime does with one skipped draw.
    struct DrawGuardDecision
    {
        bool isNew = false;          // first skip of this key: queue one compat attempt
        bool log = false;            // write the one [DX11DRAWGUARD] skip line for it
        bool logCapReached = false;  // write the one "further keys are silent" line
    };

    // "vs", "ps", "vs+ps" or "none" for a pass's missing programs.
    inline const char* DrawGuardMissingPrograms(bool hasVertex, bool hasFragment) noexcept
    {
        if (!hasVertex && !hasFragment)
            return "vs+ps";
        if (!hasVertex)
            return "vs";
        if (!hasFragment)
            return "ps";
        return "none";
    }

    // A pass D3D11RenderSystem::_render throws on: it has no fixed pipeline.
    inline bool DrawGuardShouldSkip(bool hasVertex, bool hasFragment) noexcept
    {
        return !hasVertex || !hasFragment;
    }

    // A queued compat attempt that declined only because the renderer was not
    // ready yet is retried on later frames, up to this many attempts; any
    // other decline is final for that key (a reload makes a new key).
    constexpr unsigned kDrawGuardMaxTransientAttempts = 600;

    inline bool DrawGuardOutcomeIsTransient(std::string_view outcome) noexcept
    {
        return outcome == "renderer-resources-unavailable" || outcome == "abi-unavailable";
    }

    // attemptsMade counts the attempt that just declined.
    inline bool DrawGuardShouldRetry(std::string_view outcome, unsigned attemptsMade) noexcept
    {
        return DrawGuardOutcomeIsTransient(outcome) &&
               attemptsMade < kDrawGuardMaxTransientAttempts;
    }

    // Not thread-safe; the runtime holds its lock around every call.
    class DrawGuardLedger
    {
    public:
        static constexpr size_t kDefaultMaxKeys = 256;
        static constexpr size_t kDefaultMaxLogLines = 64;

        explicit DrawGuardLedger(size_t maxKeys = kDefaultMaxKeys,
                                 size_t maxLogLines = kDefaultMaxLogLines)
            : m_maxKeys(maxKeys), m_maxLogLines(maxLogLines)
        {
        }

        // Records one skipped draw. A key seen before, or any key once the
        // table is full, is skipped silently with no compat attempt: a mod
        // that reloads a material every frame cannot grow this without bound.
        DrawGuardDecision NoteSkip(const DrawGuardKey& key)
        {
            ++m_skippedDraws;
            DrawGuardDecision decision;
            if (m_keys.find(key) != m_keys.end())
                return decision;
            if (m_keys.size() >= m_maxKeys)
            {
                ++m_untrackedDraws;
                if (!m_keyCapNoted)
                {
                    m_keyCapNoted = true;
                    decision.logCapReached = !m_logCapNoted;
                    m_logCapNoted = true;
                }
                return decision;
            }
            m_keys.insert(key);
            decision.isNew = true;
            if (m_logLines < m_maxLogLines)
            {
                ++m_logLines;
                decision.log = true;
            }
            else if (!m_logCapNoted)
            {
                m_logCapNoted = true;
                decision.logCapReached = true;
            }
            return decision;
        }

        bool IsKnown(const DrawGuardKey& key) const
        {
            return m_keys.find(key) != m_keys.end();
        }

        size_t TrackedKeys() const noexcept { return m_keys.size(); }
        size_t LogLines() const noexcept { return m_logLines; }
        uint64_t SkippedDraws() const noexcept { return m_skippedDraws; }
        uint64_t UntrackedDraws() const noexcept { return m_untrackedDraws; }

    private:
        std::unordered_set<DrawGuardKey, DrawGuardKeyHash> m_keys;
        size_t m_maxKeys;
        size_t m_maxLogLines;
        size_t m_logLines = 0;
        uint64_t m_skippedDraws = 0;
        uint64_t m_untrackedDraws = 0;
        bool m_keyCapNoted = false;
        bool m_logCapNoted = false;
    };
}
