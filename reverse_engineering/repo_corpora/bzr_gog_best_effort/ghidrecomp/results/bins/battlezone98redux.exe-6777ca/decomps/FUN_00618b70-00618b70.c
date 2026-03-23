
bool FUN_00618b70(void)

{
  HWND hWnd;
  
  hWnd = FindWindowA("Battlezone 98 Redux (2.2.301)",(LPCSTR)0x0);
  if (hWnd != (HWND)0x0) {
    ShowWindow(hWnd,9);
  }
  return hWnd != (HWND)0x0;
}

