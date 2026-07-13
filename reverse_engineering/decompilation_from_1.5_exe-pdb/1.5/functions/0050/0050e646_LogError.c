/*
 * Entry: 0050e646
 * Name: LogError
 * Namespace: Global
 * Signature: void LogError(int param_1, char * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __cdecl LogError(int param_1,char *param_2)

{
  char local_108 [255];
  undefined1 local_9;
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  _vsnprintf(local_108,0xff,param_2,&stack0x0000000c);
  local_9 = 0;
  OutputDebugStringA(local_108);
  return;
}
