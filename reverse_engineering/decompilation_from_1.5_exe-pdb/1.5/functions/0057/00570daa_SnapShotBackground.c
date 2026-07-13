/*
 * Entry: 00570daa
 * Name: SnapShotBackground
 * Namespace: Global
 * Signature: void SnapShotBackground(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl SnapShotBackground(void)

{
  HDC hDC;
  
  hDC = GetDC((HWND)shell_hwnd);
  ShellBitmap::BltBitmap(blankBg,(HDC__ *)hDC);
  ReleaseDC((HWND)shell_hwnd,hDC);
  return;
}
