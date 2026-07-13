/*
 * Entry: 004df0aa
 * Name: Net::HandlePing
 * Namespace: Net
 * Signature: void HandlePing(Net * this, ushort param_1, ushort param_2, PING_PACKET * param_3, ulong param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __thiscall
Net::HandlePing(Net *this,ushort param_1,ushort param_2,PING_PACKET *param_3,ulong param_4)

{
  PING_PACKET *pPVar1;
  undefined2 local_1c;
  ulong local_1a;
  ulong local_16;
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  local_1c = 0x5250;
  local_16 = param_4;
  local_1a = param_3->master_send_time;
  if (myPlayerID != 0xfa01) {
    Send(dp,myPlayerID,param_1,0,&local_1c,10);
  }
  if (hosting == false) {
    pPVar1 = this->ping;
    SetClockOffsetAndStartTime(pPVar1->offset,pPVar1->BAddOffset,pPVar1->host_start_time);
  }
  return;
}
