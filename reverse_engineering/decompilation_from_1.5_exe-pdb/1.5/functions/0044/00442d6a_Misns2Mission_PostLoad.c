/*
 * Entry: 00442d6a
 * Name: Misns2Mission::PostLoad
 * Namespace: Misns2Mission
 * Signature: bool PostLoad(Misns2Mission * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall Misns2Mission::PostLoad(Misns2Mission *this)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  Misns2Mission_u_144 *pMVar4;
  
  if (missionSave) {
    bVar1 = AiMission::PostLoad((AiMission *)this);
    return bVar1;
  }
  pMVar4 = &this->field18_0x90;
  iVar3 = 0x68;
  do {
    iVar2 = ConvertHandle((pMVar4->_s_0).player);
    (pMVar4->_s_0).player = iVar2;
    pMVar4 = (Misns2Mission_u_144 *)((int)pMVar4 + 4);
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  bVar1 = AiMission::PostLoad((AiMission *)this);
  return bVar1;
}
