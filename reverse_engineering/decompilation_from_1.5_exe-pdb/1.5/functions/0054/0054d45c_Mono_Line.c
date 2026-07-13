/*
 * Entry: 0054d45c
 * Name: Mono_Line
 * Namespace: Global
 * Signature: void Mono_Line(long param_1, short param_2, short param_3, short param_4, char * param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __cdecl Mono_Line(long param_1,short param_2,short param_3,short param_4,char *param_5)

{
  char local_108 [256];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  _vsnprintf(local_108,0x5a,param_5,&stack0x00000018);
  Mono_Display(param_1,local_108,param_2,param_3,param_4);
  return;
}
