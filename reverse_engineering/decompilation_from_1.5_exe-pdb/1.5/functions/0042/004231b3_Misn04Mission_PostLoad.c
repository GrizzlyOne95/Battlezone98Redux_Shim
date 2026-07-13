/*
 * Entry: 004231b3
 * Name: Misn04Mission::PostLoad
 * Namespace: Misn04Mission
 * Signature: bool PostLoad(Misn04Mission * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall Misn04Mission::PostLoad(Misn04Mission *this)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  Misn04Mission_u_260 *pMVar4;
  
  if (missionSave) {
    bVar1 = AiMission::PostLoad((AiMission *)this);
    return bVar1;
  }
  pMVar4 = &this->field18_0x104;
  iVar3 = 0x41;
  do {
    iVar2 = ConvertHandle((pMVar4->_s_0).svrec);
    (pMVar4->_s_0).svrec = iVar2;
    pMVar4 = (Misn04Mission_u_260 *)((int)pMVar4 + 4);
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  bVar1 = AiMission::PostLoad((AiMission *)this);
  return bVar1;
}
