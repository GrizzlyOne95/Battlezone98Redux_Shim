/*
 * Entry: 00554e78
 * Name: do_yesno
 * Namespace: Global
 * Signature: int do_yesno(HWND__ * param_1, char * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl do_yesno(HWND__ *param_1,char *param_2)

{
  int iVar1;
  
  YesNoMessage = param_2;
  EnableWindow((HWND)param_1,0);
  iVar1 = Shell_DialogBoxParam(shell_hInstance,(char *)0x84,shell_hwnd,YesNoDlgProc,0);
  EnableWindow((HWND)param_1,1);
  return iVar1;
}
