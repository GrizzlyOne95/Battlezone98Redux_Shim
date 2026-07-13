/*
 * Entry: 0042d5c0
 * Name: Misn08Mission::Load
 * Namespace: Misn08Mission
 * Signature: bool Load(Misn08Mission * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall Misn08Mission::Load(Misn08Mission *this,_iobuf *param_1)

{
  bool bVar1;
  int iVar2;
  Misn08Mission_u_112 *pMVar3;
  Misn08Mission_u_248 *pMVar4;
  
  if (missionSave) {
    memset(&this->field16_0x40,0);
    pMVar3 = &this->field17_0x70;
    for (iVar2 = 0x21; iVar2 != 0; iVar2 = iVar2 + -1) {
      (pMVar3->_s_0).unit_spawn_time = 99999.0;
      pMVar3 = (Misn08Mission_u_112 *)((int)pMVar3 + 4);
    }
    pMVar4 = &this->field18_0xf8;
    for (iVar2 = 0x29; iVar2 != 0; iVar2 = iVar2 + -1) {
      (pMVar4->_s_0).user = 0;
      pMVar4 = (Misn08Mission_u_248 *)((int)pMVar4 + 4);
    }
    (this->field19_0x1a0)._s_0.units1 = 0;
    (this->field19_0x1a0)._s_0.units2 = 0;
    Setup(this);
    bVar1 = AiMission::Load((AiMission *)this,param_1);
  }
  else {
    bVar1 = ::in(param_1,(this->field16_0x40).b_array,0x2c);
    if ((((bVar1) && (bVar1 = ::in(param_1,(this->field17_0x70).f_array,0x84), bVar1)) &&
        (bVar1 = ::in(param_1,(this->field18_0xf8).h_array,0xa4), bVar1)) &&
       ((bVar1 = ::in(param_1,(this->field19_0x1a0).i_array,8), bVar1 &&
        (bVar1 = AiMission::Load((AiMission *)this,param_1), bVar1)))) {
      return true;
    }
    bVar1 = false;
  }
  return bVar1;
}
