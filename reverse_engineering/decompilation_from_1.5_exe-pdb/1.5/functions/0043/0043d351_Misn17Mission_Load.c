/*
 * Entry: 0043d351
 * Name: Misn17Mission::Load
 * Namespace: Misn17Mission
 * Signature: bool Load(Misn17Mission * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall Misn17Mission::Load(Misn17Mission *this,_iobuf *param_1)

{
  bool bVar1;
  int iVar2;
  AiMission *this_00;
  Misn17Mission_u_132 *pMVar3;
  Misn17Mission_u_272 *pMVar4;
  
  if (missionSave) {
    memset(&this->field16_0x40,0);
    pMVar3 = &this->field17_0x84;
    for (iVar2 = 0x22; iVar2 != 0; iVar2 = iVar2 + -1) {
      (pMVar3->_s_0).discheck = 99999.0;
      pMVar3 = (Misn17Mission_u_132 *)((int)pMVar3 + 4);
    }
    pMVar4 = &this->field18_0x110;
    for (iVar2 = 0x8e; iVar2 != 0; iVar2 = iVar2 + -1) {
      (pMVar4->_s_0).savfactory1 = 0;
      pMVar4 = (Misn17Mission_u_272 *)((int)pMVar4 + 4);
    }
    (this->field19_0x34c)._s_0.hint = 0;
    (this->field19_0x34c)._s_0.minecount = 0;
    (this->field19_0x34c)._s_0.crit = 0;
    Setup(this);
    bVar1 = AiMission::Load(this_00,param_1);
  }
  else {
    bVar1 = ::in(param_1,(this->field16_0x40).b_array,0x40);
    if ((((bVar1) && (bVar1 = ::in(param_1,(this->field17_0x84).f_array,0x88), bVar1)) &&
        (bVar1 = ::in(param_1,(this->field18_0x110).h_array,0x238), bVar1)) &&
       ((bVar1 = ::in(param_1,(this->field19_0x34c).i_array,0xc), bVar1 &&
        (bVar1 = AiMission::Load((AiMission *)this,param_1), bVar1)))) {
      return true;
    }
    bVar1 = false;
  }
  return bVar1;
}
