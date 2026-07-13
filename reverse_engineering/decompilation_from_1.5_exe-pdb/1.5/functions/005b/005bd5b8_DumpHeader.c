/*
 * Entry: 005bd5b8
 * Name: DumpHeader
 * Namespace: Global
 * Signature: void DumpHeader(DumpState * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __cdecl DumpHeader(DumpState *param_1)

{
  DumpState *pDVar1;
  undefined1 local_14 [12];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  pDVar1 = (DumpState *)local_14;
  luaU_header((char *)pDVar1);
  DumpBlock(local_14,0xc,pDVar1);
  return;
}
