/*
 * Entry: 00432633
 * Name: Misn12Mission::PostLoad
 * Namespace: Misn12Mission
 * Signature: bool PostLoad(Misn12Mission * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall Misn12Mission::PostLoad(Misn12Mission *this)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  Misn12Mission_u_272 *pMVar4;
  
  if (missionSave) {
    bVar1 = AiMission::PostLoad((AiMission *)this);
    return bVar1;
  }
  pMVar4 = &this->field18_0x110;
  iVar3 = 0x39;
  do {
    iVar2 = ConvertHandle((pMVar4->_s_0).user);
    (pMVar4->_s_0).user = iVar2;
    pMVar4 = (Misn12Mission_u_272 *)((int)pMVar4 + 4);
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  bVar1 = AiMission::PostLoad((AiMission *)this);
  return bVar1;
}
