/*
 * Entry: 0043abda
 * Name: Misn16Mission::Load
 * Namespace: Misn16Mission
 * Signature: bool Load(Misn16Mission * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall Misn16Mission::Load(Misn16Mission *this,_iobuf *param_1)

{
  bool bVar1;
  int iVar2;
  AiMission *this_00;
  Misn16Mission_u_72 *pMVar3;
  Misn16Mission_u_112 *pMVar4;
  
  if (missionSave) {
    *(undefined4 *)&this->field16_0x40 = 0;
    *(undefined2 *)((int)&this->field16_0x40 + 4) = 0;
    pMVar3 = &this->field17_0x48;
    for (iVar2 = 9; iVar2 != 0; iVar2 = iVar2 + -1) {
      (pMVar3->_s_0).next_reinforcement = 99999.0;
      pMVar3 = (Misn16Mission_u_72 *)((int)pMVar3 + 4);
    }
    pMVar4 = &this->field18_0x70;
    for (iVar2 = 0x15; iVar2 != 0; iVar2 = iVar2 + -1) {
      (pMVar4->_s_0).base1 = 0;
      pMVar4 = (Misn16Mission_u_112 *)((int)pMVar4 + 4);
    }
    (this->field19_0xc8)._s_0.rtype = 0;
    (this->field19_0xc8)._s_0.rcount = 0;
    Setup(this);
    bVar1 = AiMission::Load(this_00,param_1);
  }
  else {
    bVar1 = ::in(param_1,(this->field16_0x40).b_array,6);
    if ((((bVar1) && (bVar1 = ::in(param_1,(this->field17_0x48).f_array,0x24), bVar1)) &&
        (bVar1 = ::in(param_1,(this->field18_0x70).h_array,0x54), bVar1)) &&
       ((bVar1 = ::in(param_1,(this->field19_0xc8).i_array,8), bVar1 &&
        (bVar1 = AiMission::Load((AiMission *)this,param_1), bVar1)))) {
      return true;
    }
    bVar1 = false;
  }
  return bVar1;
}
