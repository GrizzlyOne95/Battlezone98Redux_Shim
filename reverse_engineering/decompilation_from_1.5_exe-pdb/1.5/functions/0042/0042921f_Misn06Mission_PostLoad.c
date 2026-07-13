/*
 * Entry: 0042921f
 * Name: Misn06Mission::PostLoad
 * Namespace: Misn06Mission
 * Signature: bool PostLoad(Misn06Mission * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall Misn06Mission::PostLoad(Misn06Mission *this)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  Misn06Mission_u_304 *pMVar4;
  
  if (missionSave) {
    bVar1 = AiMission::PostLoad((AiMission *)this);
    return bVar1;
  }
  pMVar4 = &this->field18_0x130;
  iVar3 = 0x77;
  do {
    iVar2 = ConvertHandle((pMVar4->_s_0).haephestus);
    (pMVar4->_s_0).haephestus = iVar2;
    pMVar4 = (Misn06Mission_u_304 *)((int)pMVar4 + 4);
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  bVar1 = AiMission::PostLoad((AiMission *)this);
  return bVar1;
}
