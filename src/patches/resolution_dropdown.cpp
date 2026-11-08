// Options screen: the Video resolution row opens a scrollable list.
//
// The graphics options screen (cUI_OptionsGraphics, ctor 0x007AF4A0) builds the
// resolution control as a cUI_Checklist (screen+0x154) that steps one value per
// click. This file detours that ctor, lets it finish (including the
// ResolutionListFilter trim), then:
//   1. builds a hidden cUI_Selectlist under the screen's widget parent
//      (screen+0x18C), just below the row, filled from the checklist items;
//   2. gives ONLY that checklist instance a private copy of the cUI_Checklist
//      vtable whose mouse-press slot (+0x20) is a wrapper. A left click on the
//      row toggles the list; every other event reaches the stock handler;
//   3. on a list pick, selects the item through the checklist's own
//      select-by-value function and then calls the checklist's change callback
//      (+0x1D8), exactly like a cycle click, and hides the list.
// The class vtable in the exe is never written. Any identity mismatch leaves
// the stock cycle control untouched.
//
// Config: [Graphics] ResolutionDropdown (default 1);
// OPENSHIM_DISABLE_RESOLUTION_DROPDOWN=1 turns it off.
// RE note: reverse_engineering/resolution_dropdown_20261107.md.
#include "resolution_dropdown.h"

#include "bool_token.h"
#include "bzr_options_ui.h"
#include "diagnostic_switch.h"
#include "hook_engine.h"
#include "shim_log.h"

#include <Windows.h>

#include <cstdint>
#include <cstring>
#include <new>
#include <string>

namespace BZROpenShim::Hooks
{
    bool VtableTypeNameMatches(uintptr_t vtableAddress, const char* expectedName);
    bool IsWidgetLiveChildOfParent(void* parent, void* widget);
}

namespace BZROpenShim
{
    namespace
    {
        constexpr const char* kComponent = "ResolutionDropdown";

        // cUI_OptionsGraphics.
        constexpr uint32_t kScreenChecklist = 0x154;
        constexpr uint32_t kScreenParent = 0x18C;
        // cUI_View: design-space ctor arguments (x, y, w, h) and the live
        // screen-space rect used by the hit test (x, y, w, h).
        constexpr uint32_t kViewDesignX = 0xEC;
        constexpr uint32_t kViewDesignY = 0xF0;
        constexpr uint32_t kViewDesignH = 0xF8;
        constexpr uint32_t kViewRectX = 0x04;
        constexpr uint32_t kViewRectY = 0x08;
        constexpr uint32_t kViewRectW = 0x0C;
        constexpr uint32_t kViewRectH = 0x10;
        constexpr uint32_t kViewChildren = 0x12C;       // vector<cUI_View*>
        constexpr uint32_t kViewClickable = 0x145;      // byte
        // cUI_Checklist.
        constexpr uint32_t kChecklistSelected = 0x1DC;  // int
        constexpr uint32_t kChecklistCallback = 0x1D8;  // void(void)
        constexpr uint32_t kChecklistEnabled = 0x1E0;   // byte
        constexpr uint32_t kChecklistItems = 0x1E4;     // vector<item*>
        constexpr uint32_t kItemTextSize = 0x40;        // item = {char text[0x40]; int value;}
        constexpr uint32_t kItemValue = 0x40;
        constexpr uint32_t kClickVtableSlot = 8;        // +0x20
        constexpr size_t kVtableDwords = 18;            // RTTI COL + 17 slots
        // cUI_Selectlist.
        constexpr uint32_t kListRows = 0x15C;           // vector<label*>
        constexpr uint32_t kListItems = 0x168;          // vector, 0x1C-byte elements
        constexpr uint32_t kListItemSize = 0x1C;
        constexpr uint32_t kListSetActiveSlot = 9;      // +0x24, void(__thiscall)(this, byte)

        constexpr uint32_t kListTextScale = 0x174;      // float, applied to every row label

