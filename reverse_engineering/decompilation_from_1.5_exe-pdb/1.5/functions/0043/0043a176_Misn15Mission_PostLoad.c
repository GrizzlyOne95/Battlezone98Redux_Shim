/*
 * Entry: 0043a176
 * Name: Misn15Mission::PostLoad
 * Namespace: Misn15Mission
 * Signature: bool PostLoad(Misn15Mission * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall Misn15Mission::PostLoad(Misn15Mission *this)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  Misn15Mission_u_128 *pMVar4;
  
  if (missionSave) {
    bVar1 = AiMission::PostLoad((AiMission *)this);
    return bVar1;
  }
  pMVar4 = &this->field18_0x80;
  iVar3 = 0x81;
  do {
    iVar2 = ConvertHandle((pMVar4->_s_0).tart);
    (pMVar4->_s_0).tart = iVar2;
    pMVar4 = (Misn15Mission_u_128 *)((int)pMVar4 + 4);
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  bVar1 = AiMission::PostLoad((AiMission *)this);
  return bVar1;
}
