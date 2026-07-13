/*
 * Entry: 00444000
 * Name: Misns3Mission::Load
 * Namespace: Misns3Mission
 * Signature: bool Load(Misns3Mission * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall Misns3Mission::Load(Misns3Mission *this,_iobuf *param_1)

{
  bool bVar1;
  int iVar2;
  AiMission *this_00;
  Misns3Mission_u_64 *pMVar3;
  Misns3Mission_u_112 *pMVar4;
  Misns3Mission_u_260 *pMVar5;
  
  if (missionSave) {
    pMVar3 = &this->field16_0x40;
    for (iVar2 = 6; iVar2 != 0; iVar2 = iVar2 + -1) {
      *(undefined4 *)pMVar3 = 0;
      pMVar3 = (Misns3Mission_u_64 *)((int)pMVar3 + 4);
    }
    *(undefined2 *)pMVar3 = 0;
    (this->field17_0x5c)._s_0.withdraw = 99999.0;
    (this->field17_0x5c)._s_0.help1 = 99999.0;
    (this->field17_0x5c)._s_0.help2 = 99999.0;
    (this->field17_0x5c)._s_0.help3 = 99999.0;
    pMVar4 = &this->field18_0x70;
    for (iVar2 = 0x24; iVar2 != 0; iVar2 = iVar2 + -1) {
      (pMVar4->_s_0).bd1 = 0;
      pMVar4 = (Misns3Mission_u_112 *)((int)pMVar4 + 4);
    }
    pMVar5 = &this->field19_0x104;
    for (iVar2 = 7; iVar2 != 0; iVar2 = iVar2 + -1) {
      (pMVar5->_s_0).audmsg = 0;
      pMVar5 = (Misns3Mission_u_260 *)((int)pMVar5 + 4);
    }
    Setup(this);
    bVar1 = AiMission::Load(this_00,param_1);
  }
  else {
    bVar1 = ::in(param_1,(this->field16_0x40).b_array,0x1a);
    if ((((bVar1) && (bVar1 = ::in(param_1,(this->field17_0x5c).f_array,0x10), bVar1)) &&
        (bVar1 = ::in(param_1,(this->field18_0x70).h_array,0x90), bVar1)) &&
       ((bVar1 = ::in(param_1,(this->field19_0x104).i_array,0x1c), bVar1 &&
        (bVar1 = AiMission::Load((AiMission *)this,param_1), bVar1)))) {
      return true;
    }
    bVar1 = false;
  }
  return bVar1;
}
