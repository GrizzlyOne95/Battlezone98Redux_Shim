/*
 * Entry: 00438274
 * Name: Misn13Mission::PostLoad
 * Namespace: Misn13Mission
 * Signature: bool PostLoad(Misn13Mission * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall Misn13Mission::PostLoad(Misn13Mission *this)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  Misn13Mission_u_172 *pMVar4;
  
  if (missionSave) {
    bVar1 = AiMission::PostLoad((AiMission *)this);
    return bVar1;
  }
  pMVar4 = &this->field18_0xac;
  iVar3 = 0x4c;
  do {
    iVar2 = ConvertHandle((pMVar4->_s_0).user);
    (pMVar4->_s_0).user = iVar2;
    pMVar4 = (Misn13Mission_u_172 *)((int)pMVar4 + 4);
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  bVar1 = AiMission::PostLoad((AiMission *)this);
  return bVar1;
}
