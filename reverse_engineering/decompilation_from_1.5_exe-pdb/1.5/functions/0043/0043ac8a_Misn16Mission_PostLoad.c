/*
 * Entry: 0043ac8a
 * Name: Misn16Mission::PostLoad
 * Namespace: Misn16Mission
 * Signature: bool PostLoad(Misn16Mission * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall Misn16Mission::PostLoad(Misn16Mission *this)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  Misn16Mission_u_112 *pMVar4;
  
  if (missionSave) {
    bVar1 = AiMission::PostLoad((AiMission *)this);
    return bVar1;
  }
  pMVar4 = &this->field18_0x70;
  iVar3 = 0x15;
  do {
    iVar2 = ConvertHandle((pMVar4->_s_0).base1);
    (pMVar4->_s_0).base1 = iVar2;
    pMVar4 = (Misn16Mission_u_112 *)((int)pMVar4 + 4);
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  bVar1 = AiMission::PostLoad((AiMission *)this);
  return bVar1;
}
