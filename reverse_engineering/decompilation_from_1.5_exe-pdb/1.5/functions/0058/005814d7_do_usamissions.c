/*
 * Entry: 005814d7
 * Name: do_usamissions
 * Namespace: Global
 * Signature: int do_usamissions(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl do_usamissions(void)

{
  int iVar1;
  
  iVar1 = Shell_DialogBoxParam(shell_hInstance,(char *)0x76,shell_hwnd,UsaMissionsDlgProc,0);
  return iVar1;
}
