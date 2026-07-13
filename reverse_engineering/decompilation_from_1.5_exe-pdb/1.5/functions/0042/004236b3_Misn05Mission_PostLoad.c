/*
 * Entry: 004236b3
 * Name: Misn05Mission::PostLoad
 * Namespace: Misn05Mission
 * Signature: bool PostLoad(Misn05Mission * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall Misn05Mission::PostLoad(Misn05Mission *this)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  Misn05Mission_u_300 *pMVar4;
  
  if (missionSave) {
    bVar1 = AiMission::PostLoad((AiMission *)this);
    return bVar1;
  }
  pMVar4 = &this->field18_0x12c;
  iVar3 = 0x41;
  do {
    iVar2 = ConvertHandle((pMVar4->_s_0).lemnos);
    (pMVar4->_s_0).lemnos = iVar2;
    pMVar4 = (Misn05Mission_u_300 *)((int)pMVar4 + 4);
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  bVar1 = AiMission::PostLoad((AiMission *)this);
  return bVar1;
}
