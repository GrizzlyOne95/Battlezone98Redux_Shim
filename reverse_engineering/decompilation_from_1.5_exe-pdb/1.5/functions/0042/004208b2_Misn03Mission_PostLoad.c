/*
 * Entry: 004208b2
 * Name: Misn03Mission::PostLoad
 * Namespace: Misn03Mission
 * Signature: bool PostLoad(Misn03Mission * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall Misn03Mission::PostLoad(Misn03Mission *this)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  Misn03Mission_u_220 *pMVar4;
  
  if (missionSave) {
    bVar1 = AiMission::PostLoad((AiMission *)this);
    return bVar1;
  }
  pMVar4 = &this->field18_0xdc;
  iVar3 = 0x57;
  do {
    iVar2 = ConvertHandle((pMVar4->_s_0).user);
    (pMVar4->_s_0).user = iVar2;
    pMVar4 = (Misn03Mission_u_220 *)((int)pMVar4 + 4);
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  bVar1 = AiMission::PostLoad((AiMission *)this);
  return bVar1;
}
