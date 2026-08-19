// OpenShim native Redux UI framework.
//
// Callers own logical surfaces/widgets by opaque handles while Redux owns the
// actual cUI objects through its screen child tree. Native button callbacks are
// converted to queued SDK events instead of invoking companion/Lua code from
// cUI dispatch.

#include "native_ui.h"

#include "bzr_options_ui.h"
#include "openshim_sdk_v2.h"
#include "shim_log.h"

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <Windows.h>

#include <array>
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
        void* g_CurrentOptionsScreen = nullptr;
        void* g_CurrentOptionsParent = nullptr;
        ptrdiff_t g_CurrentOptionsBaselineChildCount = -1;
        DWORD g_UiThreadId = 0;

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
                         ptrdiff_t& outChildCount)
        {
            switch (host)
            {
            case OpenShimUiHost::OptionsParent:
                return ResolveOptionsParentHost(outScreen, outParent, outChildCount);
            default:
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

        void ResetRecordsForNewHostLocked(void* screen,
                                          void* parent,
                                          ptrdiff_t baselineChildCount)
        {
            g_Surfaces = {};
            g_Widgets = {};
            g_ActionSlots = {};
            g_CurrentOptionsScreen = screen;
            g_CurrentOptionsParent = parent;
            g_CurrentOptionsBaselineChildCount = baselineChildCount;
            g_UiThreadId = GetCurrentThreadId();
        }

        bool CurrentHostFingerprintMatches(ptrdiff_t currentChildCount)
        {
            if (g_CurrentOptionsBaselineChildCount < 0 || currentChildCount < 0)
                return false;
            const ptrdiff_t expected =
                g_CurrentOptionsBaselineChildCount +
                static_cast<ptrdiff_t>(CountAllocatedWidgetsForCurrentHost());
            return currentChildCount == expected;
        }

        bool PrepareHostLocked(OpenShimUiHost host,
                               void* screen,
                               void* parent,
                               ptrdiff_t childCount)
        {
            if (host != OpenShimUiHost::OptionsParent ||
                !screen || !parent || childCount < 0)
            {
                return false;
            }

            if (g_CurrentOptionsScreen != screen ||
                g_CurrentOptionsParent != parent ||
                !CurrentHostFingerprintMatches(childCount))
            {
                // Screen addresses are recycled by Redux. Child-count accounting
                // adds a generation fingerprint: after we inject N widgets, a
                // destroy/reconstruct at the same addresses returns to the stock
                // child count and therefore invalidates every stale handle.
                ResetRecordsForNewHostLocked(screen, parent, childCount);
            }

            return g_UiThreadId == GetCurrentThreadId();
        }

        bool IsSurfaceHostStillLive(const SurfaceRecord& surface)
        {
            void* screen = nullptr;
            void* parent = nullptr;
            ptrdiff_t childCount = -1;
            if (!ResolveHost(surface.host, screen, parent, childCount) ||
                screen != surface.screen || parent != surface.parent)
            {
                return false;
            }
            return CurrentHostFingerprintMatches(childCount);
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
            if (!ResolveHost(host, screen, parent, childCount))
                return OPENSHIM_UI_INVALID_HANDLE;

            AcquireSRWLockExclusive(&g_NativeUiLock);
            if (!PrepareHostLocked(host, screen, parent, childCount))
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
            CopyText(slot->name, desc->name);
            const OpenShimUiHandle handle = slot->handle;
            ReleaseSRWLockExclusive(&g_NativeUiLock);

            LogShimA(LogLevel::Info,
                     "native_ui",
                     "surface created handle=%llu host=%u screen=0x%p parent=0x%p name=%s",
                     static_cast<unsigned long long>(handle),
                     static_cast<unsigned>(host),
                     screen,
                     parent,
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
                        (surface->visible && widget.requestedVisible) ? 1u : 0u;
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
            g_BzrFn_UiSetActive(label, surfaceCopy.visible ? 1u : 0u);

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
            g_BzrFn_SetOnHover(button, reinterpret_cast<void*>(NativeUiHoverNoop));
            g_BzrFn_AddChild(surfaceCopy.parent, button, 0);
            g_BzrFn_UiSetActive(button, surfaceCopy.visible ? 1u : 0u);

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
                effective = (surface.live && surface.visible && widget->requestedVisible) ? 1u : 0u;
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
    }

    const OpenShimNativeUiApiV1* GetOpenShimNativeUiApi(uint32_t requestedVersion)
    {
        if (requestedVersion != 0 && requestedVersion != NATIVE_UI_API_V1)
            return nullptr;
        return &GetNativeUiApiTable();
    }

    void ShutdownNativeUi()
    {
        AcquireSRWLockExclusive(&g_NativeUiLock);
        g_Surfaces = {};
        g_Widgets = {};
        g_ActionSlots = {};
        g_CurrentOptionsScreen = nullptr;
        g_CurrentOptionsParent = nullptr;
        g_CurrentOptionsBaselineChildCount = -1;
        g_UiThreadId = 0;
        ReleaseSRWLockExclusive(&g_NativeUiLock);
    }
}
