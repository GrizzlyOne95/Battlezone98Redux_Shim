/*
 * Entry: 004ddb79
 * Name: Net::SendKill
 * Namespace: Net
 * Signature: void SendKill(ushort param_1, ushort param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __cdecl Net::SendKill(ushort param_1,ushort param_2,int param_3)

{
  undefined2 local_18;
  undefined1 local_16;
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  if (param_2 != 0xfa01) {
    local_18 = 0x4b50;
    local_16 = (undefined1)param_3;
    Send(dp,param_1,param_2,1,&local_18,3);
  }
  return;
}
