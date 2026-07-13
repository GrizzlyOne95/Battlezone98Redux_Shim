/*
 * Entry: 004451cb
 * Name: Misns5Mission::PostLoad
 * Namespace: Misns5Mission
 * Signature: bool PostLoad(Misns5Mission * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall Misns5Mission::PostLoad(Misns5Mission *this)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  Misns5Mission_u_104 *pMVar4;
  
  if (missionSave) {
    bVar1 = AiMission::PostLoad((AiMission *)this);
    return bVar1;
  }
  pMVar4 = &this->field18_0x68;
  iVar3 = 0xf;
  do {
    iVar2 = ConvertHandle((pMVar4->_s_0).a1);
    (pMVar4->_s_0).a1 = iVar2;
    pMVar4 = (Misns5Mission_u_104 *)((int)pMVar4 + 4);
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  bVar1 = AiMission::PostLoad((AiMission *)this);
  return bVar1;
}
