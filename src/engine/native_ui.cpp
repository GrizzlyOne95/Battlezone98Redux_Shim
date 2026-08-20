// OpenShim native Redux UI framework.
//
// Callers own logical surfaces/widgets by opaque handles while Redux owns the
// actual cUI objects through its screen child tree. Native button callbacks are
// converted to queued SDK events instead of invoking companion/Lua code from
// cUI dispatch.

#include "native_ui.h"
#include "native_ui_validation.h"

#include "bzr_options_ui.h"
#include "openshim_sdk_v2.h"
#include "shim_log.h"

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <Windows.h>

#include <array>
#include <atomic>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <new>

namespace BZROpenShim
{
    namespace
    {
        constexpr uintptr_t kOptionsParentSingletonAddr = 0x009455C4;
        constexpr uintptr_t kMainScreenSingletonAddr = 0x0094551C;
        constexpr uintptr_t kMainScreenVtableAddr = 0x0089E178;
        constexpr uintptr_t kMainScreenOverlayVtableAddr = 0x008A0B94;
        constexpr uintptr_t kMainScreenCtorAddr = 0x0078E670;
        constexpr uintptr_t kMainScreenDtorAddr = 0x0078ECA0;
        constexpr size_t kMainScreenDetourLen = 10;
        constexpr uint32_t kInternalMainMenuHostValue =
            NativeUiValidation::kMainMenuHost;
        constexpr uint64_t kMainMenuDiagnosticActionId = 0x4D4D50524F424501ull; // MainMenu probe v1
        constexpr size_t kUiViewChildBeginOffset = 0x12C;
        constexpr size_t kUiViewChildEndOffset = 0x130;
        constexpr size_t kUiViewNameOffset = 0x20;
        constexpr size_t kMaxSurfacesPerHostLifetime = 16;
        constexpr size_t kMaxWidgetsPerHostLifetime = 128;
        constexpr size_t kMaxActionSlotsPerHostLifetime = 64;

        enum class NativeWidgetKind : uint32_t
        {
            None = 0,
            Label = 1,
            Button = 2,
        };

        struct SurfaceRecord
        {
            bool allocated = false;
            bool live = false;
            bool visible = true;
            OpenShimUiHandle handle = OPENSHIM_UI_INVALID_HANDLE;
            OpenShimUiHost host = OpenShimUiHost::None;
            void* screen = nullptr;
            void* parent = nullptr;
            DWORD ownerThreadId = 0;
            uint64_t hostGeneration = 0;
            uint64_t hostFingerprint = 0;
            char name[64] = {};
        };

        struct WidgetRecord
        {
            bool allocated = false;
            bool requestedVisible = true;
            OpenShimUiHandle handle = OPENSHIM_UI_INVALID_HANDLE;
            OpenShimUiHandle surface = OPENSHIM_UI_INVALID_HANDLE;
            NativeWidgetKind kind = NativeWidgetKind::None;
            void* native = nullptr;
            int actionSlot = -1;
            char name[64] = {};
        };

        struct ActionSlot
        {
            bool allocated = false;
            OpenShimUiHandle widget = OPENSHIM_UI_INVALID_HANDLE;
            uint64_t actionId = 0;
        };

        SRWLOCK g_NativeUiLock = SRWLOCK_INIT;
        std::array<SurfaceRecord, kMaxSurfacesPerHostLifetime> g_Surfaces = {};
        std::array<WidgetRecord, kMaxWidgetsPerHostLifetime> g_Widgets = {};
        std::array<ActionSlot, kMaxActionSlotsPerHostLifetime> g_ActionSlots = {};
        OpenShimUiHandle g_NextHandle = 1;
        OpenShimUiHost g_CurrentHost = OpenShimUiHost::None;
        void* g_CurrentScreen = nullptr;
        void* g_CurrentParent = nullptr;
        ptrdiff_t g_CurrentBaselineChildCount = -1;
        uint64_t g_CurrentHostGeneration = 0;
        uint64_t g_CurrentHostFingerprint = 0;
        DWORD g_UiThreadId = 0;

        using FnMainScreenCtor = void* (__thiscall*)(void* self);
        using FnMainScreenDtor = void(__thiscall*)(void* self);
        InlineDetour32 g_MainScreenCtorDetour = {};
        InlineDetour32 g_MainScreenDtorDetour = {};
        FnMainScreenCtor g_MainScreenCtorOriginal = nullptr;
        FnMainScreenDtor g_MainScreenDtorOriginal = nullptr;
        bool g_MainMenuDiagnosticsEnabled = false;
        bool g_MainScreenHooksInstalled = false;
        bool g_MainScreenHookMismatchLogged = false;
        std::atomic<uint64_t> g_MainScreenGeneration{0};
        std::atomic<uint32_t> g_MainMenuDiagnosticHoverCount{0};
        std::atomic<uint32_t> g_MainMenuDiagnosticActionCount{0};
        OpenShimUiHandle g_MainMenuDiagnosticSurface = OPENSHIM_UI_INVALID_HANDLE;
        OpenShimUiHandle g_MainMenuDiagnosticButton = OPENSHIM_UI_INVALID_HANDLE;

        template <size_t N>
        void CopyText(char (&dest)[N], const char* source)
        {
            dest[0] = '\0';
            if (source && *source)
                strncpy_s(dest, N, source, _TRUNCATE);
        }

        bool IsFiniteRect(const OpenShimUiRect& rect)
        {
            return std::isfinite(rect.x) && std::isfinite(rect.y) &&
                   std::isfinite(rect.width) && std::isfinite(rect.height) &&
                   rect.width > 0.0f && rect.height > 0.0f;
        }

        bool IsOnForegroundGameUiThread()
        {
            HWND foreground = GetForegroundWindow();
            if (!foreground)
                return false;

            DWORD processId = 0;
            const DWORD threadId = GetWindowThreadProcessId(foreground, &processId);
            return processId == GetCurrentProcessId() &&
                   threadId != 0 && threadId == GetCurrentThreadId();
        }

        bool HasRequiredNativeUiBindings()
        {
            return IsCompatibleGameVersion() &&
                   g_BzrFn_ButtonCtor &&
                   g_BzrFn_LabelCtor &&
                   g_BzrFn_AddChild &&
                   g_BzrFn_SetOnClick &&
                   g_BzrFn_SetOnHover &&
                   g_BzrFn_UiSetActive &&
                   g_BzrFn_SetButtonLabel &&
                   g_BzrFn_SetTooltip;
        }

        ptrdiff_t ReadUiChildCount(void* view)
        {
            if (!view)
                return -1;

            __try
            {
                auto* const bytes = reinterpret_cast<uint8_t*>(view);
                void** const begin =
                    *reinterpret_cast<void***>(bytes + kUiViewChildBeginOffset);
                void** const end =
                    *reinterpret_cast<void***>(bytes + kUiViewChildEndOffset);
                if (!begin || !end || begin > end || (end - begin) >= 256)
                    return -1;
                return end - begin;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return -1;
            }
        }

