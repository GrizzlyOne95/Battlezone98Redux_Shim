# Non-activating capture of the Battlezone window via PrintWindow (no focus, no input).
param([string]$Out, [int]$Count = 1, [int]$IntervalMs = 1000)
Add-Type -ReferencedAssemblies System.Drawing -TypeDefinition @'
using System; using System.Drawing; using System.Runtime.InteropServices; using System.Diagnostics; using System.Text;
public static class PW {
  [DllImport("user32.dll")] static extern bool SetProcessDPIAware();
  [DllImport("user32.dll")] static extern bool PrintWindow(IntPtr h, IntPtr dc, uint f);
  [DllImport("user32.dll")] static extern bool GetClientRect(IntPtr h, out RECT r);
  [DllImport("user32.dll")] static extern bool EnumWindows(EP cb, IntPtr l);
  delegate bool EP(IntPtr h, IntPtr l);
  [DllImport("user32.dll")] static extern uint GetWindowThreadProcessId(IntPtr h, out uint pid);
  [DllImport("user32.dll")] static extern bool IsWindowVisible(IntPtr h);
  [DllImport("user32.dll")] static extern int GetClassName(IntPtr h, StringBuilder s, int n);
  [StructLayout(LayoutKind.Sequential)] struct RECT { public int L,T,R,B; }
  public static string Shot(string path) {
    SetProcessDPIAware(); IntPtr found = IntPtr.Zero;
    var pids = new System.Collections.Generic.List<uint>();
    foreach (var p in Process.GetProcessesByName("battlezone98redux")) pids.Add((uint)p.Id);
    EnumWindows((h,l)=>{ uint pid; GetWindowThreadProcessId(h,out pid); if(pids.Contains(pid)&&IsWindowVisible(h)){ var sb=new StringBuilder(64); GetClassName(h,sb,64); RECT r; GetClientRect(h,out r); if(r.R>300) found=h; } return true; }, IntPtr.Zero);
    if (found==IntPtr.Zero) return "no window";
    RECT c; GetClientRect(found,out c);
    using (var bmp=new Bitmap(c.R,c.B)) { using (var g=Graphics.FromImage(bmp)) { IntPtr dc=g.GetHdc(); PrintWindow(found,dc,3); g.ReleaseHdc(dc);} bmp.Save(path); }
    return "ok "+c.R+"x"+c.B;
  }
}
'@
for ($i = 1; $i -le $Count; $i++) { $p = if ($Count -gt 1) { $Out -replace "\.png$", ("_{0:D2}.png" -f $i) } else { $Out }; [PW]::Shot($p) | Out-Null; Start-Sleep -Milliseconds $IntervalMs }
