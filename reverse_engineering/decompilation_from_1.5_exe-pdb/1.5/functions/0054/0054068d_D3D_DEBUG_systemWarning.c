/*
 * Entry: 0054068d
 * Name: D3D_DEBUG_systemWarning
 * Namespace: Global
 * Signature: void D3D_DEBUG_systemWarning(char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __cdecl D3D_DEBUG_systemWarning(char *param_1)

{
  char local_58 [80];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  _vsnprintf(local_58,0x50,param_1,&stack0x00000008);
  Trace(local_58);
  return;
}
