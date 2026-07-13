/*
 * Entry: 005722c8
 * Name: do_license
 * Namespace: Global
 * Signature: int do_license(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl do_license(void)

{
  int iVar1;
  
  iVar1 = Shell_DialogBoxParam(shell_hInstance,(char *)0x121,shell_hwnd,LicenseDlgProc,0);
  return iVar1;
}
