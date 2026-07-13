/*
 * Entry: 00568ffe
 * Name: do_shell
 * Namespace: Global
 * Signature: int do_shell(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl do_shell(void)

{
  int iVar1;
  
  system_on = GetPrivateProfileIntA("Config","System",system_on,shellCfgName);
  times_on = GetPrivateProfileIntA("Config","Times",times_on,shellCfgName);
  colors_on = GetPrivateProfileIntA("Config","Colors",colors_on,shellCfgName);
  LoadChatColors();
  iVar1 = Shell_DialogBoxParam(shell_hInstance,(char *)0x67,shell_hwnd,ShellDlgProc,0);
  return iVar1;
}
