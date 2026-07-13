/*
 * Entry: 004de7cc
 * Name: Net::SendSyncAckPacket
 * Namespace: Net
 * Signature: void SendSyncAckPacket(Net * this, ushort param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __thiscall Net::SendSyncAckPacket(Net *this,ushort param_1)

{
  undefined2 local_14 [6];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  local_14[0] = 0x414b;
  Send(dp,myPlayerID,param_1,0,local_14,2);
  return;
}
