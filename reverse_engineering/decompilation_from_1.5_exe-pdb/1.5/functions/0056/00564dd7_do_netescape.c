/*
 * Entry: 00564dd7
 * Name: do_netescape
 * Namespace: Global
 * Signature: int do_netescape(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl do_netescape(void)

{
  int iVar1;
  
  NetEscapeUp = 1;
  iVar1 = Shell_DialogBoxParam(shell_hInstance,(char *)0x7ee,shell_hwnd,NetEscapeDlgProc,0);
  NetEscapeUp = 0;
  return iVar1;
}