        constexpr int kMaxItems = 64;
        constexpr int kMaxVisibleRows = 8;
        constexpr float kListWidth = 260.0f;
        // The ctor spaces rows by the font height times its scale argument, which
        // leaves no gap between lines at 1.0. Building at 1.5 and then setting
        // the text scale back to 1.0 keeps the wider spacing: row refresh and
        // SetItem re-apply +0x174 to the labels, the row positions stay.
        constexpr float kRowPitchScale = 1.5f;
        constexpr float kRowPitch = 27.0f;              // design units at kRowPitchScale
        constexpr float kBackdropPad = 8.0f;
        constexpr float kArrowGutter = 40.0f;           // page arrows sit at x - 35
        // Stock value captions ("8", "No") draw on a higher layer than any
        // injected widget, so nothing can cover them. The list opens in the
        // empty column right of the short values instead of over them.
        constexpr float kListOffsetX = 230.0f;
        constexpr uint32_t kButtonEnabled = 0x148;      // byte; 0 = skipped by the hit walk, still drawn
        // The ctor gives every row label filton.png (bright green) as its
        // selection texture; the colour argument is only a text-colour enum
        // (FUN_007cca20: anything but 0/1/2/4 is green). Green text on that
        // bar was unreadable, so the rows are retextured with the darker
        // OpenShim button fill.
        constexpr const char* kRowHighlightTexture = "uibtn.png";
        constexpr float kDesignW = 1440.0f;
        constexpr float kDesignH = 1080.0f;

        using FnCtor = void*(__thiscall*)(void* self);
        using FnClick = bool(__thiscall*)(void* self, int x, int y, int button);
        using FnSelectValue = void(__thiscall*)(void* self, int value);
        using FnThis = void(__thiscall*)(void* self);
        using FnSetActiveVirtual = void(__thiscall*)(void* self, uint8_t active);

        uint32_t g_CtorAddr = 0;
        uint32_t g_ClickAddr = 0;
        uint32_t g_SelectValueAddr = 0;
        uint32_t g_RefreshAddr = 0;
        uint32_t g_ScrollUpAddr = 0;
        uint32_t g_ScrollDownAddr = 0;

        InlineDetour32 g_Detour = {};
        FnCtor g_OriginalCtor = nullptr;
        bool g_Installed = false;
        bool g_StandDownLogged = false;
        bool g_Faulted = false;

        // Private vtable copy: [0] = RTTI COL, [1..17] = slots.
        uint32_t g_Vtable[kVtableDwords] = {};
        FnClick g_OriginalClick = nullptr;

        void* g_Screen = nullptr;
        void* g_Parent = nullptr;
        void* g_Checklist = nullptr;
        void* g_List = nullptr;
        void* g_Backdrop = nullptr;  // blackui.png panel drawn under the list
        void* g_Catcher = nullptr;   // invisible full-screen button: a click outside closes
        bool g_Open = false;

        uint8_t* Bytes(void* p) { return static_cast<uint8_t*>(p); }

        template <typename T>
        T Field(void* base, uint32_t offset)
        {
            return *reinterpret_cast<T*>(Bytes(base) + offset);
        }

        template <typename T>
        void SetField(void* base, uint32_t offset, T value)
        {
            *reinterpret_cast<T*>(Bytes(base) + offset) = value;
        }

        uintptr_t VPtr(void* object) { return Field<uintptr_t>(object, 0); }

        // Pointer-vector helpers (begin at +0, end at +4, 4-byte elements).
        int PtrVectorCount(void* vec)
        {
            const uint32_t begin = Field<uint32_t>(vec, 0);
            const uint32_t end = Field<uint32_t>(vec, 4);
            if (!begin || end < begin)
                return -1;
            return static_cast<int>((end - begin) / sizeof(void*));
        }

        void* PtrVectorAt(void* vec, int index)
        {
            return reinterpret_cast<void**>(Field<uint32_t>(vec, 0))[index];
        }

