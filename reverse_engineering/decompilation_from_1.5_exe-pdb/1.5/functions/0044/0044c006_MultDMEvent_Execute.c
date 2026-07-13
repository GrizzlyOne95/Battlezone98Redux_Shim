/*
 * Entry: 0044c006
 * Name: MultDMEvent::Execute
 * Namespace: MultDMEvent
 * Signature: void Execute(MultDMEvent * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __thiscall MultDMEvent::Execute(MultDMEvent *this)

{
  ulong *puVar1;
  float fVar2;
  bool bVar3;
  ushort uVar4;
  DWORD DVar5;
  ulong uVar6;
  uint uVar7;
  float *pfVar8;
  int iVar9;
  float fVar10;
  ushort uVar11;
  undefined2 *puVar12;
  undefined2 local_1c;
  long local_1a;
  float local_14;
  float local_c;
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  DVar5 = Get_TimeNow();
  uVar6 = Get_Time_Long();
  if ((Net::TimeLimit < 1) && (cockpitTimer.show != false)) {
    uVar7 = uVar6 / 1000;
    if (uVar7 + 2 < this->dwLastTime) {
      this->dwLastTime = uVar7 - 1;
    }
    if (this->dwLastTime < uVar7) {
      cockpitTimer.frac = 1.0;
      cockpitTimer.warn = 0x7fffffff;
      cockpitTimer.alert = 0x7fffffff;
      cockpitTimer.countdown = false;
      cockpitTimer.active = true;
      cockpitTimer.hours = true;
      cockpitTimer.timer = uVar7;
      this->dwLastTime = uVar7;
    }
  }
  if ((this->doing_king_of_the_hill != 0) && (GameObject::userObject != (GameObject *)0x0)) {
    local_14 = this->king_x;
    local_c = this->king_z;
    pfVar8 = (float *)(**(code **)(GameObject::userObject->_padding_ + 0xc))();
    if ((local_c - pfVar8[2]) * (local_c - pfVar8[2]) + (local_14 - *pfVar8) * (local_14 - *pfVar8)
        < (float)this->king_dist) {
      fVar10 = TimeStep();
      fVar10 = fVar10 + this->fTimeInZone;
      this->fTimeInZone = fVar10;
      fVar2 = this->fTimeInZoneLast + 1.0;
      if (fVar2 < fVar10 != (fVar2 == fVar10)) {
        Increment_Player_TimeInZone(fVar10 - this->fTimeInZoneLast);
        this->fTimeInZoneLast = this->fTimeInZone;
      }
    }
  }
  bVar3 = Net::GetHosting();
  if (!bVar3) {
    return;
  }
  if ((Net::KillLimit < 1) || (iVar9 = GetTotalKills(), iVar9 < Net::KillLimit)) {
    if (Net::TimeLimit < 1) {
      return;
    }
    if (this->starttimer != 0) {
      this->starttimer = 0;
      StartCockpitTimer(Net::TimeLimit * 0x3c,0x78,0x3c);
    }
    local_1a = cockpitTimer.timer;
    if (0 < cockpitTimer.timer) {
      puVar1 = &this->dwNextTimeLimit;
      if (DVar5 + 10000 < *puVar1) {
        *puVar1 = DVar5;
      }
      if (DVar5 <= *puVar1) {
        return;
      }
      *puVar1 = DVar5 + 10000;
      local_1c = 0x5450;
      uVar7 = 10;
      puVar12 = &local_1c;
      iVar9 = 0;
      uVar11 = 0;
      uVar4 = Net_GetMyPlayerID();
      Net::Send(Net::dp,uVar4,uVar11,iVar9,puVar12,uVar7);
      return;
    }
  }
  Net::bStopGame = true;
  if (NetEscapeUp == 0) {
    do_escape();
  }
  return;
}
