/*
 * Entry: 00429374
 * Name: Misn07Mission::PostLoad
 * Namespace: Misn07Mission
 * Signature: bool PostLoad(Misn07Mission * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall Misn07Mission::PostLoad(Misn07Mission *this)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  Misn07Mission_u_484 *pMVar4;
  
  if (missionSave) {
    bVar1 = AiMission::PostLoad((AiMission *)this);
    return bVar1;
  }
  pMVar4 = &this->field18_0x1e4;
  iVar3 = 200;
  do {
    iVar2 = ConvertHandle((pMVar4->_s_0).user);
    (pMVar4->_s_0).user = iVar2;
    pMVar4 = (Misn07Mission_u_484 *)((int)pMVar4 + 4);
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  bVar1 = AiMission::PostLoad((AiMission *)this);
  return bVar1;
}
