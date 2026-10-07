# Per-window capture and input for same-PC multiplayer clients.
#
# Targets one client window by process id, so it works while that window is
# unfocused and never touches the desktop's real cursor or keyboard. Used by
# BZRCoopSession.ps1; dot-source it to get the functions.

if (-not ('BZRWin.Native' -as [type])) {
    Add-Type -ReferencedAssemblies System.Drawing -TypeDefinition @'
using System;
using System.Drawing;
using System.Drawing.Imaging;
using System.Runtime.InteropServices;
using System.Text;
namespace BZRWin {
public static class Native {
    [DllImport("user32.dll")] static extern bool SetProcessDPIAware();
    // Window sizes and message coordinates must be physical pixels; the game
    // window is DPI-aware, so this process has to be too.
    static Native() { SetProcessDPIAware(); }
    [DllImport("user32.dll")] static extern bool EnumWindows(EnumProc cb, IntPtr lp);
    delegate bool EnumProc(IntPtr h, IntPtr lp);
    [DllImport("user32.dll")] static extern uint GetWindowThreadProcessId(IntPtr h, out uint pid);
    [DllImport("user32.dll")] static extern bool IsWindowVisible(IntPtr h);
    [DllImport("user32.dll", CharSet = CharSet.Unicode)] static extern int GetWindowText(IntPtr h, StringBuilder s, int n);
    [DllImport("user32.dll")] static extern bool GetClientRect(IntPtr h, out RECT r);
    [DllImport("user32.dll")] static extern bool PrintWindow(IntPtr h, IntPtr hdc, uint flags);
    [DllImport("user32.dll")] public static extern bool PostMessage(IntPtr h, uint msg, IntPtr w, IntPtr l);
    [DllImport("user32.dll")] public static extern bool SetWindowPos(IntPtr h, IntPtr after, int x, int y, int cx, int cy, uint flags);
    [StructLayout(LayoutKind.Sequential)] public struct RECT { public int L, T, R, B; }

    public static IntPtr MainWindow(uint pid) {
        IntPtr found = IntPtr.Zero;
        EnumWindows((h, lp) => {
            uint p; GetWindowThreadProcessId(h, out p);
            if (p == pid && IsWindowVisible(h)) {
                var sb = new StringBuilder(256); GetWindowText(h, sb, 256);
                if (sb.Length > 0) { found = h; return false; }
            }
            return true;
        }, IntPtr.Zero);
        return found;
    }

    public static string Title(IntPtr h) { var sb = new StringBuilder(256); GetWindowText(h, sb, 256); return sb.ToString(); }

    // PW_RENDERFULLCONTENT (2) captures DirectX swap chains on Windows 8.1+.
    public static void Capture(IntPtr h, string path) {
        RECT r; GetClientRect(h, out r);
        using (var bmp = new Bitmap(Math.Max(1, r.R - r.L), Math.Max(1, r.B - r.T), PixelFormat.Format32bppArgb))
        using (var g = Graphics.FromImage(bmp)) {
            IntPtr hdc = g.GetHdc();
            PrintWindow(h, hdc, 1 | 2);
            g.ReleaseHdc(hdc);
            bmp.Save(path, ImageFormat.Png);
        }
    }

    static IntPtr XY(int x, int y) { return (IntPtr)((y << 16) | (x & 0xFFFF)); }
    // The shell queues a screen change on click but only builds the new screen
    // while the app believes it is active; a background client keeps its old
    // screen until it next gets activation. Tell it so without taking focus.
    public static void Activate(IntPtr h) {
        PostMessage(h, 0x001C, (IntPtr)1, IntPtr.Zero);         // WM_ACTIVATEAPP
        PostMessage(h, 0x0006, (IntPtr)1, IntPtr.Zero);         // WM_ACTIVATE (WA_ACTIVE)
        PostMessage(h, 0x0007, IntPtr.Zero, IntPtr.Zero);       // WM_SETFOCUS
    }
    public static void Click(IntPtr h, int x, int y) {
        Activate(h);
        // The shell's corner buttons only take a press after a hover frame.
        PostMessage(h, 0x0200, IntPtr.Zero, XY(x, y));          // WM_MOUSEMOVE
        System.Threading.Thread.Sleep(150);
        PostMessage(h, 0x0200, IntPtr.Zero, XY(x, y));
        PostMessage(h, 0x0201, (IntPtr)1, XY(x, y));            // WM_LBUTTONDOWN
        System.Threading.Thread.Sleep(120);
        PostMessage(h, 0x0202, IntPtr.Zero, XY(x, y));          // WM_LBUTTONUP
    }
    public static void Key(IntPtr h, int vk) {
        Activate(h);
        PostMessage(h, 0x0100, (IntPtr)vk, (IntPtr)1);          // WM_KEYDOWN
        System.Threading.Thread.Sleep(40);
        PostMessage(h, 0x0101, (IntPtr)vk, unchecked((IntPtr)(int)0xC0000001)); // WM_KEYUP
    }
    public static void Char(IntPtr h, char c) { PostMessage(h, 0x0102, (IntPtr)c, (IntPtr)1); }

    // Real keyboard input for keys the game polls (GetAsyncKeyState, OIS /
    // DirectInput) rather than reads from window messages. SendInput has no
    // target window, so the client is brought to the foreground first and
    // nothing is sent unless that worked. The key is sent as a scan code
    // (DirectInput ignores VK-only injection) and held across several frames.
    // The previous foreground window gets focus back afterwards.
    [DllImport("user32.dll")] static extern IntPtr GetForegroundWindow();
    [DllImport("user32.dll")] static extern bool SetForegroundWindow(IntPtr h);
    [DllImport("user32.dll")] static extern bool BringWindowToTop(IntPtr h);
    [DllImport("user32.dll")] static extern bool AttachThreadInput(uint a, uint b, bool attach);
    [DllImport("kernel32.dll")] static extern uint GetCurrentThreadId();
    [DllImport("user32.dll")] static extern uint MapVirtualKey(uint code, uint mapType);
    [DllImport("user32.dll", SetLastError = true)] static extern uint SendInput(uint n, INPUT[] p, int cb);
    [StructLayout(LayoutKind.Sequential)] struct INPUT { public uint type; public InputUnion U; }
    // MOUSEINPUT is the largest member; SendInput rejects a short cbSize.
    [StructLayout(LayoutKind.Explicit)] struct InputUnion {
        [FieldOffset(0)] public MOUSEINPUT mi;
        [FieldOffset(0)] public KEYBDINPUT ki;
    }
    [StructLayout(LayoutKind.Sequential)] struct MOUSEINPUT { public int dx, dy; public uint mouseData, dwFlags, time; public IntPtr extra; }
    [StructLayout(LayoutKind.Sequential)] struct KEYBDINPUT { public ushort wVk, wScan; public uint dwFlags, time; public IntPtr extra; }

    static bool Foreground(IntPtr h) {
        if (GetForegroundWindow() == h) return true;
        uint pid;
        uint fg = GetWindowThreadProcessId(GetForegroundWindow(), out pid), me = GetCurrentThreadId();
        bool attached = fg != 0 && fg != me && AttachThreadInput(me, fg, true);
        BringWindowToTop(h);
        SetForegroundWindow(h);
        if (attached) AttachThreadInput(me, fg, false);
        return GetForegroundWindow() == h;
    }
    // withVk: also fill wVk and drop KEYEVENTF_SCANCODE, so Windows posts the
    // virtual key as given instead of deriving it from the scan code.
    static bool SendScan(int vk, bool up, bool withVk) {
        var i = new INPUT[1];
        i[0].type = 1;
        i[0].U.ki.wScan = (ushort)MapVirtualKey((uint)vk, 0);
        if (withVk) i[0].U.ki.wVk = (ushort)vk;
        uint flags = withVk ? 0u : 0x0008u;                      // KEYEVENTF_SCANCODE
        if ((vk >= 0x21 && vk <= 0x28) || vk == 0x2D || vk == 0x2E) flags |= 0x0001; // arrows/nav: EXTENDEDKEY
        if (up) flags |= 0x0002;                                 // KEYEVENTF_KEYUP
        i[0].U.ki.dwFlags = flags;
        return SendInput(1, i, Marshal.SizeOf(typeof(INPUT))) == 1;
    }
    public static string FocusedKey(IntPtr h, int vk, int holdMs, bool withVk) {
        IntPtr before = GetForegroundWindow();
        bool ok = false;
        for (int attempt = 0; attempt < 5 && !ok; attempt++) {
            ok = Foreground(h);
            if (!ok) System.Threading.Thread.Sleep(100);
        }
        if (!ok) return "not foreground";
        System.Threading.Thread.Sleep(60);                       // let the game see the activation
        bool down = SendScan(vk, false, withVk);
        System.Threading.Thread.Sleep(holdMs);
        bool upOk = SendScan(vk, true, withVk);
        System.Threading.Thread.Sleep(60);
        if (before != IntPtr.Zero && before != h) Foreground(before);
        return down && upOk ? "ok" : "SendInput failed err=" + Marshal.GetLastWin32Error();
    }
}
}
'@
}

