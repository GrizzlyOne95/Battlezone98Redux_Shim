/*
 * Entry: 00440254
 * Name: Misns1Mission::Load
 * Namespace: Misns1Mission
 * Signature: bool Load(Misns1Mission * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall Misns1Mission::Load(Misns1Mission *this,_iobuf *param_1)

{
  bool bVar1;
  int iVar2;
  AiMission *this_00;
  Misns1Mission_u_132 *pMVar3;
  Misns1Mission_u_244 *pMVar4;
  Misns1Mission_u_428 *pMVar5;
  
  if (missionSave) {
    memset(&this->field16_0x40,0);
    pMVar3 = &this->field17_0x84;
    for (iVar2 = 0x1b; iVar2 != 0; iVar2 = iVar2 + -1) {
      (pMVar3->_s_0).startconvoy = 99999.0;
      pMVar3 = (Misns1Mission_u_132 *)((int)pMVar3 + 4);
    }
    pMVar4 = &this->field18_0xf4;
    for (iVar2 = 0x2d; iVar2 != 0; iVar2 = iVar2 + -1) {
      (pMVar4->_s_0).colorado = 0;
      pMVar4 = (Misns1Mission_u_244 *)((int)pMVar4 + 4);
    }
    pMVar5 = &this->field19_0x1ac;
    for (iVar2 = 7; iVar2 != 0; iVar2 = iVar2 + -1) {
      (pMVar5->_s_0).path = 0;
      pMVar5 = (Misns1Mission_u_428 *)((int)pMVar5 + 4);
    }
    Setup(this);
    bVar1 = AiMission::Load(this_00,param_1);
  }
  else {
    bVar1 = ::in(param_1,(this->field16_0x40).b_array,0x40);
    if ((((bVar1) && (bVar1 = ::in(param_1,(this->field17_0x84).f_array,0x6c), bVar1)) &&
        (bVar1 = ::in(param_1,(this->field18_0xf4).h_array,0xb4), bVar1)) &&
       ((bVar1 = ::in(param_1,(this->field19_0x1ac).i_array,0x1c), bVar1 &&
        (bVar1 = AiMission::Load((AiMission *)this,param_1), bVar1)))) {
      return true;
    }
    bVar1 = false;
  }
  return bVar1;
}
