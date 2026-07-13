/*
 * Entry: 00553a8e
 * Name: do_phone
 * Namespace: Global
 * Signature: int do_phone(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl do_phone(void)

{
  int iVar1;
  
  iVar1 = Shell_DialogBoxParam(shell_hInstance,(char *)0x97,shell_hwnd,PhoneDlgProc,0);
  return iVar1;
}
