/*
 * Entry: 005549b3
 * Name: do_password
 * Namespace: Global
 * Signature: int do_password(HWND__ * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl do_password(HWND__ *param_1)

{
  int iVar1;
  
  EnableWindow((HWND)param_1,0);
  iVar1 = Shell_DialogBoxParam(shell_hInstance,(char *)0x9b,shell_hwnd,PasswordDlgProc,0);
  EnableWindow((HWND)param_1,1);
  return iVar1;
}
