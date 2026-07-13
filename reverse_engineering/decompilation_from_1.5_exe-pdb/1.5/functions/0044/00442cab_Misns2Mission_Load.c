/*
 * Entry: 00442cab
 * Name: Misns2Mission::Load
 * Namespace: Misns2Mission
 * Signature: bool Load(Misns2Mission * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall Misns2Mission::Load(Misns2Mission *this,_iobuf *param_1)

{
  bool bVar1;
  int iVar2;
  AiMission *this_00;
  Misns2Mission_u_64 *pMVar3;
  Misns2Mission_u_104 *pMVar4;
  Misns2Mission_u_144 *pMVar5;
  Misns2Mission_u_564 *pMVar6;
  
  if (missionSave) {
    pMVar3 = &this->field16_0x40;
    for (iVar2 = 9; iVar2 != 0; iVar2 = iVar2 + -1) {
      *(undefined4 *)pMVar3 = 0;
      pMVar3 = (Misns2Mission_u_64 *)((int)pMVar3 + 4);
    }
    (pMVar3->_s_0).cintimeset = false;
    pMVar4 = &this->field17_0x68;
    for (iVar2 = 9; iVar2 != 0; iVar2 = iVar2 + -1) {
      (pMVar4->_s_0).wave1start = 99999.0;
      pMVar4 = (Misns2Mission_u_104 *)((int)pMVar4 + 4);
    }
    pMVar5 = &this->field18_0x90;
    for (iVar2 = 0x68; iVar2 != 0; iVar2 = iVar2 + -1) {
      (pMVar5->_s_0).player = 0;
      pMVar5 = (Misns2Mission_u_144 *)((int)pMVar5 + 4);
    }
    pMVar6 = &this->field19_0x234;
    for (iVar2 = 9; iVar2 != 0; iVar2 = iVar2 + -1) {
      (pMVar6->_s_0).audmsg = 0;
      pMVar6 = (Misns2Mission_u_564 *)((int)pMVar6 + 4);
    }
    Setup(this);
    bVar1 = AiMission::Load(this_00,param_1);
  }
  else {
    bVar1 = ::in(param_1,(this->field16_0x40).b_array,0x25);
    if ((((bVar1) && (bVar1 = ::in(param_1,(this->field17_0x68).f_array,0x24), bVar1)) &&
        (bVar1 = ::in(param_1,(this->field18_0x90).h_array,0x1a0), bVar1)) &&
       ((bVar1 = ::in(param_1,(this->field19_0x234).i_array,0x24), bVar1 &&
        (bVar1 = AiMission::Load((AiMission *)this,param_1), bVar1)))) {
      return true;
    }
    bVar1 = false;
  }
  return bVar1;
}
