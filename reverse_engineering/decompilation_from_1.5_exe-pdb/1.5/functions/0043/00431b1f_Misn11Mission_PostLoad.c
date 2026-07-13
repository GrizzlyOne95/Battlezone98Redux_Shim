/*
 * Entry: 00431b1f
 * Name: Misn11Mission::PostLoad
 * Namespace: Misn11Mission
 * Signature: bool PostLoad(Misn11Mission * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall Misn11Mission::PostLoad(Misn11Mission *this)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  Misn11Mission_u_108 *pMVar4;
  
  if (missionSave) {
    bVar1 = AiMission::PostLoad((AiMission *)this);
    return bVar1;
  }
  pMVar4 = &this->field18_0x6c;
  iVar3 = 0x10;
  do {
    iVar2 = ConvertHandle((pMVar4->_s_0).player);
    (pMVar4->_s_0).player = iVar2;
    pMVar4 = (Misn11Mission_u_108 *)((int)pMVar4 + 4);
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  bVar1 = AiMission::PostLoad((AiMission *)this);
  return bVar1;
}
