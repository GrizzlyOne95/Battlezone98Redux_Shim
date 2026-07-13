/*
 * Entry: 00571191
 * Name: GetScreenDPI
 * Namespace: Global
 * Signature: int GetScreenDPI(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl GetScreenDPI(void)

{
  HDC hdc;
  int iVar1;
  
  hdc = GetDC((HWND)0x0);
  iVar1 = 0x60;
  if (hdc != (HDC)0x0) {
    iVar1 = GetDeviceCaps(hdc,0x5a);
    ReleaseDC((HWND)0x0,hdc);
  }
  return iVar1;
}
