/*
 * Entry: 004788ba
 * Name: FindI76Instance
 * Namespace: Global
 * Signature: int FindI76Instance(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl FindI76Instance(void)

{
  HWND hWnd;
  
  hWnd = FindWindowA("Battlezone 1.5.2.27 Update 1",(LPCSTR)0x0);
  if (hWnd != (HWND)0x0) {
    ShowWindow(hWnd,9);
  }
  return (uint)(hWnd != (HWND)0x0);
}
