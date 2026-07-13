/*
 * Entry: 0042d681
 * Name: Misn08Mission::PostLoad
 * Namespace: Misn08Mission
 * Signature: bool PostLoad(Misn08Mission * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall Misn08Mission::PostLoad(Misn08Mission *this)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  Misn08Mission_u_248 *pMVar4;
  
  if (missionSave) {
    bVar1 = AiMission::PostLoad((AiMission *)this);
    return bVar1;
  }
  pMVar4 = &this->field18_0xf8;
  iVar3 = 0x29;
  do {
    iVar2 = ConvertHandle((pMVar4->_s_0).user);
    (pMVar4->_s_0).user = iVar2;
    pMVar4 = (Misn08Mission_u_248 *)((int)pMVar4 + 4);
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  bVar1 = AiMission::PostLoad((AiMission *)this);
  return bVar1;
}