        // Called under SEH only.
        bool ChecklistItemAt(void* checklist, int index, const char*& text, int& value)
        {
            void* const vec = Bytes(checklist) + kChecklistItems;
            const int count = PtrVectorCount(vec);
            if (index < 0 || index >= count)
                return false;
            uint8_t* const item = Bytes(PtrVectorAt(vec, index));
            if (!item)
                return false;
            if (!std::memchr(item, 0, kItemTextSize))
                return false;
            text = reinterpret_cast<const char*>(item);
            value = *reinterpret_cast<int*>(item + kItemValue);
            return true;
        }

        void SetListActive(bool active)
        {
            const uint32_t* const vtable = reinterpret_cast<const uint32_t*>(VPtr(g_List));
            reinterpret_cast<FnSetActiveVirtual>(vtable[kListSetActiveSlot])(g_List, active ? 1 : 0);
            if (g_BzrFn_UiSetActive)
            {
                if (g_Backdrop)
                    g_BzrFn_UiSetActive(g_Backdrop, active ? 1 : 0);
                if (g_Catcher)
                    g_BzrFn_UiSetActive(g_Catcher, active ? 1 : 0);
            }
        }

        // "3840 x 2160 @ 32-bit colour" -> "3840 x 2160": every row has the same
        // depth, and the suffix only overflowed the row.
        void ShortLabel(const char* text, char (&out)[kItemTextSize])
        {
            size_t n = 0;
            while (n + 1 < sizeof(out) && text[n] && !(text[n] == ' ' && text[n + 1] == '@'))
            {
                out[n] = text[n];
                ++n;
            }
            out[n] = 0;
        }

        // True while the globals still describe the live screen: the checklist
        // is still a child of the parent, still carries our vtable copy, and so
        // is the list. Under SEH only.
        bool StateIsLive()
        {
            if (g_Faulted || !g_Screen || !g_Parent || !g_Checklist || !g_List)
                return false;
            if (VPtr(g_Checklist) != reinterpret_cast<uintptr_t>(&g_Vtable[1]))
                return false;
            return Hooks::IsWidgetLiveChildOfParent(g_Parent, g_Checklist) &&
                   Hooks::IsWidgetLiveChildOfParent(g_Parent, g_List);
        }

        void CloseList()
        {
            SetListActive(false);
            g_Open = false;
        }

        void OpenList()
        {
            void* const list = g_List;
            int selected = Field<int>(g_Checklist, kChecklistSelected);
            const int itemCount =
                static_cast<int>((Field<uint32_t>(list, kListItems + 4) - Field<uint32_t>(list, kListItems)) /
                                 kListItemSize);
            const int rows = PtrVectorCount(Bytes(list) + kListRows);
            if (selected < 0 || selected >= itemCount)
                selected = 0;
            int maxScroll = itemCount - rows;
            if (maxScroll < 0)
                maxScroll = 0;
            int scroll = selected - (rows > 0 ? rows / 2 : 0);
            if (scroll < 0)
                scroll = 0;
            if (scroll > maxScroll)
                scroll = maxScroll;
            SetField<int>(list, kUiSelectlistSelectedOffset, selected);
            SetField<int>(list, kUiSelectlistScrollOffset, scroll);
            reinterpret_cast<FnThis>(g_RefreshAddr)(list);
            SetListActive(true);
            g_Open = true;
        }

        // Left click on the row. Returns 1 when handled (list toggled), 0 to
        // fall through to the stock handler. Mirrors the stock guards: active
        // byte, enabled byte, hit rect, clickable byte.
        int HandleRowClick(void* self, int x, int y)
        {
            __try
            {
                if (!StateIsLive())
                    return 0;
                if (!Field<uint8_t>(self, kUiViewInputActiveOffset) || !Field<uint8_t>(self, kChecklistEnabled))
                    return 0;
                const float fx = static_cast<float>(x);
                const float fy = static_cast<float>(y);
                const float rx = Field<float>(self, kViewRectX);
                const float ry = Field<float>(self, kViewRectY);
                const float rw = Field<float>(self, kViewRectW);
                const float rh = Field<float>(self, kViewRectH);
                if (fx < rx || rx + rw < fx || fy < ry || ry + rh < fy)
                    return 0;
                if (!Field<uint8_t>(self, kViewClickable))
                    return 0;
                if (g_Open)
                    CloseList();
                else
                    OpenList();
                return 1;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                g_Faulted = true;
                LogShimA(LogLevel::Warn, kComponent,
                         "[ResDrop] row click faulted (0x%08X); resolution control back to stock",
                         static_cast<uint32_t>(GetExceptionCode()));
                return 0;
            }
        }

