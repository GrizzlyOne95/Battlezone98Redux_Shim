/*
 * Entry: 00573ef0
 * Name: do_credits
 * Namespace: Global
 * Signature: int do_credits(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl do_credits(void)

{
  int iVar1;
  
  iVar1 = Shell_DialogBoxParam(shell_hInstance,(char *)0x112,shell_hwnd,CreditsDlgProc,0);
  return iVar1;
}
