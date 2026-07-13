/*
 * Entry: 00464c84
 * Name: Tran04Mission::PostLoad
 * Namespace: Tran04Mission
 * Signature: bool PostLoad(Tran04Mission * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall Tran04Mission::PostLoad(Tran04Mission *this)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  Tran04Mission_u_100 *pTVar4;
  
  if (missionSave) {
    bVar1 = AiMission::PostLoad((AiMission *)this);
    return bVar1;
  }
  pTVar4 = &this->field18_0x64;
  iVar3 = 8;
  do {
    iVar2 = ConvertHandle((pTVar4->_s_0).player);
    (pTVar4->_s_0).player = iVar2;
    pTVar4 = (Tran04Mission_u_100 *)((int)pTVar4 + 4);
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  bVar1 = AiMission::PostLoad((AiMission *)this);
  return bVar1;
}