        bool __fastcall ClickWrapper(void* self, void* /*edx*/, int x, int y, int button)
        {
            if (button == 0 && self == g_Checklist && !g_Faulted && HandleRowClick(self, x, y))
                return true;
            return g_OriginalClick(self, x, y, button);
        }

        void __cdecl OnListPageUp()
        {
            __try
            {
                if (StateIsLive())
                    reinterpret_cast<FnThis>(g_ScrollUpAddr)(g_List);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                g_Faulted = true;
            }
        }

        void __cdecl OnListPageDown()
        {
            __try
            {
                if (StateIsLive())
                    reinterpret_cast<FnThis>(g_ScrollDownAddr)(g_List);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                g_Faulted = true;
            }
        }

        // void(void) callback the list calls after a row click set +0x14C.
        void __cdecl OnListSelect()
        {
            __try
            {
                if (!StateIsLive())
                    return;
                const int index = Field<int>(g_List, kUiSelectlistSelectedOffset);
                const char* text = nullptr;
                int value = 0;
                if (!ChecklistItemAt(g_Checklist, index, text, value))
                {
                    CloseList();
                    return;
                }
                reinterpret_cast<FnSelectValue>(g_SelectValueAddr)(g_Checklist, value);
                // Same follow-up as a cycle click: the stored change callback.
                const uint32_t callback = Field<uint32_t>(g_Checklist, kChecklistCallback);
                if (callback)
                    reinterpret_cast<void(__cdecl*)()>(callback)();
                CloseList();
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                g_Faulted = true;
                LogShimA(LogLevel::Warn, kComponent,
                         "[ResDrop] list select faulted (0x%08X); resolution control back to stock",
                         static_cast<uint32_t>(GetExceptionCode()));
            }
        }

        // While the list is open, a click anywhere outside it lands here.
        void __cdecl OnCatcherClick()
        {
            __try
            {
                if (g_Open && StateIsLive())
                    CloseList();
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                g_Faulted = true;
            }
        }

        // The engine calls a button's hover slot unconditionally; null crashes.
        void __cdecl OnCatcherHover(void* /*param*/) {}

        void LogStandDown(const char* reason)
        {
            // A stand-down after the backdrop was built must not leave it drawn.
            if (g_Backdrop && g_BzrFn_UiSetActive)
                g_BzrFn_UiSetActive(g_Backdrop, 0);
            if (g_StandDownLogged)
                return;
            g_StandDownLogged = true;
            LogShimA(LogLevel::Warn, kComponent, "[ResDrop] stands down: %s", reason);
        }

