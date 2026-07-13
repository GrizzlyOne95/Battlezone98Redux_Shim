/*
 * Entry: 004235f0
 * Name: Misn05Mission::Load
 * Namespace: Misn05Mission
 * Signature: bool Load(Misn05Mission * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall Misn05Mission::Load(Misn05Mission *this,_iobuf *param_1)

{
  bool bVar1;
  int iVar2;
  AiMission *this_00;
  Misn05Mission_u_136 *pMVar3;
  Misn05Mission_u_300 *pMVar4;
  
  if (missionSave) {
    memset(&this->field16_0x40,0);
    pMVar3 = &this->field17_0x88;
    for (iVar2 = 0x28; iVar2 != 0; iVar2 = iVar2 + -1) {
      (pMVar3->_s_0).processtime = 99999.0;
      pMVar3 = (Misn05Mission_u_136 *)((int)pMVar3 + 4);
    }
    pMVar4 = &this->field18_0x12c;
    for (iVar2 = 0x41; iVar2 != 0; iVar2 = iVar2 + -1) {
      (pMVar4->_s_0).lemnos = 0;
      pMVar4 = (Misn05Mission_u_300 *)((int)pMVar4 + 4);
    }
    (this->field19_0x234)._s_0.attacksent = 0;
    Setup(this);
    bVar1 = AiMission::Load(this_00,param_1);
  }
  else {
    bVar1 = ::in(param_1,(this->field16_0x40).b_array,0x46);
    if ((((bVar1) && (bVar1 = ::in(param_1,(this->field17_0x88).f_array,0xa0), bVar1)) &&
        (bVar1 = ::in(param_1,(this->field18_0x12c).h_array,0x104), bVar1)) &&
       ((bVar1 = ::in(param_1,(this->field19_0x234).i_array,4), bVar1 &&
        (bVar1 = AiMission::Load((AiMission *)this,param_1), bVar1)))) {
      return true;
    }
    bVar1 = false;
  }
  return bVar1;
}
