/*
 * Entry: 005712f0
 * Name: GetMCIError
 * Namespace: Global
 * Signature: void GetMCIError(ulong param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __cdecl GetMCIError(ulong param_1)

{
  CHAR local_88 [128];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  mciGetErrorStringA(param_1,local_88,0x80);
  return;
}