        // Runs after the stock ctor returned. Everything is validated before
        // anything is changed; the vtable swap is the last step.
        bool InjectDropdown(void* screen)
        {
            if (!g_BzrFn_SelectlistCtor || !g_BzrFn_SelectlistSetItem || !g_BzrFn_SelectlistSetOnSelect ||
                !g_BzrFn_AddChild)
            {
                LogStandDown("UI widget bindings unavailable");
                return false;
            }
            if (!Hooks::VtableTypeNameMatches(VPtr(screen), ".?AVcUI_OptionsGraphics@@"))
            {
                LogStandDown("screen vtable RTTI mismatch");
                return false;
            }
            void* const checklist = Field<void*>(screen, kScreenChecklist);
            void* const parent = Field<void*>(screen, kScreenParent);
            if (!checklist || !parent)
            {
                LogStandDown("screen has no checklist or parent");
                return false;
            }
            const uintptr_t checklistVtable = VPtr(checklist);
            if (!Hooks::VtableTypeNameMatches(checklistVtable, ".?AVcUI_Checklist@@") ||
                reinterpret_cast<const uint32_t*>(checklistVtable)[kClickVtableSlot] != g_ClickAddr)
            {
                LogStandDown("checklist vtable or click slot mismatch");
                return false;
            }
            if (!Hooks::IsWidgetLiveChildOfParent(parent, checklist))
            {
                LogStandDown("checklist is not a child of the screen parent");
                return false;
            }

            const int itemCount = PtrVectorCount(Bytes(checklist) + kChecklistItems);
            if (itemCount < 2 || itemCount > kMaxItems)
            {
                LogStandDown("unexpected resolution item count");
                return false;
            }
            for (int i = 0; i < itemCount; ++i)
            {
                const char* text = nullptr;
                int value = 0;
                if (!ChecklistItemAt(checklist, i, text, value))
                {
                    LogStandDown("malformed checklist item");
                    return false;
                }
            }

            const float rowX = Field<float>(checklist, kViewDesignX);
            const float rowY = Field<float>(checklist, kViewDesignY);
            const float rowH = Field<float>(checklist, kViewDesignH);
            if (!(rowX >= 0.0f && rowX < kDesignW - kListWidth + 1.0f && rowY > 0.0f && rowY < kDesignH &&
                  rowH > 0.0f && rowH < 200.0f))
            {
                LogStandDown("resolution row rect out of the design space");
                return false;
            }
            float listX = rowX + kListOffsetX;
            if (listX + kListWidth + kBackdropPad > kDesignW)
                listX = kDesignW - kListWidth - kBackdropPad;
            const int visibleRows = itemCount < kMaxVisibleRows ? itemCount : kMaxVisibleRows;
            const bool scrollable = itemCount > visibleRows;
            const float listH = visibleRows * kRowPitch + 4.0f;
            float listY = rowY + rowH;
            if (listY + listH + kBackdropPad > kDesignH)
                listY = kDesignH - listH - kBackdropPad;

            // Backdrop before the list so it draws under it. A small overlay view
            // rasterizes nothing on this screen; a button-backed plate does
            // (same construction as the options rows). Its enabled byte is
            // cleared so the hit walk skips it and the rows above get the click.
            if (g_BzrFn_ButtonCtor && g_BzrFn_SetTextureOff && g_BzrFn_SetOnHover)
            {
                void* const backdropMem = ::operator new(kUiButtonSize, std::nothrow);
                if (backdropMem)
                {
                    std::memset(backdropMem, 0, kUiButtonSize);
                    const float gutter = scrollable ? kArrowGutter : 0.0f;
                    void* const backdrop = g_BzrFn_ButtonCtor(
                        backdropMem, "OpenShimResDropdownBg", listX - kBackdropPad - gutter, listY - kBackdropPad,
                        kListWidth + kBackdropPad * 2.0f + gutter, listH + kBackdropPad * 2.0f, 0x20, parent, 0, 0);
                    if (backdrop)
                    {
                        g_BzrFn_SetTextureOff(backdrop, "uiplate.png");
                        if (g_BzrFn_SetTextureOver)
                            g_BzrFn_SetTextureOver(backdrop, "uiplate.png");
                        if (g_BzrFn_SetTextureOn)
                            g_BzrFn_SetTextureOn(backdrop, "uiplate.png");
                        g_BzrFn_SetOnHover(backdrop, reinterpret_cast<void*>(OnCatcherHover));
                        if (g_BzrFn_SetButtonLabel)
                            g_BzrFn_SetButtonLabel(backdrop, "");
                        g_BzrFn_AddChild(parent, backdrop, 0);
                        SetField<uint8_t>(backdrop, kButtonEnabled, 0);
                        if (g_BzrFn_UiSetActive)
                            g_BzrFn_UiSetActive(backdrop, 0);
                        g_Backdrop = backdrop;
                    }
                }
            }

            void* const mem = ::operator new(kUiSelectlistSize, std::nothrow);
            if (!mem)
            {
                LogStandDown("allocation failed");
                return false;
            }
            std::memset(mem, 0, kUiSelectlistSize);
            // Colour and row scale are the values the lobby probe takes from
            // the stock lists. The arrows' callbacks are void(void), so they
            // reach this list through the global.
            void* const list = g_BzrFn_SelectlistCtor(mem, "OpenShimResDropdown", listX, listY, kListWidth,
                                                      listH, reinterpret_cast<void*>(OnListPageUp),
                                                      reinterpret_cast<void*>(OnListPageDown), 0, parent,
                                                      0xFF00FF00, kRowPitchScale);
            if (!list || !Hooks::VtableTypeNameMatches(VPtr(list), ".?AVcUI_Selectlist@@"))
            {
                // A half-built engine object is leaked, not freed.
                LogStandDown("selectlist ctor failed or RTTI mismatch");
                return false;
            }

            // Insert before the first child so the open list gets mouse events
            // ahead of the rows it covers (the parent walks children in order
            // and stops at the first handler).
            const int childCount = PtrVectorCount(Bytes(parent) + kViewChildren);
            void* const anchor = childCount > 0 ? PtrVectorAt(Bytes(parent) + kViewChildren, 0) : nullptr;
            g_BzrFn_AddChild(parent, list, reinterpret_cast<int>(anchor));
            SetField<float>(list, kListTextScale, 1.0f);
            if (g_BzrFn_SetTextureOff)
            {
                const int rows = PtrVectorCount(Bytes(list) + kListRows);
                for (int i = 0; i < rows && i < kMaxItems; ++i)
                {
                    if (void* const row = PtrVectorAt(Bytes(list) + kListRows, i))
                        g_BzrFn_SetTextureOff(row, kRowHighlightTexture);
                }
            }

            for (int i = 0; i < itemCount; ++i)
            {
                const char* text = nullptr;
                int value = 0;
                ChecklistItemAt(checklist, i, text, value);
                char label[kItemTextSize];
                ShortLabel(text, label);
                g_BzrFn_SelectlistSetItem(list, label, i, value);
            }

            // Catcher second in the child order: the open list sees a click first,
            // the catcher takes every other click on the screen.
            if (g_BzrFn_ButtonCtor && g_BzrFn_SetOnClick && g_BzrFn_SetOnHover && g_BzrFn_UiSetActive)
            {
                void* const catcherMem = ::operator new(kUiButtonSize, std::nothrow);
                if (catcherMem)
                {
                    std::memset(catcherMem, 0, kUiButtonSize);
                    void* const catcher = g_BzrFn_ButtonCtor(catcherMem, "OpenShimResDropdownCatcher", 0.0f, 0.0f,
                                                             kDesignW, kDesignH, 0x20, parent, 0, 0);
                    if (catcher)
                    {
                        g_BzrFn_SetOnHover(catcher, reinterpret_cast<void*>(OnCatcherHover));
                        g_BzrFn_SetOnClick(catcher, reinterpret_cast<void*>(OnCatcherClick));
                        // Inactive from the start: if a later engine call faults, a live
                        // full-screen catcher would swallow every click on the screen.
                        g_BzrFn_UiSetActive(catcher, 0);
                        const int count = PtrVectorCount(Bytes(parent) + kViewChildren);
                        void* const next = count > 1 ? PtrVectorAt(Bytes(parent) + kViewChildren, 1) : nullptr;
                        g_BzrFn_AddChild(parent, catcher, reinterpret_cast<int>(next));
                        g_Catcher = catcher;
                    }
                }
            }
            g_BzrFn_SelectlistSetOnSelect(list, reinterpret_cast<void*>(OnListSelect));

            // Hidden until the row is clicked.
            const uint32_t* const listVtable = reinterpret_cast<const uint32_t*>(VPtr(list));
            reinterpret_cast<FnSetActiveVirtual>(listVtable[kListSetActiveSlot])(list, 0);
            if (g_BzrFn_UiSetActive)
            {
                if (g_Backdrop)
                    g_BzrFn_UiSetActive(g_Backdrop, 0);
                if (g_Catcher)
                    g_BzrFn_UiSetActive(g_Catcher, 0);
            }

            // Last: take over this instance's click slot.
            std::memcpy(g_Vtable, reinterpret_cast<const void*>(checklistVtable - sizeof(uint32_t)),
                        sizeof(g_Vtable));
            g_OriginalClick = reinterpret_cast<FnClick>(g_Vtable[1 + kClickVtableSlot]);
            g_Vtable[1 + kClickVtableSlot] = reinterpret_cast<uint32_t>(&ClickWrapper);
            g_Screen = screen;
            g_Parent = parent;
            g_Checklist = checklist;
            g_List = list;
            g_Open = false;
            SetField<uint32_t>(checklist, 0, reinterpret_cast<uint32_t>(&g_Vtable[1]));
            return true;
        }

