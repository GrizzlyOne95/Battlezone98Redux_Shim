/*
 * Entry: 0044bcdf
 * Name: Misns8Mission::Load
 * Namespace: Misns8Mission
 * Signature: bool Load(Misns8Mission * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall Misns8Mission::Load(Misns8Mission *this,_iobuf *param_1)

{
  bool bVar1;
  int iVar2;
  Misns8Mission_u_180 *pMVar3;
  Misns8Mission_u_304 *pMVar4;
  Misns8Mission_u_628 *pMVar5;
  
  if (missionSave) {
    memset(&this->field16_0x40,0);
    pMVar3 = &this->field17_0xb4;
    for (iVar2 = 0x1e; iVar2 != 0; iVar2 = iVar2 + -1) {
      (pMVar3->_s_0).unit_spawn_time = 99999.0;
      pMVar3 = (Misns8Mission_u_180 *)((int)pMVar3 + 4);
    }
    pMVar4 = &this->field18_0x130;
    for (iVar2 = 0x50; iVar2 != 0; iVar2 = iVar2 + -1) {
      (pMVar4->_s_0).user = 0;
      pMVar4 = (Misns8Mission_u_304 *)((int)pMVar4 + 4);
    }
    pMVar5 = &this->field19_0x274;
    for (iVar2 = 0xd; iVar2 != 0; iVar2 = iVar2 + -1) {
      (pMVar5->_s_0).units = 0;
      pMVar5 = (Misns8Mission_u_628 *)((int)pMVar5 + 4);
    }
    Setup(this);
    bVar1 = AiMission::Load((AiMission *)this,param_1);
  }
  else {
    bVar1 = ::in(param_1,(this->field16_0x40).b_array,0x71);
    if ((((bVar1) && (bVar1 = ::in(param_1,(this->field17_0xb4).f_array,0x78), bVar1)) &&
        (bVar1 = ::in(param_1,(this->field18_0x130).h_array,0x140), bVar1)) &&
       ((bVar1 = ::in(param_1,(this->field19_0x274).i_array,0x34), bVar1 &&
        (bVar1 = AiMission::Load((AiMission *)this,param_1), bVar1)))) {
      return true;
    }
    bVar1 = false;
  }
  return bVar1;
}
