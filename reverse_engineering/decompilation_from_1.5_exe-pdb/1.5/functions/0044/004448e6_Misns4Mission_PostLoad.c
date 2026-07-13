/*
 * Entry: 004448e6
 * Name: Misns4Mission::PostLoad
 * Namespace: Misns4Mission
 * Signature: bool PostLoad(Misns4Mission * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall Misns4Mission::PostLoad(Misns4Mission *this)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  Misns4Mission_u_124 *pMVar4;
  
  if (missionSave) {
    bVar1 = AiMission::PostLoad((AiMission *)this);
    return bVar1;
  }
  pMVar4 = &this->field18_0x7c;
  iVar3 = 0x15;
  do {
    iVar2 = ConvertHandle((pMVar4->_s_0).convoy_handle[0]);
    (pMVar4->_s_0).convoy_handle[0] = iVar2;
    pMVar4 = (Misns4Mission_u_124 *)((int)pMVar4 + 4);
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  bVar1 = AiMission::PostLoad((AiMission *)this);
  return bVar1;
}
