/*
 * Entry: 0053fdcd
 * Name: dpf
 * Namespace: Global
 * Signature: void dpf(char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __cdecl dpf(char *param_1)

{
  int iVar1;
  va_list arglist;
  CHAR local_108 [256];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  lstrcpyA(local_108,"D3DApp: ");
  arglist = &stack0x00000008;
  iVar1 = lstrlenA(local_108);
  wvsprintfA(local_108 + iVar1,param_1,arglist);
  lstrcatA(local_108,"\r\n");
  OutputDebugStringA(local_108);
  return;
}
