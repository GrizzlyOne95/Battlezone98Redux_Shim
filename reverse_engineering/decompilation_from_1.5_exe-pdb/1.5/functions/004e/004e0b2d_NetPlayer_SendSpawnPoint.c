/*
 * Entry: 004e0b2d
 * Name: NetPlayer::SendSpawnPoint
 * Namespace: NetPlayer
 * Signature: void SendSpawnPoint(NetPlayer * this, dp_s * param_1, ushort param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __thiscall NetPlayer::SendSpawnPoint(NetPlayer *this,dp_s *param_1,ushort param_2)

{
  SpawnPoint *this_00;
  VECTOR_3D *pVVar1;
  undefined2 local_24;
  float local_22;
  float fStack_1e;
  float fStack_1a;
  uchar local_16;
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  if (this->SpawnPointer == (SpawnPoint *)0x0) {
    this_00 = SpawnPoint::GetSafest((uint)this->bTeamNumber);
    this->SpawnPointer = this_00;
    if (this_00 != (SpawnPoint *)0x0) {
      SpawnPoint::Assign(this_00,this);
    }
  }
  if (this->SpawnPointer != (SpawnPoint *)0x0) {
    local_24 = 0x5350;
    pVVar1 = SpawnPoint::GetLocation(this->SpawnPointer);
    local_16 = this->bTeamNumber;
    local_22 = pVVar1->x;
    fStack_1e = pVVar1->y;
    fStack_1a = pVVar1->z;
    Net::Send(param_1,param_2,this->playerId,1,&local_24,0x12);
    total_bytes_sent = total_bytes_sent + 0x12;
    total_msg_sent = total_msg_sent + 1;
  }
  return;
}
