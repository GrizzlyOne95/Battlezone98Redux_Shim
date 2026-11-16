#pragma once

// When Direct3D 11 device-loss recovery gives up and ends the game.
//
// d3d11_device_loss_recovery.cpp lets Ogre recreate a removed device. Ogre's
// restore is not exception-safe: when a step throws, the window is left with
// no swap chain and the next frame dereferences it (the 2026-11-15 crash in
// D3D11RenderWindowHwnd::_beginUpdate). So each recovery step that cannot
// lead to a working renderer ends the process cleanly with a logged reason
// instead. A clean exit beats a null dereference, and a crash or exit beats
// an endless black screen of back-to-back resets, which the budget below
// stops. Kept free of Windows headers so the tests can drive it.

#include <cstddef>
#include <cstdint>

namespace BZROpenShim
{
namespace D3D11RecoveryPolicy
{
    // At most kMaxRecoveries device recreations inside any kWindowMs; one
    // more means the GPU keeps resetting and the session cannot recover.
    constexpr unsigned kMaxRecoveries = 3;
    constexpr uint32_t kWindowMs = 120000;

    // Remembers the tick (GetTickCount, ms, wraps every ~49.7 days) of the
    // recent recoveries. Unsigned subtraction keeps the window correct
    // across the wrap.
    class Budget
    {
    public:
        // Records a recovery starting at nowMs. Returns false when it is one
        // too many for the window; the caller then fails closed.
        bool Admit(uint32_t nowMs)
        {
            unsigned inWindow = 0;
            for (size_t i = 0; i < m_Count; ++i)
                if (nowMs - m_Ticks[i] < kWindowMs)
                    ++inWindow;
            if (inWindow >= kMaxRecoveries)
                return false;
            m_Ticks[m_Next] = nowMs;
            m_Next = (m_Next + 1) % kMaxRecoveries;
            if (m_Count < kMaxRecoveries)
                ++m_Count;
            return true;
        }

    private:
        uint32_t m_Ticks[kMaxRecoveries] = {};
        size_t m_Count = 0;
        size_t m_Next = 0;
    };

    // When a recovery starts. Returns the reason to fail closed, or nullptr.
    inline const char* BudgetReason(bool budgetAdmitted)
    {
        static_assert(kMaxRecoveries == 3 && kWindowMs == 120000, "update the reason text below");
        return budgetAdmitted ? nullptr : "the GPU was reset more than 3 times within 120 s";
    }

    // Once the hardware adapter has been waited for. A software
    // (WARP/reference) device after a reset ran out of memory and crashed in
    // the renderer (d3d11_device_loss_recovery.cpp header), so one is never
    // created while the hardware adapter has not come back.
    inline const char* AdapterReason(bool hardwareSettled, bool requestedSoftware)
    {
        if (!hardwareSettled && requestedSoftware)
            return "the hardware adapter did not come back and Ogre asked for a software (WARP) device";
        return nullptr;
    }

    // After a recovery's device creation. Ogre throws when creation fails
    // (OgreD3D11RenderSystem.cpp:295-298) after releasing the old device, so the
    // renderer has nothing to draw with.
    inline const char* AfterCreate(bool created)
    {
        return created ? nullptr : "the replacement device could not be created";
    }

    // An exception escaped Ogre's handleDeviceLost (OgreD3D11RenderSystem.cpp
    // :1583-1622). notifyDeviceLost (1594) releases the window's back buffer
    // and then its swap chain (OgreD3D11RenderWindow.cpp:440-444, 230-232,
    // 452-458); notifyDeviceRestored (1608) creates the swap chain and then
    // the back buffer (446-450). So whenever the window has no swap chain it
    // also has no back buffer, and a throw with the back buffer gone would
    // leave the next frame's _beginUpdate on a null swap chain: it fails
    // closed. A throw while the back buffer is there (before 1594, or after
    // 1608) is rethrown as stock, unless the render target view is missing:
    // it is created after the back buffer (OgreD3D11RenderWindow.cpp:160-170),
    // so a throw between them leaves a half-restored window, which fails
    // closed as well. windowQueried false means the window could not be
    // asked, so the state is unknown and it fails closed too.
    inline bool DeviceLostThrowFailsClosed(bool windowQueried, bool hasBackBuffer, bool hasRenderTargetView)
    {
        return !windowQueried || !hasBackBuffer || !hasRenderTargetView;
    }
}
}
