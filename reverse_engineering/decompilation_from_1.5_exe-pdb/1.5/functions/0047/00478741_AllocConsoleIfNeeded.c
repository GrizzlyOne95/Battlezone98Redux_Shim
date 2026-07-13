/*
 * Entry: 00478741
 * Name: AllocConsoleIfNeeded
 * Namespace: Global
 * Signature: void AllocConsoleIfNeeded(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl AllocConsoleIfNeeded(void)

{
  BOOL BVar1;
  HMENU hMenu;
  UINT uIDEnableItem;
  UINT uEnable;
  
  if (console_hwnd == (HWND__ *)0x0) {
    BVar1 = AllocConsole();
    if (BVar1 != 0) {
      console_hwnd = (HWND__ *)GetConsoleWindow();
      SetForegroundWindow((HWND)Device.hwndApp);
      SetConsoleCtrlHandler((PHANDLER_ROUTINE)0x0,1);
      uEnable = 1;
      uIDEnableItem = 0xf060;
      hMenu = GetSystemMenu((HWND)console_hwnd,0);
      EnableMenuItem(hMenu,uIDEnableItem,uEnable);
    }
  }
  return;
}
