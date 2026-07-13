/*
 * Entry: 0043a0b8
 * Name: Misn15Mission::Load
 * Namespace: Misn15Mission
 * Signature: bool Load(Misn15Mission * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall Misn15Mission::Load(Misn15Mission *this,_iobuf *param_1)

{
  bool bVar1;
  int iVar2;
  AiMission *this_00;
  Misn15Mission_u_80 *pMVar3;
  Misn15Mission_u_128 *pMVar4;
  
  if (missionSave) {
    *(undefined4 *)&this->field16_0x40 = 0;
    *(undefined4 *)((int)&this->field16_0x40 + 4) = 0;
    *(undefined4 *)((int)&this->field16_0x40 + 8) = 0;
    *(undefined2 *)((int)&this->field16_0x40 + 0xc) = 0;
    (this->field16_0x40)._s_0.tartarus = false;
    pMVar3 = &this->field17_0x50;
    for (iVar2 = 0xb; iVar2 != 0; iVar2 = iVar2 + -1) {
      (pMVar3->_s_0).camera_time = 99999.0;
      pMVar3 = (Misn15Mission_u_80 *)((int)pMVar3 + 4);
    }
    pMVar4 = &this->field18_0x80;
    for (iVar2 = 0x81; iVar2 != 0; iVar2 = iVar2 + -1) {
      (pMVar4->_s_0).tart = 0;
      pMVar4 = (Misn15Mission_u_128 *)((int)pMVar4 + 4);
    }
    (this->field19_0x288)._s_0.savcount = 0;
    (this->field19_0x288)._s_0.silocount = 0;
    Setup(this);
    bVar1 = AiMission::Load(this_00,param_1);
  }
  else {
    bVar1 = ::in(param_1,(this->field16_0x40).b_array,0xf);
    if ((((bVar1) && (bVar1 = ::in(param_1,(this->field17_0x50).f_array,0x2c), bVar1)) &&
        (bVar1 = ::in(param_1,(this->field18_0x80).h_array,0x204), bVar1)) &&
       ((bVar1 = ::in(param_1,(this->field19_0x288).i_array,8), bVar1 &&
        (bVar1 = AiMission::Load((AiMission *)this,param_1), bVar1)))) {
      return true;
    }
    bVar1 = false;
  }
  return bVar1;
}
