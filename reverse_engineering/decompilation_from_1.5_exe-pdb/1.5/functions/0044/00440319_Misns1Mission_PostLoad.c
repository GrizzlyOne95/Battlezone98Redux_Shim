/*
 * Entry: 00440319
 * Name: Misns1Mission::PostLoad
 * Namespace: Misns1Mission
 * Signature: bool PostLoad(Misns1Mission * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall Misns1Mission::PostLoad(Misns1Mission *this)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  Misns1Mission_u_244 *pMVar4;
  
  if (missionSave) {
    bVar1 = AiMission::PostLoad((AiMission *)this);
    return bVar1;
  }
  pMVar4 = &this->field18_0xf4;
  iVar3 = 0x2d;
  do {
    iVar2 = ConvertHandle((pMVar4->_s_0).colorado);
    (pMVar4->_s_0).colorado = iVar2;
    pMVar4 = (Misns1Mission_u_244 *)((int)pMVar4 + 4);
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  bVar1 = AiMission::PostLoad((AiMission *)this);
  return bVar1;
}
