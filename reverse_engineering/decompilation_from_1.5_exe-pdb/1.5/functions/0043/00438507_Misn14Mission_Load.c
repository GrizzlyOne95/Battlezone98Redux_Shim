/*
 * Entry: 00438507
 * Name: Misn14Mission::Load
 * Namespace: Misn14Mission
 * Signature: bool Load(Misn14Mission * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall Misn14Mission::Load(Misn14Mission *this,_iobuf *param_1)

{
  bool bVar1;
  int iVar2;
  AiMission *this_00;
  Misn14Mission_u_92 *pMVar3;
  Misn14Mission_u_64 *pMVar4;
  Misn14Mission_u_136 *pMVar5;
  
  if (missionSave) {
    pMVar4 = &this->field16_0x40;
    for (iVar2 = 6; iVar2 != 0; iVar2 = iVar2 + -1) {
      *(undefined4 *)pMVar4 = 0;
      pMVar4 = (Misn14Mission_u_64 *)((int)pMVar4 + 4);
    }
    pMVar3 = &this->field17_0x5c;
    for (iVar2 = 10; iVar2 != 0; iVar2 = iVar2 + -1) {
      (pMVar3->_s_0).camera_time = 99999.0;
      pMVar3 = (Misn14Mission_u_92 *)((int)pMVar3 + 4);
    }
    pMVar5 = &this->field18_0x88;
    for (iVar2 = 0x16; iVar2 != 0; iVar2 = iVar2 + -1) {
      (pMVar5->_s_0).beacon1 = 0;
      pMVar5 = (Misn14Mission_u_136 *)((int)pMVar5 + 4);
    }
    (this->field19_0xe4)._s_0.wave_count = 0;
    Setup(this);
    bVar1 = AiMission::Load(this_00,param_1);
    return bVar1;
  }
  bVar1 = ::in(param_1,(this->field16_0x40).b_array,0x18);
  if ((bVar1) && (bVar1 = ::in(param_1,(this->field17_0x5c).f_array,0x28), bVar1)) {
    bVar1 = true;
  }
  else {
    bVar1 = false;
  }
  pMVar3 = &this->field17_0x5c;
  iVar2 = 10;
  do {
    if ((pMVar3->_s_0).camera_time == 9999.0) {
      (pMVar3->_s_0).camera_time = 99999.0;
    }
    pMVar3 = (Misn14Mission_u_92 *)((int)pMVar3 + 4);
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  if ((((bVar1) && (bVar1 = ::in(param_1,(this->field18_0x88).h_array,0x58), bVar1)) &&
      (bVar1 = ::in(param_1,(this->field19_0xe4).i_array,4), bVar1)) &&
     (bVar1 = AiMission::Load((AiMission *)this,param_1), bVar1)) {
    return true;
  }
  return false;
}