        bool UiNameEquals(void* object, const char* expected)
        {
            if (!object || !expected)
                return false;

            const size_t expectedLength = std::strlen(expected);
            if (expectedLength >= 128)
                return false;

            __try
            {
                const auto* const name =
                    reinterpret_cast<const uint8_t*>(object) + kUiViewNameOffset;
                for (size_t index = 0; index < expectedLength; ++index)
                {
                    if (name[index] != static_cast<uint8_t>(expected[index]))
                        return false;
                }
                return name[expectedLength] == 0;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        uint64_t HashFingerprintBytes(uint64_t hash, const void* bytes, size_t length)
        {
            constexpr uint64_t kFnvPrime = 1099511628211ull;
            const auto* cursor = static_cast<const uint8_t*>(bytes);
            for (size_t index = 0; index < length; ++index)
            {
                hash ^= cursor[index];
                hash *= kFnvPrime;
            }
            return hash;
        }

        bool ResolveMainMenuHost(void*& outScreen,
                                 void*& outParent,
                                 ptrdiff_t& outChildCount,
                                 uint64_t& outFingerprint,
                                 uint64_t& outGeneration)
        {
            outScreen = nullptr;
            outParent = nullptr;
            outChildCount = -1;
            outFingerprint = 0;
            outGeneration = 0;
            if (!g_MainMenuDiagnosticsEnabled || !IsCompatibleGameVersion())
                return false;

            constexpr const char* kRequiredChildren[] =
            {
                "ExitGame_MainScreen",
                "Options_MainScreen",
                "Mods",
                "SinglePlayer_MainScreen",
                "MultiPlayer_MainScreen",
                "ViewCredits_MainScreen",
                "Replay Intro_MainScreen",
            };

            __try
            {
                void* const screen = *reinterpret_cast<void**>(kMainScreenSingletonAddr);
                if (!screen || *reinterpret_cast<uintptr_t*>(screen) != kMainScreenVtableAddr)
                    return false;

                auto* const screenBytes = reinterpret_cast<uint8_t*>(screen);
                void** const begin =
                    *reinterpret_cast<void***>(screenBytes + kUiViewChildBeginOffset);
                void** const end =
                    *reinterpret_cast<void***>(screenBytes + kUiViewChildEndOffset);
                if (!begin || !end || begin >= end || (end - begin) >= 64)
                    return false;

                void* overlay = nullptr;
                size_t overlayMatches = 0;
                for (void** slot = begin; slot != end; ++slot)
                {
                    if (UiNameEquals(*slot, "MainScreen_Overlay"))
                    {
                        overlay = *slot;
                        ++overlayMatches;
                    }
                }
                if (overlayMatches != 1 || !overlay ||
                    *reinterpret_cast<uintptr_t*>(overlay) != kMainScreenOverlayVtableAddr)
                {
                    return false;
                }

                auto* const overlayBytes = reinterpret_cast<uint8_t*>(overlay);
                void** const childBegin =
                    *reinterpret_cast<void***>(overlayBytes + kUiViewChildBeginOffset);
                void** const childEnd =
                    *reinterpret_cast<void***>(overlayBytes + kUiViewChildEndOffset);
                if (!childBegin || !childEnd || childBegin >= childEnd ||
                    (childEnd - childBegin) >= 128)
                {
                    return false;
                }

                std::array<size_t, std::size(kRequiredChildren)> matches = {};
                uint64_t fingerprint = 1469598103934665603ull;
                fingerprint = HashFingerprintBytes(fingerprint, &screen, sizeof(screen));
                fingerprint = HashFingerprintBytes(fingerprint, &overlay, sizeof(overlay));
                for (void** slot = childBegin; slot != childEnd; ++slot)
                {
                    for (size_t required = 0; required < std::size(kRequiredChildren); ++required)
                    {
                        if (!UiNameEquals(*slot, kRequiredChildren[required]))
                            continue;
                        ++matches[required];
                        fingerprint = HashFingerprintBytes(fingerprint, slot, sizeof(*slot));
                        fingerprint = HashFingerprintBytes(
                            fingerprint,
                            kRequiredChildren[required],
                            std::strlen(kRequiredChildren[required]));
                    }
                }
                for (const size_t matchCount : matches)
                {
                    if (matchCount != 1)
                        return false;
                }

                const uint64_t generation = g_MainScreenGeneration.load();
                if (generation == 0)
                    return false;

                outScreen = screen;
                outParent = overlay;
                outChildCount = childEnd - childBegin;
                outFingerprint = fingerprint;
                outGeneration = generation;
                return true;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }
        }

        bool ResolveOptionsParentHost(void*& outScreen,
                                      void*& outParent,
                                      ptrdiff_t& outChildCount)
        {
            outScreen = nullptr;
            outParent = nullptr;
            outChildCount = -1;
            if (!IsCompatibleGameVersion())
                return false;

            __try
            {
                void* const screen = *reinterpret_cast<void**>(kOptionsParentSingletonAddr);
                if (!screen)
                    return false;

                auto* const screenBytes = reinterpret_cast<uint8_t*>(screen);
                void** const begin =
                    *reinterpret_cast<void***>(screenBytes + kUiViewChildBeginOffset);
                void** const end =
                    *reinterpret_cast<void***>(screenBytes + kUiViewChildEndOffset);
                if (!begin || !end || begin >= end || (end - begin) >= 64)
                    return false;

                for (void** slot = begin; slot != end; ++slot)
                {
                    void* const child = *slot;
                    if (!child)
                        continue;

                    auto* const childBytes = reinterpret_cast<uint8_t*>(child);
                    const char* const name =
                        reinterpret_cast<const char*>(childBytes + kUiViewNameOffset);
                    if (std::strncmp(name, "Middle_Overlay", sizeof("Middle_Overlay")) == 0)
                    {
                        const ptrdiff_t childCount = ReadUiChildCount(child);
                        if (childCount < 0)
                            return false;
                        outScreen = screen;
                        outParent = child;
                        outChildCount = childCount;
                        return true;
                    }
                }
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                return false;
            }

            // Never guess another parent. Parenting to a full-bleed frame view
            // can reorder cUI input dispatch and starve stock controls.
            return false;
        }

        bool ResolveHost(OpenShimUiHost host,
                         void*& outScreen,
                         void*& outParent,
                         ptrdiff_t& outChildCount,
                         uint64_t& outFingerprint,
                         uint64_t& outGeneration)
        {
            outFingerprint = 0;
            outGeneration = 0;
            switch (host)
            {
            case OpenShimUiHost::OptionsParent:
                if (!ResolveOptionsParentHost(outScreen, outParent, outChildCount))
                    return false;
                outFingerprint =
                    static_cast<uint64_t>(reinterpret_cast<uintptr_t>(outScreen)) << 32 |
                    static_cast<uint64_t>(reinterpret_cast<uintptr_t>(outParent));
                return true;
            default:
                if (static_cast<uint32_t>(host) == kInternalMainMenuHostValue)
                {
                    return ResolveMainMenuHost(outScreen,
                                               outParent,
                                               outChildCount,
                                               outFingerprint,
                                               outGeneration);
                }
                outScreen = nullptr;
                outParent = nullptr;
                outChildCount = -1;
                return false;
            }
        }

        size_t CountAllocatedWidgetsForCurrentHost()
        {
            size_t count = 0;
            for (const WidgetRecord& widget : g_Widgets)
            {
                if (widget.allocated)
                    ++count;
            }
            return count;
        }

        void ResetRecordsForNewHostLocked(OpenShimUiHost host,
                                          void* screen,
                                          void* parent,
                                          ptrdiff_t baselineChildCount,
                                          uint64_t fingerprint,
                                          uint64_t generation)
        {
            g_Surfaces = {};
            g_Widgets = {};
            g_ActionSlots = {};
            g_CurrentHost = host;
            g_CurrentScreen = screen;
            g_CurrentParent = parent;
            g_CurrentBaselineChildCount = baselineChildCount;
            g_CurrentHostFingerprint = fingerprint;
            g_CurrentHostGeneration = generation;
            g_UiThreadId = GetCurrentThreadId();
        }

        bool CurrentHostFingerprintMatches(ptrdiff_t currentChildCount,
                                           uint64_t fingerprint,
                                           uint64_t generation)
        {
            NativeUiValidation::HostIdentity identity = {};
            identity.host = static_cast<uint32_t>(g_CurrentHost);
            identity.screen = reinterpret_cast<uintptr_t>(g_CurrentScreen);
            identity.parent = reinterpret_cast<uintptr_t>(g_CurrentParent);
            identity.baselineChildCount = g_CurrentBaselineChildCount;
            identity.currentChildCount = currentChildCount;
            identity.allocatedWidgetCount = CountAllocatedWidgetsForCurrentHost();
            identity.fingerprint = fingerprint;
            identity.generation = generation;
            return fingerprint == g_CurrentHostFingerprint &&
                   generation == g_CurrentHostGeneration &&
                   NativeUiValidation::IsValidHostIdentity(
                       identity, g_MainMenuDiagnosticsEnabled);
        }

        bool PrepareHostLocked(OpenShimUiHost host,
                               void* screen,
                               void* parent,
                               ptrdiff_t childCount,
                               uint64_t fingerprint,
                               uint64_t generation)
        {
            const bool supportedHost = NativeUiValidation::IsSupportedHost(
                static_cast<uint32_t>(host), g_MainMenuDiagnosticsEnabled);
            if (!supportedHost ||
                !screen || !parent || childCount < 0)
            {
                return false;
            }

            if (g_CurrentHost != host ||
                g_CurrentScreen != screen ||
                g_CurrentParent != parent ||
                !CurrentHostFingerprintMatches(childCount, fingerprint, generation))
            {
                // Screen addresses are recycled by Redux. Child-count accounting
                // adds a generation fingerprint: after we inject N widgets, a
                // destroy/reconstruct at the same addresses returns to the stock
                // child count and therefore invalidates every stale handle.
                ResetRecordsForNewHostLocked(
                    host, screen, parent, childCount, fingerprint, generation);
            }

            return g_UiThreadId == GetCurrentThreadId();
        }

        bool IsSurfaceHostStillLive(const SurfaceRecord& surface)
        {
            void* screen = nullptr;
            void* parent = nullptr;
            ptrdiff_t childCount = -1;
            uint64_t fingerprint = 0;
            uint64_t generation = 0;
            if (!ResolveHost(surface.host,
                             screen,
                             parent,
                             childCount,
                             fingerprint,
                             generation))
            {
                return false;
            }

            NativeUiValidation::HostIdentity expected = {};
            expected.host = static_cast<uint32_t>(surface.host);
            expected.screen = reinterpret_cast<uintptr_t>(surface.screen);
            expected.parent = reinterpret_cast<uintptr_t>(surface.parent);
            expected.baselineChildCount = g_CurrentBaselineChildCount;
            expected.currentChildCount = childCount;
            expected.allocatedWidgetCount = CountAllocatedWidgetsForCurrentHost();
            expected.fingerprint = surface.hostFingerprint;
            expected.generation = surface.hostGeneration;

            NativeUiValidation::HostIdentity current = expected;
            current.screen = reinterpret_cast<uintptr_t>(screen);
            current.parent = reinterpret_cast<uintptr_t>(parent);
            current.fingerprint = fingerprint;
            current.generation = generation;
            return CurrentHostFingerprintMatches(childCount, fingerprint, generation) &&
                   NativeUiValidation::SameHostLifetime(
                       expected, current, g_MainMenuDiagnosticsEnabled);
        }

        OpenShimUiHandle AllocateHandleLocked()
        {
            OpenShimUiHandle result = g_NextHandle++;
            if (result == OPENSHIM_UI_INVALID_HANDLE)
                result = g_NextHandle++;
            return result;
        }

        SurfaceRecord* FindSurfaceLocked(OpenShimUiHandle handle)
        {
            if (handle == OPENSHIM_UI_INVALID_HANDLE)
                return nullptr;
            for (SurfaceRecord& surface : g_Surfaces)
            {
                if (surface.allocated && surface.handle == handle)
                    return &surface;
            }
            return nullptr;
        }

        WidgetRecord* FindWidgetLocked(OpenShimUiHandle handle)
        {
            if (handle == OPENSHIM_UI_INVALID_HANDLE)
                return nullptr;
            for (WidgetRecord& widget : g_Widgets)
            {
                if (widget.allocated && widget.handle == handle)
                    return &widget;
            }
            return nullptr;
        }

        SurfaceRecord* FindFreeSurfaceLocked()
        {
            for (SurfaceRecord& surface : g_Surfaces)
            {
                if (!surface.allocated || !surface.live)
                    return &surface;
            }
            return nullptr;
        }

        WidgetRecord* FindFreeWidgetLocked()
        {
            // Never recycle a widget record during one host lifetime. Released
            // engine children remain owned by Redux until that screen dies.
            for (WidgetRecord& widget : g_Widgets)
            {
                if (!widget.allocated)
                    return &widget;
            }
            return nullptr;
        }

        int FindFreeActionSlotLocked()
        {
            for (size_t index = 0; index < g_ActionSlots.size(); ++index)
            {
                if (!g_ActionSlots[index].allocated)
                    return static_cast<int>(index);
            }
            return -1;
        }

        void ReleaseReservedWidgetLocked(OpenShimUiHandle handle, int actionSlot)
        {
            WidgetRecord* const widget = FindWidgetLocked(handle);
            if (widget && !widget->native)
                *widget = {};
            if (actionSlot >= 0 &&
                static_cast<size_t>(actionSlot) < g_ActionSlots.size() &&
                g_ActionSlots[actionSlot].widget == handle)
            {
                g_ActionSlots[actionSlot] = {};
            }
        }

        void __cdecl NativeUiHoverNoop(void* /*param*/)
        {
        }

        void __cdecl NativeUiMainMenuDiagnosticHover(void* /*param*/)
        {
            const uint32_t count = g_MainMenuDiagnosticHoverCount.fetch_add(1) + 1;
            if (count == 1)
            {
                LogShimA(LogLevel::Info,
                         "native_ui_probe",
                         "MainMenu probe hover count=1");
            }
        }

        void DispatchActionSlot(size_t index)
        {
            if (index >= g_ActionSlots.size())
                return;

            ActionSlot action = {};
            WidgetRecord widget = {};
            SurfaceRecord surface = {};

            AcquireSRWLockShared(&g_NativeUiLock);
            action = g_ActionSlots[index];
            if (action.allocated)
            {
                WidgetRecord* const foundWidget = FindWidgetLocked(action.widget);
                if (foundWidget)
                {
                    widget = *foundWidget;
                    SurfaceRecord* const foundSurface = FindSurfaceLocked(widget.surface);
                    if (foundSurface)
                        surface = *foundSurface;
                }
            }
            ReleaseSRWLockShared(&g_NativeUiLock);

            if (!action.allocated || !widget.allocated || !widget.native ||
                widget.kind != NativeWidgetKind::Button ||
                !surface.live || !surface.visible || !widget.requestedVisible ||
                surface.ownerThreadId != GetCurrentThreadId() ||
                !IsSurfaceHostStillLive(surface))
            {
                return;
            }

            PublishOpenShimEvent(OpenShimEventType::NativeUiAction,
                                 action.actionId,
                                 0,
                                 widget.name);

            if (action.actionId == kMainMenuDiagnosticActionId)
            {
                const uint32_t count = g_MainMenuDiagnosticActionCount.fetch_add(1) + 1;
                AcquireSRWLockExclusive(&g_NativeUiLock);
                WidgetRecord* const liveWidget = FindWidgetLocked(widget.handle);
                if (liveWidget)
                    liveWidget->requestedVisible = false;
                ReleaseSRWLockExclusive(&g_NativeUiLock);
                g_BzrFn_UiSetActive(widget.native, 0);
                LogShimA(LogLevel::Info,
                         "native_ui_probe",
                         "MainMenu probe click/action count=%u; probe deactivated",
                         count);
            }
            LogShimA(LogLevel::Debug,
                     "native_ui",
                     "action surface=%llu widget=%llu action=%llu name=%s",
                     static_cast<unsigned long long>(surface.handle),
                     static_cast<unsigned long long>(widget.handle),
                     static_cast<unsigned long long>(action.actionId),
                     widget.name);
        }

#define OPENSHIM_UI_ACTION_THUNK(index) \
        static void __cdecl NativeUiActionThunk##index() { DispatchActionSlot(index); }

        OPENSHIM_UI_ACTION_THUNK(0)  OPENSHIM_UI_ACTION_THUNK(1)
        OPENSHIM_UI_ACTION_THUNK(2)  OPENSHIM_UI_ACTION_THUNK(3)
        OPENSHIM_UI_ACTION_THUNK(4)  OPENSHIM_UI_ACTION_THUNK(5)
        OPENSHIM_UI_ACTION_THUNK(6)  OPENSHIM_UI_ACTION_THUNK(7)
        OPENSHIM_UI_ACTION_THUNK(8)  OPENSHIM_UI_ACTION_THUNK(9)
        OPENSHIM_UI_ACTION_THUNK(10) OPENSHIM_UI_ACTION_THUNK(11)
        OPENSHIM_UI_ACTION_THUNK(12) OPENSHIM_UI_ACTION_THUNK(13)
        OPENSHIM_UI_ACTION_THUNK(14) OPENSHIM_UI_ACTION_THUNK(15)
        OPENSHIM_UI_ACTION_THUNK(16) OPENSHIM_UI_ACTION_THUNK(17)
        OPENSHIM_UI_ACTION_THUNK(18) OPENSHIM_UI_ACTION_THUNK(19)
        OPENSHIM_UI_ACTION_THUNK(20) OPENSHIM_UI_ACTION_THUNK(21)
        OPENSHIM_UI_ACTION_THUNK(22) OPENSHIM_UI_ACTION_THUNK(23)
        OPENSHIM_UI_ACTION_THUNK(24) OPENSHIM_UI_ACTION_THUNK(25)
        OPENSHIM_UI_ACTION_THUNK(26) OPENSHIM_UI_ACTION_THUNK(27)
        OPENSHIM_UI_ACTION_THUNK(28) OPENSHIM_UI_ACTION_THUNK(29)
        OPENSHIM_UI_ACTION_THUNK(30) OPENSHIM_UI_ACTION_THUNK(31)
        OPENSHIM_UI_ACTION_THUNK(32) OPENSHIM_UI_ACTION_THUNK(33)
        OPENSHIM_UI_ACTION_THUNK(34) OPENSHIM_UI_ACTION_THUNK(35)
        OPENSHIM_UI_ACTION_THUNK(36) OPENSHIM_UI_ACTION_THUNK(37)
        OPENSHIM_UI_ACTION_THUNK(38) OPENSHIM_UI_ACTION_THUNK(39)
        OPENSHIM_UI_ACTION_THUNK(40) OPENSHIM_UI_ACTION_THUNK(41)
        OPENSHIM_UI_ACTION_THUNK(42) OPENSHIM_UI_ACTION_THUNK(43)
        OPENSHIM_UI_ACTION_THUNK(44) OPENSHIM_UI_ACTION_THUNK(45)
        OPENSHIM_UI_ACTION_THUNK(46) OPENSHIM_UI_ACTION_THUNK(47)
        OPENSHIM_UI_ACTION_THUNK(48) OPENSHIM_UI_ACTION_THUNK(49)
        OPENSHIM_UI_ACTION_THUNK(50) OPENSHIM_UI_ACTION_THUNK(51)
        OPENSHIM_UI_ACTION_THUNK(52) OPENSHIM_UI_ACTION_THUNK(53)
        OPENSHIM_UI_ACTION_THUNK(54) OPENSHIM_UI_ACTION_THUNK(55)
        OPENSHIM_UI_ACTION_THUNK(56) OPENSHIM_UI_ACTION_THUNK(57)
        OPENSHIM_UI_ACTION_THUNK(58) OPENSHIM_UI_ACTION_THUNK(59)
        OPENSHIM_UI_ACTION_THUNK(60) OPENSHIM_UI_ACTION_THUNK(61)
        OPENSHIM_UI_ACTION_THUNK(62) OPENSHIM_UI_ACTION_THUNK(63)

#undef OPENSHIM_UI_ACTION_THUNK

        static void* const kActionThunks[kMaxActionSlotsPerHostLifetime] =
        {
            reinterpret_cast<void*>(NativeUiActionThunk0),  reinterpret_cast<void*>(NativeUiActionThunk1),
            reinterpret_cast<void*>(NativeUiActionThunk2),  reinterpret_cast<void*>(NativeUiActionThunk3),
            reinterpret_cast<void*>(NativeUiActionThunk4),  reinterpret_cast<void*>(NativeUiActionThunk5),
            reinterpret_cast<void*>(NativeUiActionThunk6),  reinterpret_cast<void*>(NativeUiActionThunk7),
            reinterpret_cast<void*>(NativeUiActionThunk8),  reinterpret_cast<void*>(NativeUiActionThunk9),
            reinterpret_cast<void*>(NativeUiActionThunk10), reinterpret_cast<void*>(NativeUiActionThunk11),
            reinterpret_cast<void*>(NativeUiActionThunk12), reinterpret_cast<void*>(NativeUiActionThunk13),
            reinterpret_cast<void*>(NativeUiActionThunk14), reinterpret_cast<void*>(NativeUiActionThunk15),
            reinterpret_cast<void*>(NativeUiActionThunk16), reinterpret_cast<void*>(NativeUiActionThunk17),
            reinterpret_cast<void*>(NativeUiActionThunk18), reinterpret_cast<void*>(NativeUiActionThunk19),
            reinterpret_cast<void*>(NativeUiActionThunk20), reinterpret_cast<void*>(NativeUiActionThunk21),
            reinterpret_cast<void*>(NativeUiActionThunk22), reinterpret_cast<void*>(NativeUiActionThunk23),
            reinterpret_cast<void*>(NativeUiActionThunk24), reinterpret_cast<void*>(NativeUiActionThunk25),
            reinterpret_cast<void*>(NativeUiActionThunk26), reinterpret_cast<void*>(NativeUiActionThunk27),
            reinterpret_cast<void*>(NativeUiActionThunk28), reinterpret_cast<void*>(NativeUiActionThunk29),
            reinterpret_cast<void*>(NativeUiActionThunk30), reinterpret_cast<void*>(NativeUiActionThunk31),
            reinterpret_cast<void*>(NativeUiActionThunk32), reinterpret_cast<void*>(NativeUiActionThunk33),
            reinterpret_cast<void*>(NativeUiActionThunk34), reinterpret_cast<void*>(NativeUiActionThunk35),
            reinterpret_cast<void*>(NativeUiActionThunk36), reinterpret_cast<void*>(NativeUiActionThunk37),
            reinterpret_cast<void*>(NativeUiActionThunk38), reinterpret_cast<void*>(NativeUiActionThunk39),
            reinterpret_cast<void*>(NativeUiActionThunk40), reinterpret_cast<void*>(NativeUiActionThunk41),
            reinterpret_cast<void*>(NativeUiActionThunk42), reinterpret_cast<void*>(NativeUiActionThunk43),
            reinterpret_cast<void*>(NativeUiActionThunk44), reinterpret_cast<void*>(NativeUiActionThunk45),
            reinterpret_cast<void*>(NativeUiActionThunk46), reinterpret_cast<void*>(NativeUiActionThunk47),
            reinterpret_cast<void*>(NativeUiActionThunk48), reinterpret_cast<void*>(NativeUiActionThunk49),
            reinterpret_cast<void*>(NativeUiActionThunk50), reinterpret_cast<void*>(NativeUiActionThunk51),
            reinterpret_cast<void*>(NativeUiActionThunk52), reinterpret_cast<void*>(NativeUiActionThunk53),
            reinterpret_cast<void*>(NativeUiActionThunk54), reinterpret_cast<void*>(NativeUiActionThunk55),
            reinterpret_cast<void*>(NativeUiActionThunk56), reinterpret_cast<void*>(NativeUiActionThunk57),
            reinterpret_cast<void*>(NativeUiActionThunk58), reinterpret_cast<void*>(NativeUiActionThunk59),
            reinterpret_cast<void*>(NativeUiActionThunk60), reinterpret_cast<void*>(NativeUiActionThunk61),
            reinterpret_cast<void*>(NativeUiActionThunk62), reinterpret_cast<void*>(NativeUiActionThunk63),
        };

        uint8_t __cdecl ApiIsAvailable()
        {
            return HasRequiredNativeUiBindings() ? 1u : 0u;
        }

        OpenShimUiHandle __cdecl ApiCreateSurface(const OpenShimUiSurfaceDesc* desc)
        {
            if (!desc || desc->structSize < sizeof(OpenShimUiSurfaceDesc) ||
                desc->apiVersion != NATIVE_UI_API_V1 ||
                !HasRequiredNativeUiBindings() || !IsOnForegroundGameUiThread())
            {
                return OPENSHIM_UI_INVALID_HANDLE;
            }

            const OpenShimUiHost host = static_cast<OpenShimUiHost>(desc->host);
            void* screen = nullptr;
            void* parent = nullptr;
            ptrdiff_t childCount = -1;
            uint64_t fingerprint = 0;
            uint64_t generation = 0;
            if (!ResolveHost(host,
                             screen,
                             parent,
                             childCount,
                             fingerprint,
                             generation))
                return OPENSHIM_UI_INVALID_HANDLE;

            AcquireSRWLockExclusive(&g_NativeUiLock);
            if (!PrepareHostLocked(
                    host, screen, parent, childCount, fingerprint, generation))
            {
                ReleaseSRWLockExclusive(&g_NativeUiLock);
                return OPENSHIM_UI_INVALID_HANDLE;
            }

            SurfaceRecord* const slot = FindFreeSurfaceLocked();
            if (!slot)
            {
                ReleaseSRWLockExclusive(&g_NativeUiLock);
                return OPENSHIM_UI_INVALID_HANDLE;
            }

            *slot = {};
            slot->allocated = true;
            slot->live = true;
            slot->visible = true;
            slot->handle = AllocateHandleLocked();
            slot->host = host;
            slot->screen = screen;
            slot->parent = parent;
            slot->ownerThreadId = GetCurrentThreadId();
            slot->hostGeneration = generation;
            slot->hostFingerprint = fingerprint;
            CopyText(slot->name, desc->name);
            const OpenShimUiHandle handle = slot->handle;
            ReleaseSRWLockExclusive(&g_NativeUiLock);

            LogShimA(LogLevel::Info,
                     "native_ui",
                     "surface created handle=%llu host=%u screen=0x%p parent=0x%p generation=%llu fingerprint=0x%llX name=%s",
                     static_cast<unsigned long long>(handle),
                     static_cast<unsigned>(host),
                     screen,
                     parent,
                     static_cast<unsigned long long>(generation),
                     static_cast<unsigned long long>(fingerprint),
                     desc->name);
            return handle;
        }

        int32_t __cdecl ApiReleaseSurface(OpenShimUiHandle surfaceHandle)
        {
            if (!IsOnForegroundGameUiThread())
                return 0;

            std::array<void*, kMaxWidgetsPerHostLifetime> nativeViews = {};
            size_t nativeCount = 0;

            AcquireSRWLockExclusive(&g_NativeUiLock);
            SurfaceRecord* const surface = FindSurfaceLocked(surfaceHandle);
            if (!surface || !surface->live ||
                surface->ownerThreadId != GetCurrentThreadId() ||
                !IsSurfaceHostStillLive(*surface))
            {
                ReleaseSRWLockExclusive(&g_NativeUiLock);
                return 0;
            }

            surface->live = false;
            surface->visible = false;
            for (const WidgetRecord& widget : g_Widgets)
            {
                if (widget.allocated && widget.surface == surfaceHandle && widget.native &&
                    nativeCount < nativeViews.size())
                {
                    nativeViews[nativeCount++] = widget.native;
                }
            }
            ReleaseSRWLockExclusive(&g_NativeUiLock);

            for (size_t i = 0; i < nativeCount; ++i)
                g_BzrFn_UiSetActive(nativeViews[i], 0);
            return 1;
        }

        int32_t __cdecl ApiSetSurfaceVisible(OpenShimUiHandle surfaceHandle, uint8_t visible)
        {
            if (!IsOnForegroundGameUiThread())
                return 0;

            struct PendingVisibility
            {
                void* native = nullptr;
                uint8_t active = 0;
            };
            std::array<PendingVisibility, kMaxWidgetsPerHostLifetime> pending = {};
            size_t pendingCount = 0;

            AcquireSRWLockExclusive(&g_NativeUiLock);
            SurfaceRecord* const surface = FindSurfaceLocked(surfaceHandle);
            if (!surface || !surface->live ||
                surface->ownerThreadId != GetCurrentThreadId() ||
                !IsSurfaceHostStillLive(*surface))
            {
                ReleaseSRWLockExclusive(&g_NativeUiLock);
                return 0;
            }

            surface->visible = visible != 0;
            for (const WidgetRecord& widget : g_Widgets)
            {
                if (widget.allocated && widget.surface == surfaceHandle && widget.native &&
                    pendingCount < pending.size())
                {
                    pending[pendingCount].native = widget.native;
                    pending[pendingCount].active =
                        NativeUiValidation::EffectiveVisibility(
                            surface->live, surface->visible, widget.requestedVisible) ? 1u : 0u;
                    ++pendingCount;
                }
            }
            ReleaseSRWLockExclusive(&g_NativeUiLock);

            for (size_t i = 0; i < pendingCount; ++i)
                g_BzrFn_UiSetActive(pending[i].native, pending[i].active);
            return 1;
        }

        OpenShimUiHandle __cdecl ApiAddLabel(const OpenShimUiLabelDesc* desc)
        {
            if (!desc || desc->structSize < sizeof(OpenShimUiLabelDesc) ||
                desc->apiVersion != NATIVE_UI_API_V1 || !IsFiniteRect(desc->rect) ||
                !HasRequiredNativeUiBindings() || !IsOnForegroundGameUiThread())
            {
                return OPENSHIM_UI_INVALID_HANDLE;
            }

            SurfaceRecord surfaceCopy = {};
            OpenShimUiHandle handle = OPENSHIM_UI_INVALID_HANDLE;

            AcquireSRWLockExclusive(&g_NativeUiLock);
            SurfaceRecord* const surface = FindSurfaceLocked(desc->surface);
            WidgetRecord* const widgetSlot = FindFreeWidgetLocked();
            if (!surface || !surface->live || !widgetSlot ||
                surface->ownerThreadId != GetCurrentThreadId() ||
                !IsSurfaceHostStillLive(*surface))
            {
                ReleaseSRWLockExclusive(&g_NativeUiLock);
                return OPENSHIM_UI_INVALID_HANDLE;
            }

            surfaceCopy = *surface;
            handle = AllocateHandleLocked();
            *widgetSlot = {};
            widgetSlot->allocated = true;
            widgetSlot->requestedVisible = true;
            widgetSlot->handle = handle;
            widgetSlot->surface = desc->surface;
            widgetSlot->kind = NativeWidgetKind::Label;
            ReleaseSRWLockExclusive(&g_NativeUiLock);

            void* labelMem = ::operator new(kUiTextSize, std::nothrow);
            if (!labelMem)
            {
                AcquireSRWLockExclusive(&g_NativeUiLock);
                ReleaseReservedWidgetLocked(handle, -1);
                ReleaseSRWLockExclusive(&g_NativeUiLock);
                return OPENSHIM_UI_INVALID_HANDLE;
            }
            std::memset(labelMem, 0, kUiTextSize);

            char generatedName[64] = {};
            const char* objectName = desc->name;
            if (!objectName || !*objectName)
            {
                std::snprintf(generatedName, sizeof(generatedName),
                              "OpenShimNativeLabel_%llu",
                              static_cast<unsigned long long>(handle));
                objectName = generatedName;
            }

            void* const label = g_BzrFn_LabelCtor(labelMem,
                                                  objectName,
                                                  desc->rect.x,
                                                  desc->rect.y,
                                                  desc->rect.width,
                                                  desc->rect.height,
                                                  0x20,
                                                  surfaceCopy.parent,
                                                  0);
            if (!label)
            {
                AcquireSRWLockExclusive(&g_NativeUiLock);
                ReleaseReservedWidgetLocked(handle, -1);
                ReleaseSRWLockExclusive(&g_NativeUiLock);
                return OPENSHIM_UI_INVALID_HANDLE;
            }

            if (g_BzrFn_LabelState)
                g_BzrFn_LabelState(label, reinterpret_cast<void*>(1));
            g_BzrFn_AddChild(surfaceCopy.parent, label, 0);
            g_BzrFn_SetTooltip(label, desc->text);
            g_BzrFn_UiSetActive(
                label,
                NativeUiValidation::EffectiveVisibility(
                    surfaceCopy.live, surfaceCopy.visible, true) ? 1u : 0u);

            AcquireSRWLockExclusive(&g_NativeUiLock);
            WidgetRecord* const finalWidget = FindWidgetLocked(handle);
            if (!finalWidget)
            {
                ReleaseSRWLockExclusive(&g_NativeUiLock);
                g_BzrFn_UiSetActive(label, 0);
                return OPENSHIM_UI_INVALID_HANDLE;
            }
            finalWidget->native = label;
            CopyText(finalWidget->name, objectName);
            ReleaseSRWLockExclusive(&g_NativeUiLock);
            return handle;
        }

        OpenShimUiHandle __cdecl ApiAddButton(const OpenShimUiButtonDesc* desc)
        {
            if (!desc || desc->structSize < sizeof(OpenShimUiButtonDesc) ||
                desc->apiVersion != NATIVE_UI_API_V1 || !IsFiniteRect(desc->rect) ||
                !HasRequiredNativeUiBindings() || !IsOnForegroundGameUiThread())
            {
                return OPENSHIM_UI_INVALID_HANDLE;
            }

            SurfaceRecord surfaceCopy = {};
            OpenShimUiHandle handle = OPENSHIM_UI_INVALID_HANDLE;
            int actionSlot = -1;

            AcquireSRWLockExclusive(&g_NativeUiLock);
            SurfaceRecord* const surface = FindSurfaceLocked(desc->surface);
            WidgetRecord* const widgetSlot = FindFreeWidgetLocked();
            actionSlot = FindFreeActionSlotLocked();
            if (!surface || !surface->live || !widgetSlot || actionSlot < 0 ||
                surface->ownerThreadId != GetCurrentThreadId() ||
                !IsSurfaceHostStillLive(*surface))
            {
                ReleaseSRWLockExclusive(&g_NativeUiLock);
                return OPENSHIM_UI_INVALID_HANDLE;
            }

            surfaceCopy = *surface;
            handle = AllocateHandleLocked();
            *widgetSlot = {};
            widgetSlot->allocated = true;
            widgetSlot->requestedVisible = true;
            widgetSlot->handle = handle;
            widgetSlot->surface = desc->surface;
            widgetSlot->kind = NativeWidgetKind::Button;
            widgetSlot->actionSlot = actionSlot;
            g_ActionSlots[actionSlot].allocated = true;
            g_ActionSlots[actionSlot].widget = handle;
            g_ActionSlots[actionSlot].actionId = desc->actionId;
            ReleaseSRWLockExclusive(&g_NativeUiLock);

            void* buttonMem = ::operator new(kUiButtonSize, std::nothrow);
            if (!buttonMem)
            {
                AcquireSRWLockExclusive(&g_NativeUiLock);
                ReleaseReservedWidgetLocked(handle, actionSlot);
                ReleaseSRWLockExclusive(&g_NativeUiLock);
                return OPENSHIM_UI_INVALID_HANDLE;
            }
            std::memset(buttonMem, 0, kUiButtonSize);

            char generatedName[64] = {};
            const char* objectName = desc->name;
            if (!objectName || !*objectName)
            {
                std::snprintf(generatedName, sizeof(generatedName),
                              "OpenShimNativeButton_%llu",
                              static_cast<unsigned long long>(handle));
                objectName = generatedName;
            }

            void* const button = g_BzrFn_ButtonCtor(buttonMem,
                                                    objectName,
                                                    desc->rect.x,
                                                    desc->rect.y,
                                                    desc->rect.width,
                                                    desc->rect.height,
                                                    0x20,
                                                    surfaceCopy.parent,
                                                    0,
                                                    0);
            if (!button)
            {
                AcquireSRWLockExclusive(&g_NativeUiLock);
                ReleaseReservedWidgetLocked(handle, actionSlot);
                ReleaseSRWLockExclusive(&g_NativeUiLock);
                return OPENSHIM_UI_INVALID_HANDLE;
            }

            if (g_BzrFn_SetTextureOff) g_BzrFn_SetTextureOff(button, "mpcron.png");
            if (g_BzrFn_SetTextureOver) g_BzrFn_SetTextureOver(button, "mpcrclk.png");
            if (g_BzrFn_SetTextureOn) g_BzrFn_SetTextureOn(button, "mpcrclk.png");
            if (g_BzrFn_SetButtonTextScale) g_BzrFn_SetButtonTextScale(button, 0.85f);
            g_BzrFn_SetButtonLabel(button, desc->text);
            g_BzrFn_SetOnClick(button, kActionThunks[actionSlot]);
            g_BzrFn_SetOnHover(
                button,
                desc->actionId == kMainMenuDiagnosticActionId
                    ? reinterpret_cast<void*>(NativeUiMainMenuDiagnosticHover)
                    : reinterpret_cast<void*>(NativeUiHoverNoop));
            g_BzrFn_AddChild(surfaceCopy.parent, button, 0);
            g_BzrFn_UiSetActive(
                button,
                NativeUiValidation::EffectiveVisibility(
                    surfaceCopy.live, surfaceCopy.visible, true) ? 1u : 0u);

            AcquireSRWLockExclusive(&g_NativeUiLock);
            WidgetRecord* const finalWidget = FindWidgetLocked(handle);
            if (!finalWidget)
            {
                ReleaseSRWLockExclusive(&g_NativeUiLock);
                g_BzrFn_UiSetActive(button, 0);
                return OPENSHIM_UI_INVALID_HANDLE;
            }
            finalWidget->native = button;
            CopyText(finalWidget->name, objectName);
            ReleaseSRWLockExclusive(&g_NativeUiLock);
            return handle;
        }

        int32_t __cdecl ApiSetText(OpenShimUiHandle widgetHandle, const char* text)
        {
            if (!text || !IsOnForegroundGameUiThread())
                return 0;

            WidgetRecord widget = {};
            SurfaceRecord surface = {};
            AcquireSRWLockShared(&g_NativeUiLock);
            WidgetRecord* const foundWidget = FindWidgetLocked(widgetHandle);
            if (foundWidget)
            {
                widget = *foundWidget;
                SurfaceRecord* const foundSurface = FindSurfaceLocked(widget.surface);
                if (foundSurface)
                    surface = *foundSurface;
            }
            ReleaseSRWLockShared(&g_NativeUiLock);

            if (!widget.allocated || !widget.native || !surface.live ||
                surface.ownerThreadId != GetCurrentThreadId() ||
                !IsSurfaceHostStillLive(surface))
            {
                return 0;
            }

            switch (widget.kind)
            {
            case NativeWidgetKind::Label:
                g_BzrFn_SetTooltip(widget.native, text);
                if (g_BzrFn_LabelState)
                    g_BzrFn_LabelState(widget.native, reinterpret_cast<void*>(1));
                return 1;
            case NativeWidgetKind::Button:
                g_BzrFn_SetButtonLabel(widget.native, text);
                return 1;
            default:
                return 0;
            }
        }

        int32_t __cdecl ApiSetVisible(OpenShimUiHandle widgetHandle, uint8_t visible)
        {
            if (!IsOnForegroundGameUiThread())
                return 0;

            void* native = nullptr;
            uint8_t effective = 0;
            SurfaceRecord surface = {};

            AcquireSRWLockExclusive(&g_NativeUiLock);
            WidgetRecord* const widget = FindWidgetLocked(widgetHandle);
            if (widget)
            {
                SurfaceRecord* const foundSurface = FindSurfaceLocked(widget->surface);
                if (foundSurface)
                    surface = *foundSurface;
                widget->requestedVisible = visible != 0;
                native = widget->native;
                effective = NativeUiValidation::EffectiveVisibility(
                    surface.live, surface.visible, widget->requestedVisible) ? 1u : 0u;
            }
            ReleaseSRWLockExclusive(&g_NativeUiLock);

            if (!native || !surface.live ||
                surface.ownerThreadId != GetCurrentThreadId() ||
                !IsSurfaceHostStillLive(surface))
            {
                return 0;
            }

            g_BzrFn_UiSetActive(native, effective);
            return 1;
        }

        const OpenShimNativeUiApiV1& GetNativeUiApiTable()
        {
            static const OpenShimNativeUiApiV1 api = []
            {
                OpenShimNativeUiApiV1 value = {};
                value.structSize = sizeof(OpenShimNativeUiApiV1);
                value.apiVersion = NATIVE_UI_API_V1;
                value.isAvailable = ApiIsAvailable;
                value.createSurface = ApiCreateSurface;
                value.releaseSurface = ApiReleaseSurface;
                value.setSurfaceVisible = ApiSetSurfaceVisible;
                value.addLabel = ApiAddLabel;
                value.addButton = ApiAddButton;
                value.setText = ApiSetText;
                value.setVisible = ApiSetVisible;
                return value;
            }();
            return api;
        }

        void ResetMainMenuRecordsForLifetimeChange()
        {
            AcquireSRWLockExclusive(&g_NativeUiLock);
            if (static_cast<uint32_t>(g_CurrentHost) == kInternalMainMenuHostValue)
            {
                g_Surfaces = {};
                g_Widgets = {};
                g_ActionSlots = {};
                g_CurrentHost = OpenShimUiHost::None;
                g_CurrentScreen = nullptr;
                g_CurrentParent = nullptr;
                g_CurrentBaselineChildCount = -1;
                g_CurrentHostGeneration = 0;
                g_CurrentHostFingerprint = 0;
                g_UiThreadId = 0;
            }
            g_MainMenuDiagnosticSurface = OPENSHIM_UI_INVALID_HANDLE;
            g_MainMenuDiagnosticButton = OPENSHIM_UI_INVALID_HANDLE;
            ReleaseSRWLockExclusive(&g_NativeUiLock);
        }

        void OnMainScreenConstructed(void* screen)
        {
            const uint64_t generation = g_MainScreenGeneration.fetch_add(1) + 1;
            ResetMainMenuRecordsForLifetimeChange();
            g_MainMenuDiagnosticHoverCount.store(0);
            g_MainMenuDiagnosticActionCount.store(0);

            if (!g_MainMenuDiagnosticsEnabled || !screen)
                return;

            __try
            {
                if (*reinterpret_cast<void**>(kMainScreenSingletonAddr) != screen)
                {
                    LogShimA(LogLevel::Warn,
                             "native_ui_probe",
                             "MainScreen ctor generation=%llu singleton mismatch; probe not created",
                             static_cast<unsigned long long>(generation));
                    return;
                }
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                LogShimA(LogLevel::Warn,
                         "native_ui_probe",
                         "MainScreen ctor generation=%llu singleton unreadable; probe not created",
                         static_cast<unsigned long long>(generation));
                return;
            }

            OpenShimUiSurfaceDesc surface = {};
            surface.host = kInternalMainMenuHostValue;
            CopyText(surface.name, "MainMenuDiagnosticProbe");
            g_MainMenuDiagnosticSurface = ApiCreateSurface(&surface);
            if (g_MainMenuDiagnosticSurface == OPENSHIM_UI_INVALID_HANDLE)
            {
                LogShimA(LogLevel::Warn,
                         "native_ui_probe",
                         "MainScreen generation=%llu host validation failed; probe not created",
                         static_cast<unsigned long long>(generation));
                return;
            }

            OpenShimUiButtonDesc button = {};
            button.surface = g_MainMenuDiagnosticSurface;
            button.rect = {20.0f, 970.0f, 260.0f, 58.0f};
            button.actionId = kMainMenuDiagnosticActionId;
            CopyText(button.name, "OpenShim_MainMenuProbe");
            CopyText(button.text, "OPENSHIM PROBE");
            g_MainMenuDiagnosticButton = ApiAddButton(&button);
            if (g_MainMenuDiagnosticButton == OPENSHIM_UI_INVALID_HANDLE)
            {
                ApiReleaseSurface(g_MainMenuDiagnosticSurface);
                g_MainMenuDiagnosticSurface = OPENSHIM_UI_INVALID_HANDLE;
                LogShimA(LogLevel::Warn,
                         "native_ui_probe",
                         "MainScreen generation=%llu button creation failed; probe disabled",
                         static_cast<unsigned long long>(generation));
                return;
            }

            LogShimA(LogLevel::Info,
                     "native_ui_probe",
                     "MainMenu probe created generation=%llu surface=%llu button=%llu rect=(20,970,260,58)",
                     static_cast<unsigned long long>(generation),
                     static_cast<unsigned long long>(g_MainMenuDiagnosticSurface),
                     static_cast<unsigned long long>(g_MainMenuDiagnosticButton));
        }

        void OnMainScreenDestroyed(void* screen)
        {
            const uint64_t retiredGeneration = g_MainScreenGeneration.fetch_add(1);
            const uint32_t hoverCount = g_MainMenuDiagnosticHoverCount.load();
            const uint32_t actionCount = g_MainMenuDiagnosticActionCount.load();
            ResetMainMenuRecordsForLifetimeChange();
            LogShimA(LogLevel::Info,
                     "native_ui_probe",
                     "MainScreen destroyed screen=0x%p generation=%llu hoverCount=%u actionCount=%u; handles invalidated without deleting Redux children",
                     screen,
                     static_cast<unsigned long long>(retiredGeneration),
                     hoverCount,
                     actionCount);
        }

        void* __fastcall MainScreenCtorHook(void* self, void* /*edx*/)
        {
            void* screen = self;
            if (g_MainScreenCtorOriginal)
                screen = g_MainScreenCtorOriginal(self);
            OnMainScreenConstructed(screen);
            return screen;
        }

        void __fastcall MainScreenDtorHook(void* self, void* /*edx*/)
        {
            OnMainScreenDestroyed(self);
            if (g_MainScreenDtorOriginal)
                g_MainScreenDtorOriginal(self);
        }

        void InstallMainScreenDiagnosticHooks()
        {
            if (g_MainScreenHooksInstalled)
                return;

            const uint8_t expectedDtor[kMainScreenDetourLen] =
            {
                0x55, 0x8B, 0xEC, 0x6A, 0xFF,
                0x68, 0xC8, 0xE6, 0x85, 0x00,
            };
            const uint8_t expectedCtor[kMainScreenDetourLen] =
            {
                0x55, 0x8B, 0xEC, 0x6A, 0xFF,
                0x68, 0x54, 0xEC, 0x85, 0x00,
            };

            if (!ExpectedBytesMatchAt(kMainScreenDtorAddr, expectedDtor, sizeof(expectedDtor)) ||
                !ExpectedBytesMatchAt(kMainScreenCtorAddr, expectedCtor, sizeof(expectedCtor)))
            {
                if (!g_MainScreenHookMismatchLogged)
                {
                    LogShimA(LogLevel::Warn,
                             "native_ui_probe",
                             "MainScreen ctor/dtor bytes mismatch; diagnostic probe disabled");
                    g_MainScreenHookMismatchLogged = true;
                }
                return;
            }

            if (!InstallInlineDetour32(g_MainScreenDtorDetour,
                                       kMainScreenDtorAddr,
                                       reinterpret_cast<void*>(MainScreenDtorHook),
                                       kMainScreenDetourLen,
                                       expectedDtor,
                                       sizeof(expectedDtor)))
            {
                LogShimA(LogLevel::Warn,
                         "native_ui_probe",
                         "Failed installing MainScreen destructor hook; probe disabled");
                return;
            }
            g_MainScreenDtorOriginal =
                reinterpret_cast<FnMainScreenDtor>(g_MainScreenDtorDetour.trampoline);

            if (!InstallInlineDetour32(g_MainScreenCtorDetour,
                                       kMainScreenCtorAddr,
                                       reinterpret_cast<void*>(MainScreenCtorHook),
                                       kMainScreenDetourLen,
                                       expectedCtor,
                                       sizeof(expectedCtor)))
            {
                LogShimA(LogLevel::Warn,
                         "native_ui_probe",
                         "Failed installing MainScreen constructor hook; probe disabled");
                return;
            }
            g_MainScreenCtorOriginal =
                reinterpret_cast<FnMainScreenCtor>(g_MainScreenCtorDetour.trampoline);
            g_MainScreenHooksInstalled =
                g_MainScreenCtorOriginal != nullptr && g_MainScreenDtorOriginal != nullptr;
            if (g_MainScreenHooksInstalled)
            {
                LogShimA(LogLevel::Info,
                         "native_ui_probe",
                         "Installed opt-in MainScreen diagnostic lifetime hooks");
            }
        }
    }

    const OpenShimNativeUiApiV1* GetOpenShimNativeUiApi(uint32_t requestedVersion)
    {
        if (requestedVersion != 0 && requestedVersion != NATIVE_UI_API_V1)
            return nullptr;
        return &GetNativeUiApiTable();
    }

    void EnsureNativeUiMainMenuDiagnosticScaffold()
    {
        bool enabled = false;
        if (!TryGetUserConfigBool("NativeUiDiagnostics", "MainMenuProbe", enabled) ||
            !enabled || !IsCompatibleGameVersion())
        {
            return;
        }

        g_MainMenuDiagnosticsEnabled = true;
        InstallMainScreenDiagnosticHooks();
    }

    void ShutdownNativeUi()
    {
        AcquireSRWLockExclusive(&g_NativeUiLock);
        g_Surfaces = {};
        g_Widgets = {};
        g_ActionSlots = {};
        g_CurrentHost = OpenShimUiHost::None;
        g_CurrentScreen = nullptr;
        g_CurrentParent = nullptr;
        g_CurrentBaselineChildCount = -1;
        g_CurrentHostGeneration = 0;
        g_CurrentHostFingerprint = 0;
        g_UiThreadId = 0;
        g_MainMenuDiagnosticSurface = OPENSHIM_UI_INVALID_HANDLE;
        g_MainMenuDiagnosticButton = OPENSHIM_UI_INVALID_HANDLE;
        ReleaseSRWLockExclusive(&g_NativeUiLock);
    }
}
