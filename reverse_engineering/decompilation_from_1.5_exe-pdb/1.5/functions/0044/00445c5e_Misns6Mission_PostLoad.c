/*
 * Entry: 00445c5e
 * Name: Misns6Mission::PostLoad
 * Namespace: Misns6Mission
 * Signature: bool PostLoad(Misns6Mission * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall Misns6Mission::PostLoad(Misns6Mission *this)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  Misns6Mission_u_108 *pMVar4;
  
  if (missionSave) {
    bVar1 = AiMission::PostLoad((AiMission *)this);
    return bVar1;
  }
  pMVar4 = &this->field18_0x6c;
  iVar3 = 0x10;
  do {
    iVar2 = ConvertHandle((pMVar4->_s_0).beacon);
    (pMVar4->_s_0).beacon = iVar2;
    pMVar4 = (Misns6Mission_u_108 *)((int)pMVar4 + 4);
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  bVar1 = AiMission::PostLoad((AiMission *)this);
  return bVar1;
}
