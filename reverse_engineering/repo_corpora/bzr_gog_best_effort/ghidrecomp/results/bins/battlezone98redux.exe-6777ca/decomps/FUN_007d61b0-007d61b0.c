
void FUN_007d61b0(void)

{
  BOOL BVar1;
  HICON lParam;
  HMENU hMenu;
  UINT uIDEnableItem;
  UINT uEnable;
  
  if (DAT_0094670c == (HWND)0x0) {
    BVar1 = AllocConsole();
    if (BVar1 != 0) {
      DAT_0094670c = GetConsoleWindow();
      lParam = LoadIconA(DAT_02cecec0,(LPCSTR)0xc9);
      if (lParam != (HICON)0x0) {
        SendMessageA(DAT_0094670c,0x80,1,(LPARAM)lParam);
        SendMessageA(DAT_0094670c,0x80,0,(LPARAM)lParam);
      }
      FUN_00437450(&DAT_02cecee0);
      SetConsoleCtrlHandler((PHANDLER_ROUTINE)0x0,1);
      uEnable = 1;
      uIDEnableItem = 0xf060;
      hMenu = GetSystemMenu(DAT_0094670c,0);
      EnableMenuItem(hMenu,uIDEnableItem,uEnable);
    }
  }
  return;
}

