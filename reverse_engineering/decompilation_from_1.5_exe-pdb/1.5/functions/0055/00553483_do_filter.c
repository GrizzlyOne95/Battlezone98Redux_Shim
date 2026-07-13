/*
 * Entry: 00553483
 * Name: do_filter
 * Namespace: Global
 * Signature: int do_filter(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl do_filter(void)

{
  int iVar1;
  
  iVar1 = Shell_DialogBoxParam(shell_hInstance,(char *)0x81d,shell_hwnd,FilterDlgProc,0);
  return iVar1;
}
