#pragma once
// OpenShim's own shell screens.
//
// Redux builds every shell screen in one factory switch (ShellScreenFactory)
// and navigates by pushing screen ids onto a history vector. OpenShim screens
// join that system rather than drawing over a stock screen: the factory is
// detoured, and an id registered here is built by OpenShim the way a stock
// screen is built -- the stock "Top Screen" view (background and the four
// border views), a painted 1440x1080 centre panel, and stock widgets on top.
// The shell then treats it like any other screen: it fades in and out, sits
// on the history stack, answers Esc with Back, and is destroyed by the shell.
//
// Internal API. Not part of the plugin SDK.

#include <cstdint>

namespace BZROpenShim::ShellScreens
{
    // History ids for OpenShim screens. Stock ids stop at 0x2A; these sit far
    // above them so a later stock screen cannot collide.
    inline constexpr uint32_t kCustomScreenIdBase = 0x4F530000;  // 'OS' << 16
    inline constexpr uint32_t kCareerScreenId = kCustomScreenIdBase + 1;
    // OpenShim Options: the hub reached from the stock Options screen, and
    // one screen per settings category (base + category index).
    inline constexpr uint32_t kOptionsHubScreenId = kCustomScreenIdBase + 2;
    inline constexpr uint32_t kOptionsCategoryScreenIdBase = kCustomScreenIdBase + 0x10;

    // Adds the screen's children to `screen` (a constructed Top Screen). Runs
    // inside the shell's factory call, on the UI thread, which is the point
    // where stock screens build theirs; a widget built later, from a click,
    // draws its caption but not its frame. Returning false only logs: the
    // shell still gets the (partly built) screen, and Esc still leaves it.
    using BuildFn = bool (*)(void* screen);
    // Called as the shell destroys the screen, before its children go.
    using ClosedFn = void (*)(void* screen);

    struct ScreenDef
    {
        uint32_t id;
        const char* name;
        BuildFn build;
        ClosedFn closed;
    };

    // Binds the engine rows and installs the factory detour on first use.
    // False when this build cannot host OpenShim screens.
    bool RegisterScreen(const ScreenDef& def);
    bool IsAvailable();

    // Navigation from a button callback. `fromScreen` is the live screen the
    // click came from (any stock or OpenShim screen); its shell manager does
    // the transition, at the end of the frame, exactly as for a stock button.
    bool RequestScreen(void* fromScreen, uint32_t id);
    bool Back(void* fromScreen);

    // The live screen built for `id`, or null when it is not on screen.
    void* LiveScreen(uint32_t id);

    // ---- widget kit -------------------------------------------------------
    // Coordinates are the shell's 1440x1080 design space, as in the stock
    // screen constructors.
    struct Rect
    {
        float x, y, w, h;
    };

    struct ButtonSkin
    {
        const char* off;
        const char* over;
        const char* on;
    };

    // Stock skins.
    extern const ButtonSkin kSkinTopCorner;   // topcorner / topcrnhv / topcrnck, 342x77
    extern const ButtonSkin kSkinToMainMenu;  // tomnoff / tomnon / tomnclk, 369x68

    // Stock cUI_View flags for a screen-sized panel (as Middle_Overlay and the
    // other stock centre panels) and for controls.
    inline constexpr uint32_t kPanelFlags = 0x60;
    inline constexpr uint32_t kControlFlags = 0x20;
    // Large centred title text, as the stock "MISSION FAILED" header.
    inline constexpr uint32_t kTitleLabelFlags = 0x9020;

    // Every widget is constructed with a layout parent and then attached to a
    // container, which is how the stock constructors do it: the centre panel
    // is attached to the screen, and every control -- including the
    // top-corner Back button, whose layout parent is null -- is attached to
    // the centre panel.
    //
    // A view showing `texture` (may be null).
    void* AddPanel(void* container, void* layoutParent, const char* name, const Rect& r,
                   const char* texture, uint32_t flags = kPanelFlags);
    void* AddLabel(void* container, void* layoutParent, const char* name, const Rect& r,
                   const char* text, uint32_t flags = kControlFlags);
    // `textOffset` is the stock ctor's caption inset (28 for the top-corner
    // Back button). `onClick` is a plain cdecl callback, as stock buttons use.
    // `onHover` fires when the button's hover state changes, entering or
    // leaving, so it cannot tell which by itself; read CursorDesignPoint.
    // A skin whose `off` is null shows nothing at rest, like the stock option
    // buttons, which sit over slots painted into the panel.
    using HoverFn = void(__cdecl*)(void* param);
    void* AddButton(void* container, void* layoutParent, const char* name, const Rect& r,
                    const char* text, const ButtonSkin& skin, float textScale,
                    float textOffset, void(__cdecl* onClick)(), HoverFn onHover = nullptr);
    void SetLabelText(void* label, const char* text);

    // The cursor in the 1440x1080 design space of the centred content area
    // (the shell scales by client height and centres horizontally). False
    // when the game window is not in front.
    bool CursorDesignPoint(float& x, float& y);
    inline bool Contains(const Rect& r, float x, float y)
    {
        return x >= r.x && x < r.x + r.w && y >= r.y && y < r.y + r.h;
    }

    // True when an OpenShim UI texture is deployed (loose file in the
    // CustomWidgets folder). Screens fall back to the bare stock background
    // when their panel art is missing rather than showing a missing texture.
    bool IsTextureDeployed(const char* textureName);
}
