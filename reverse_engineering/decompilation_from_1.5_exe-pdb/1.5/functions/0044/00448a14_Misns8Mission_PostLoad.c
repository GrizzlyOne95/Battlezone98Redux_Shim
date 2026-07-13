/*
 * Entry: 00448a14
 * Name: Misns8Mission::PostLoad
 * Namespace: Misns8Mission
 * Signature: bool PostLoad(Misns8Mission * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall Misns8Mission::PostLoad(Misns8Mission *this)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  Misns8Mission_u_304 *pMVar4;
  
  if (missionSave) {
    bVar1 = AiMission::PostLoad((AiMission *)this);
    return bVar1;
  }
  pMVar4 = &this->field18_0x130;
  iVar3 = 0x50;
  do {
    iVar2 = ConvertHandle((pMVar4->_s_0).user);
    (pMVar4->_s_0).user = iVar2;
    pMVar4 = (Misns8Mission_u_304 *)((int)pMVar4 + 4);
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  bVar1 = AiMission::PostLoad((AiMission *)this);
  return bVar1;
}
