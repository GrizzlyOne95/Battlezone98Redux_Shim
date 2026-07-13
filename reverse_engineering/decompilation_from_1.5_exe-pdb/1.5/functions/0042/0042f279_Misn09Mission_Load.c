/*
 * Entry: 0042f279
 * Name: Misn09Mission::Load
 * Namespace: Misn09Mission
 * Signature: bool Load(Misn09Mission * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall Misn09Mission::Load(Misn09Mission *this,_iobuf *param_1)

{
  bool bVar1;
  int iVar2;
  Misn09Mission_u_120 *pMVar3;
  Misn09Mission_u_236 *pMVar4;
  
  if (missionSave) {
    memset(&this->field16_0x40,0);
    pMVar3 = &this->field17_0x78;
    for (iVar2 = 0x1c; iVar2 != 0; iVar2 = iVar2 + -1) {
      (pMVar3->_s_0).start_convoy_time = 99999.0;
      pMVar3 = (Misn09Mission_u_120 *)((int)pMVar3 + 4);
    }
    pMVar4 = &this->field18_0xec;
    for (iVar2 = 0x36; iVar2 != 0; iVar2 = iVar2 + -1) {
      (pMVar4->_s_0).user = 0;
      pMVar4 = (Misn09Mission_u_236 *)((int)pMVar4 + 4);
    }
    (this->field19_0x1c8)._s_0.stuff = 0;
    (this->field19_0x1c8)._s_0.x = 0;
    (this->field19_0x1c8)._s_0.y = 0;
    (this->field19_0x1c8)._s_0.scrap = 0;
    (this->field19_0x1c8)._s_0.audmsg = 0;
    Setup(this);
    bVar1 = AiMission::Load((AiMission *)this,param_1);
  }
  else {
    bVar1 = ::in(param_1,(this->field16_0x40).b_array,0x36);
    if ((((bVar1) && (bVar1 = ::in(param_1,(this->field17_0x78).f_array,0x70), bVar1)) &&
        (bVar1 = ::in(param_1,(this->field18_0xec).h_array,0xd8), bVar1)) &&
       ((bVar1 = ::in(param_1,(this->field19_0x1c8).i_array,0x14), bVar1 &&
        (bVar1 = AiMission::Load((AiMission *)this,param_1), bVar1)))) {
      return true;
    }
    bVar1 = false;
  }
  return bVar1;
}
