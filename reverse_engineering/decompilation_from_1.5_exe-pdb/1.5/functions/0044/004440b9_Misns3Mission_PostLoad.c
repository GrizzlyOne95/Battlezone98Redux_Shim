/*
 * Entry: 004440b9
 * Name: Misns3Mission::PostLoad
 * Namespace: Misns3Mission
 * Signature: bool PostLoad(Misns3Mission * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall Misns3Mission::PostLoad(Misns3Mission *this)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  Misns3Mission_u_112 *pMVar4;
  
  if (missionSave) {
    bVar1 = AiMission::PostLoad((AiMission *)this);
    return bVar1;
  }
  pMVar4 = &this->field18_0x70;
  iVar3 = 0x24;
  do {
    iVar2 = ConvertHandle((pMVar4->_s_0).bd1);
    (pMVar4->_s_0).bd1 = iVar2;
    pMVar4 = (Misns3Mission_u_112 *)((int)pMVar4 + 4);
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  bVar1 = AiMission::PostLoad((AiMission *)this);
  return bVar1;
}
