/*
 * Entry: 0043d419
 * Name: Misn17Mission::PostLoad
 * Namespace: Misn17Mission
 * Signature: bool PostLoad(Misn17Mission * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall Misn17Mission::PostLoad(Misn17Mission *this)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  Misn17Mission_u_272 *pMVar4;
  
  if (missionSave) {
    bVar1 = AiMission::PostLoad((AiMission *)this);
    return bVar1;
  }
  pMVar4 = &this->field18_0x110;
  iVar3 = 0x8e;
  do {
    iVar2 = ConvertHandle((pMVar4->_s_0).savfactory1);
    (pMVar4->_s_0).savfactory1 = iVar2;
    pMVar4 = (Misn17Mission_u_272 *)((int)pMVar4 + 4);
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  bVar1 = AiMission::PostLoad((AiMission *)this);
  return bVar1;
}
