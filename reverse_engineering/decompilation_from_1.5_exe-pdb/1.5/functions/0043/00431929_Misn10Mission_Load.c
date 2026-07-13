/*
 * Entry: 00431929
 * Name: Misn10Mission::Load
 * Namespace: Misn10Mission
 * Signature: bool Load(Misn10Mission * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall Misn10Mission::Load(Misn10Mission *this,_iobuf *param_1)

{
  bool bVar1;
  int iVar2;
  Misn10Mission_u_132 *pMVar3;
  Misn10Mission_u_188 *pMVar4;
  
  if (missionSave) {
    memset(&this->field16_0x40,0);
    pMVar3 = &this->field17_0x84;
    for (iVar2 = 0xd; iVar2 != 0; iVar2 = iVar2 + -1) {
      (pMVar3->_s_0).gech_warning_message = 99999.0;
      pMVar3 = (Misn10Mission_u_132 *)((int)pMVar3 + 4);
    }
    pMVar4 = &this->field18_0xbc;
    for (iVar2 = 0x1f; iVar2 != 0; iVar2 = iVar2 + -1) {
      (pMVar4->_s_0).user = 0;
      pMVar4 = (Misn10Mission_u_188 *)((int)pMVar4 + 4);
    }
    (this->field19_0x13c)._s_0.audmsg = 0;
    Setup(this);
    bVar1 = AiMission::Load((AiMission *)this,param_1);
  }
  else {
    bVar1 = ::in(param_1,(this->field16_0x40).b_array,0x42);
    if ((((bVar1) && (bVar1 = ::in(param_1,(this->field17_0x84).f_array,0x34), bVar1)) &&
        (bVar1 = ::in(param_1,(this->field18_0xbc).h_array,0x7c), bVar1)) &&
       ((bVar1 = ::in(param_1,(this->field19_0x13c).i_array,4), bVar1 &&
        (bVar1 = AiMission::Load((AiMission *)this,param_1), bVar1)))) {
      return true;
    }
    bVar1 = false;
  }
  return bVar1;
}
