/*
 * Entry: 00436252
 * Name: Misn12Mission::Load
 * Namespace: Misn12Mission
 * Signature: bool Load(Misn12Mission * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall Misn12Mission::Load(Misn12Mission *this,_iobuf *param_1)

{
  bool bVar1;
  int iVar2;
  Misn12Mission_u_160 *pMVar3;
  Misn12Mission_u_272 *pMVar4;
  
  if (missionSave) {
    memset(&this->field16_0x40,0);
    pMVar3 = &this->field17_0xa0;
    for (iVar2 = 0x1b; iVar2 != 0; iVar2 = iVar2 + -1) {
      (pMVar3->_s_0).countdown_time = 99999.0;
      pMVar3 = (Misn12Mission_u_160 *)((int)pMVar3 + 4);
    }
    pMVar4 = &this->field18_0x110;
    for (iVar2 = 0x39; iVar2 != 0; iVar2 = iVar2 + -1) {
      (pMVar4->_s_0).user = 0;
      pMVar4 = (Misn12Mission_u_272 *)((int)pMVar4 + 4);
    }
    (this->field19_0x1f8)._s_0.audmsg = 0;
    Setup(this);
    bVar1 = AiMission::Load((AiMission *)this,param_1);
  }
  else {
    bVar1 = ::in(param_1,(this->field16_0x40).b_array,0x5c);
    if ((((bVar1) && (bVar1 = ::in(param_1,(this->field17_0xa0).f_array,0x6c), bVar1)) &&
        (bVar1 = ::in(param_1,(this->field18_0x110).h_array,0xe4), bVar1)) &&
       ((bVar1 = ::in(param_1,(this->field19_0x1f8).i_array,4), bVar1 &&
        (bVar1 = AiMission::Load((AiMission *)this,param_1), bVar1)))) {
      return true;
    }
    bVar1 = false;
  }
  return bVar1;
}
