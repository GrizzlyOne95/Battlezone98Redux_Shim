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
function Send-BZRClientText([int]$ProcessId, [string]$Text) {
    # No Activate here: WM_SETFOCUS clears the focused text field the
    # preceding click selected.
    $h = Get-BZRClientWindow $ProcessId
    foreach ($c in $Text.ToCharArray()) { [BZRWin.Native]::Char($h, $c) }
}
