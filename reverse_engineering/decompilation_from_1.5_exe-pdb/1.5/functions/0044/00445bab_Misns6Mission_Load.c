/*
 * Entry: 00445bab
 * Name: Misns6Mission::Load
 * Namespace: Misns6Mission
 * Signature: bool Load(Misns6Mission * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall Misns6Mission::Load(Misns6Mission *this,_iobuf *param_1)

{
  bool bVar1;
  int iVar2;
  AiMission *this_00;
  Misns6Mission_u_80 *pMVar3;
  Misns6Mission_u_108 *pMVar4;
  
  if (missionSave) {
    *(undefined4 *)&this->field16_0x40 = 0;
    *(undefined4 *)((int)&this->field16_0x40 + 4) = 0;
    *(undefined4 *)((int)&this->field16_0x40 + 8) = 0;
    *(undefined2 *)((int)&this->field16_0x40 + 0xc) = 0;
    (this->field16_0x40)._s_0.counter_attack = false;
    pMVar3 = &this->field17_0x50;
    for (iVar2 = 6; iVar2 != 0; iVar2 = iVar2 + -1) {
      (pMVar3->_s_0).check_time = 99999.0;
      pMVar3 = (Misns6Mission_u_80 *)((int)pMVar3 + 4);
    }
    pMVar4 = &this->field18_0x6c;
    for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
      (pMVar4->_s_0).beacon = 0;
      pMVar4 = (Misns6Mission_u_108 *)((int)pMVar4 + 4);
    }
    (this->field19_0xb0)._s_0.next_target = 0;
    (this->field19_0xb0)._s_0.audmsg = 0;
    Setup(this);
    bVar1 = AiMission::Load(this_00,param_1);
  }
  else {
    bVar1 = ::in(param_1,(this->field16_0x40).b_array,0xf);
    if ((((bVar1) && (bVar1 = ::in(param_1,(this->field17_0x50).f_array,0x18), bVar1)) &&
        (bVar1 = ::in(param_1,(this->field18_0x6c).h_array,0x40), bVar1)) &&
       ((bVar1 = ::in(param_1,(this->field19_0xb0).i_array,8), bVar1 &&
        (bVar1 = AiMission::Load((AiMission *)this,param_1), bVar1)))) {
      return true;
    }
    bVar1 = false;
  }
  return bVar1;
}
