/*
 * Entry: 00553e75
 * Name: do_error
 * Namespace: Global
 * Signature: void do_error(HWND__ * param_1, char * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __cdecl do_error(HWND__ *param_1,char *param_2)

{
  char local_408 [1024];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  _vsnprintf(local_408,0x400,param_2,&stack0x0000000c);
  EnableWindow((HWND)param_1,0);
  ErrorDlgMessage = local_408;
  Shell_DialogBoxParam(shell_hInstance,(char *)0x84,shell_hwnd,ErrorDlgProc,0);
  EnableWindow((HWND)param_1,1);
  return;
}
