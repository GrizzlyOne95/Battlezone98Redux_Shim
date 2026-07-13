/*
 * Entry: 00464536
 * Name: Tran03Mission::PostLoad
 * Namespace: Tran03Mission
 * Signature: bool PostLoad(Tran03Mission * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall Tran03Mission::PostLoad(Tran03Mission *this)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  Tran03Mission_u_100 *pTVar4;
  
  if (missionSave) {
    bVar1 = AiMission::PostLoad((AiMission *)this);
    return bVar1;
  }
  pTVar4 = &this->field18_0x64;
  iVar3 = 4;
  do {
    iVar2 = ConvertHandle((pTVar4->_s_0).scav);
    (pTVar4->_s_0).scav = iVar2;
    pTVar4 = (Tran03Mission_u_100 *)((int)pTVar4 + 4);
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  bVar1 = AiMission::PostLoad((AiMission *)this);
  return bVar1;
}
