/*
 * Entry: 0042f36d
 * Name: Misn10Mission::PostLoad
 * Namespace: Misn10Mission
 * Signature: bool PostLoad(Misn10Mission * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall Misn10Mission::PostLoad(Misn10Mission *this)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  Misn10Mission_u_188 *pMVar4;
  
  if (missionSave) {
    bVar1 = AiMission::PostLoad((AiMission *)this);
    return bVar1;
  }
  pMVar4 = &this->field18_0xbc;
  iVar3 = 0x1f;
  do {
    iVar2 = ConvertHandle((pMVar4->_s_0).user);
    (pMVar4->_s_0).user = iVar2;
    pMVar4 = (Misn10Mission_u_188 *)((int)pMVar4 + 4);
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  bVar1 = AiMission::PostLoad((AiMission *)this);
  return bVar1;
}