        void InjectGuarded(void* screen)
        {
            // A rebuilt screen replaces the previous one's state.
            g_Screen = g_Parent = g_Checklist = g_List = g_Backdrop = g_Catcher = nullptr;
            g_Open = false;
            __try
            {
                if (InjectDropdown(screen))
                    LogShimA(LogLevel::Info, kComponent, "[ResDrop] resolution dropdown attached");
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                g_Screen = g_Parent = g_Checklist = g_List = g_Backdrop = g_Catcher = nullptr;
                LogShimA(LogLevel::Warn, kComponent,
                         "[ResDrop] injection faulted (0x%08X); options screen left stock",
                         static_cast<uint32_t>(GetExceptionCode()));
            }
        }

        void* __fastcall CtorHook(void* self, void* /*edx*/)
        {
            void* const result = g_OriginalCtor(self);
            InjectGuarded(self);
            return result;
        }
    }

    void InitializeResolutionDropdown()
    {
        if (g_Installed)
            return;
        char value[16] = {};
        const DWORD n = GetEnvironmentVariableA("OPENSHIM_DISABLE_RESOLUTION_DROPDOWN", value,
                                                static_cast<DWORD>(sizeof(value)));
        if (n > 0 && n < sizeof(value) && BoolToken::IsTruthy(value, n))
            return;
        const std::string ini = DiagnosticSwitch::OpenShimIniPath();
        if (GetPrivateProfileIntA("Graphics", "ResolutionDropdown", 1, ini.c_str()) == 0)
            return;

        const HookEngine::EngineRow rows[] = {
            {"ResDropScreenCtor", &g_CtorAddr},
            {"ResDropChecklistClick", &g_ClickAddr},
            {"ResDropChecklistSelectValue", &g_SelectValueAddr},
            {"ResDropListRefresh", &g_RefreshAddr},
            {"ResDropListScrollUp", &g_ScrollUpAddr},
            {"ResDropListScrollDown", &g_ScrollDownAddr},
        };
        if (!HookEngine::BindEngineRows("ResolutionDropdown", rows, sizeof(rows) / sizeof(rows[0])))
            return;  // BindEngineRows logged the reason once.

        // push ebp; mov ebp,esp; push -1; push offset SEH handler. The row's
        // 23 guard bytes were just verified; the handler operand is read live.
        constexpr size_t kDetourLen = 10;
        uint8_t expected[kDetourLen] = {};
        std::memcpy(expected, reinterpret_cast<const void*>(static_cast<uintptr_t>(g_CtorAddr)), kDetourLen);
        if (!InstallInlineDetour32(g_Detour, g_CtorAddr, reinterpret_cast<void*>(CtorHook), kDetourLen, expected,
                                   kDetourLen))
        {
            LogShimA(LogLevel::Warn, kComponent, "[ResDrop] stands down: could not detour the screen ctor");
            return;
        }
        g_OriginalCtor = reinterpret_cast<FnCtor>(g_Detour.trampoline);
        if (!g_OriginalCtor)
            return;
        g_Installed = true;
        LogShimA(LogLevel::Info, kComponent, "[ResDrop] installed: graphics options ctor hooked");
    }
}
