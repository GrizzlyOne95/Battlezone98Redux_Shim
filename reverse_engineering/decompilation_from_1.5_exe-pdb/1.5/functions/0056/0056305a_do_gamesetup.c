/*
 * Entry: 0056305a
 * Name: do_gamesetup
 * Namespace: Global
 * Signature: int do_gamesetup(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

int __cdecl do_gamesetup(void)

{
  int iVar1;
  int iVar2;
  char *pcVar3;
  char *pcVar4;
  undefined1 local_138 [4];
  byte local_134;
  undefined4 local_110;
  HDC__ *local_10c;
  char local_108 [2];
  char acStack_106 [21];
  undefined1 local_f1 [57];
  undefined1 local_b8 [176];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)local_b8;
  iVar2 = 0;
  if (first != 0) {
    InitCommonControls();
  }
  local_10c = (HDC__ *)GetDC((HWND)shell_hwnd);
  first = 0;
  EnsurePalette();
  init_bitmap_dialog(local_10c);
  UnlockMouse();
  iVar1 = 0;
  do {
    pcVar3 = &sFlagFileName + iVar1;
    Net::pcFlagName[iVar1] = *pcVar3;
    iVar1 = iVar1 + 1;
  } while (*pcVar3 != '\0');
  iVar1 = dpCreate(&Net::dp,0,0,"freeze.dat");
  if (iVar1 == 0) {
    Net::bBroadcastOptimize = true;
    Net_SetHeat();
    Net::myPlayerID = 0xfa01;
    local_110 = 0x5f;
    dpGetSessionDesc(Net::dp,&dp_session_game,&local_110);
    dpEnumPlayersEx(Net::dp,0,dpEnumThePlayersCallback,0,0);
    dpGetCaps(Net::dp,local_138,1);
    if ((local_134 & 1) != 0) {
      Creator = true;
    }
    iVar2 = Shell_DialogBoxParam(shell_hInstance,(char *)0x7ed,shell_hwnd,NetGameDlgProc,0);
  }
  else {
    pcVar3 = "Heat Connection failed";
    pcVar4 = local_108;
    for (iVar1 = 5; iVar1 != 0; iVar1 = iVar1 + -1) {
      *(undefined4 *)pcVar4 = *(undefined4 *)pcVar3;
      pcVar3 = pcVar3 + 4;
      pcVar4 = pcVar4 + 4;
    }
    *(undefined2 *)pcVar4 = *(undefined2 *)pcVar3;
    pcVar4[2] = pcVar3[2];
    memset(local_f1,0,0xe9);
    read_text_label("multi_error","heat_failed",local_108);
    MessageBoxA((HWND)shell_hwnd,local_108,"Error",0x10);
  }
  LockMouse();
  clean_bitmap_dialog(local_10c);
  ReleaseDC((HWND)shell_hwnd,(HDC)local_10c);
  return iVar2;
}
