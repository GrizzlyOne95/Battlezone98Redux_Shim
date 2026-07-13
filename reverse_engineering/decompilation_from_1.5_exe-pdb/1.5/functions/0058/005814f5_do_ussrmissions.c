/*
 * Entry: 005814f5
 * Name: do_ussrmissions
 * Namespace: Global
 * Signature: int do_ussrmissions(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl do_ussrmissions(void)

{
  int iVar1;
  
  iVar1 = Shell_DialogBoxParam(shell_hInstance,(char *)0x77,shell_hwnd,UssrMissionsDlgProc,0);
  return iVar1;
}
