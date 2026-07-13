/*
 * Entry: 0043eb22
 * Name: Misn18Mission::PostLoad
 * Namespace: Misn18Mission
 * Signature: bool PostLoad(Misn18Mission * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall Misn18Mission::PostLoad(Misn18Mission *this)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  Misn18Mission_u_164 *pMVar4;
  
  if (missionSave) {
    bVar1 = AiMission::PostLoad((AiMission *)this);
    return bVar1;
  }
  pMVar4 = &this->field18_0xa4;
  iVar3 = 0x40;
  do {
    iVar2 = ConvertHandle((pMVar4->_s_0).transport);
    (pMVar4->_s_0).transport = iVar2;
    pMVar4 = (Misn18Mission_u_164 *)((int)pMVar4 + 4);
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  bVar1 = AiMission::PostLoad((AiMission *)this);
  return bVar1;
}
