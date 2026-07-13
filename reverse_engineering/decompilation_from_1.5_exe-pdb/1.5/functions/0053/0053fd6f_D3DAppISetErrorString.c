/*
 * Entry: 0053fd6f
 * Name: D3DAppISetErrorString
 * Namespace: Global
 * Signature: void D3DAppISetErrorString(char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __cdecl D3DAppISetErrorString(char *param_1)

{
  CHAR local_108 [256];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  local_108[0] = '\0';
  wvsprintfA(local_108,param_1,&stack0x00000008);
  lstrcatA(local_108,"\r\n");
  lstrcpyA(LastErrorString,local_108);
  return;
}
