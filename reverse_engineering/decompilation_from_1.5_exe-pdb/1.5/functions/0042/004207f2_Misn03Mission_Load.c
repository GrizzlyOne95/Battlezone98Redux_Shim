/*
 * Entry: 004207f2
 * Name: Misn03Mission::Load
 * Namespace: Misn03Mission
 * Signature: bool Load(Misn03Mission * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall Misn03Mission::Load(Misn03Mission *this,_iobuf *param_1)

{
  bool bVar1;
  int iVar2;
  Misn03Mission_u_120 *pMVar3;
  Misn03Mission_u_220 *pMVar4;
  
  if (missionSave) {
    memset(&this->field16_0x40,0);
    pMVar3 = &this->field17_0x78;
    for (iVar2 = 0x18; iVar2 != 0; iVar2 = iVar2 + -1) {
      (pMVar3->_s_0).next_second = 99999.0;
      pMVar3 = (Misn03Mission_u_120 *)((int)pMVar3 + 4);
    }
    pMVar4 = &this->field18_0xdc;
    for (iVar2 = 0x57; iVar2 != 0; iVar2 = iVar2 + -1) {
      (pMVar4->_s_0).user = 0;
      pMVar4 = (Misn03Mission_u_220 *)((int)pMVar4 + 4);
    }
    (this->field19_0x23c)._s_0.x = 0;
    (this->field19_0x23c)._s_0.z = 0;
    (this->field19_0x23c)._s_0.y = 0;
    (this->field19_0x23c)._s_0.audmsg = 0;
    Setup(this);
    bVar1 = AiMission::Load((AiMission *)this,param_1);
  }
  else {
    bVar1 = ::in(param_1,(this->field16_0x40).b_array,0x35);
    if ((((bVar1) && (bVar1 = ::in(param_1,(this->field17_0x78).f_array,0x60), bVar1)) &&
        (bVar1 = ::in(param_1,(this->field18_0xdc).h_array,0x15c), bVar1)) &&
       ((bVar1 = ::in(param_1,(this->field19_0x23c).i_array,0x10), bVar1 &&
        (bVar1 = AiMission::Load((AiMission *)this,param_1), bVar1)))) {
      return true;
    }
    bVar1 = false;
  }
  return bVar1;
}
