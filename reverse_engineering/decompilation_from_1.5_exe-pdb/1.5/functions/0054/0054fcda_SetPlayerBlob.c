/*
 * Entry: 0054fcda
 * Name: SetPlayerBlob
 * Namespace: Global
 * Signature: void SetPlayerBlob(dp_s * param_1, ushort param_2, char * param_3, int param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __cdecl SetPlayerBlob(dp_s *param_1,ushort param_2,char *param_3,int param_4)

{
  undefined2 in_stack_0000000a;
  undefined4 local_18;
  undefined4 uStack_14;
  undefined4 uStack_10;
  undefined4 uStack_c;
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  if (param_2 != 0xfa01) {
    uStack_14 = 0;
    uStack_10 = 0;
    uStack_c = 0;
    local_18 = param_4 & 0xff;
    if (param_3 != (char *)0x0) {
      strncpy((char *)((int)&local_18 + 1),param_3,0xe);
    }
    dpSetPlayerBlob(param_1,_param_2,&local_18,0x10);
  }
  return;
}
