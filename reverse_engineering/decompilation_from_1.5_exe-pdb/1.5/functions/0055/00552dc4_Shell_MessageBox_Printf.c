/*
 * Entry: 00552dc4
 * Name: Shell_MessageBox_Printf
 * Namespace: Global
 * Signature: int Shell_MessageBox_Printf(uint param_1, char * param_2, char * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

int __cdecl Shell_MessageBox_Printf(uint param_1,char *param_2,char *param_3)

{
  char local_408 [1024];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  _vsnprintf(local_408,0x400,param_3,&stack0x00000010);
  return 0;
}
