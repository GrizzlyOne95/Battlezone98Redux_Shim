/*
 * Entry: 004e0bd6
 * Name: NetPlayer::SendPing
 * Namespace: NetPlayer
 * Signature: void SendPing(NetPlayer * this, dp_s * param_1, ushort param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __thiscall NetPlayer::SendPing(NetPlayer *this,dp_s *param_1,ushort param_2)

{
  undefined2 local_28;
  ulong local_26;
  ulong local_22;
  ulong local_1e;
  ulong local_1a;
  int local_16;
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  local_28 = 0x5050;
  if (this->bClockInitialized == false) {
    local_22 = 0;
    local_16 = 0;
    local_1e = 0;
  }
  else {
    local_22 = this->offset;
    if (local_22 == 0) {
      local_16 = 1;
    }
    else {
      local_16 = this->BAddOffset;
    }
    local_1e = GetStartTime();
  }
  local_1a = GetAveragePingTime(this);
  local_26 = GetCurrentNetworkTime();
  Net::Send(param_1,param_2,this->playerId,0,&local_28,0x16);
  if (network_loggit != 0) {
    if (fp == (_iobuf *)0x0) {
      fp = (_iobuf *)fopen("j.log","w");
    }
    fprintf((FILE *)fp,"Send ping %d -> %d off = %ld dl = %ld mst = %ld\n",param_2,
            (uint)this->playerId,local_22,local_1a,local_1e);
  }
  this->dwPingReplies = this->dwPingReplies << 1;
  return;
}
