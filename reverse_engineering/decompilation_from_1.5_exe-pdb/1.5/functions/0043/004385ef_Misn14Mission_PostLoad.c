/*
 * Entry: 004385ef
 * Name: Misn14Mission::PostLoad
 * Namespace: Misn14Mission
 * Signature: bool PostLoad(Misn14Mission * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall Misn14Mission::PostLoad(Misn14Mission *this)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  Misn14Mission_u_136 *pMVar4;
  
  if (missionSave) {
    bVar1 = AiMission::PostLoad((AiMission *)this);
    return bVar1;
  }
  pMVar4 = &this->field18_0x88;
  iVar3 = 0x16;
  do {
    iVar2 = ConvertHandle((pMVar4->_s_0).beacon1);
    (pMVar4->_s_0).beacon1 = iVar2;
    pMVar4 = (Misn14Mission_u_136 *)((int)pMVar4 + 4);
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  bVar1 = AiMission::PostLoad((AiMission *)this);
  return bVar1;
}