function Get-BZRClientWindow([int]$ProcessId) {
    $h = [BZRWin.Native]::MainWindow([uint32]$ProcessId)
    if ($h -eq [IntPtr]::Zero) { throw "No visible window for pid $ProcessId" }
    $h
}
function Save-BZRClientCapture([int]$ProcessId, [string]$Path) {
    [BZRWin.Native]::Capture((Get-BZRClientWindow $ProcessId), $Path)
}
function Send-BZRClientClick([int]$ProcessId, [int]$X, [int]$Y) {
    [BZRWin.Native]::Click((Get-BZRClientWindow $ProcessId), $X, $Y)
}
function Send-BZRClientKey([int]$ProcessId, [int]$VirtualKey) {
    [BZRWin.Native]::Key((Get-BZRClientWindow $ProcessId), $VirtualKey)
}
function Send-BZRClientKeyFocused([int]$ProcessId, [int]$VirtualKey, [int]$HoldMs = 150, [switch]$WithVk) {
    # Takes the desktop foreground for the press; see FocusedKey.
    $r = [BZRWin.Native]::FocusedKey((Get-BZRClientWindow $ProcessId), $VirtualKey, $HoldMs, [bool]$WithVk)
    if ($r -ne 'ok') { throw "focused key 0x$('{0:X2}' -f $VirtualKey) to pid ${ProcessId}: $r" }
}
function Send-BZRClientText([int]$ProcessId, [string]$Text) {
    # No Activate here: WM_SETFOCUS clears the focused text field the
    # preceding click selected.
    $h = Get-BZRClientWindow $ProcessId
    foreach ($c in $Text.ToCharArray()) { [BZRWin.Native]::Char($h, $c) }
}
