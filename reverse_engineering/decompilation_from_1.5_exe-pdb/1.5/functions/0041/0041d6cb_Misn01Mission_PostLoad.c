/*
 * Entry: 0041d6cb
 * Name: Misn01Mission::PostLoad
 * Namespace: Misn01Mission
 * Signature: bool PostLoad(Misn01Mission * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall Misn01Mission::PostLoad(Misn01Mission *this)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  Misn01Mission_u_100 *pMVar4;
  
  if (missionSave) {
    bVar1 = AiMission::PostLoad((AiMission *)this);
    return bVar1;
  }
  pMVar4 = &this->field18_0x64;
  iVar3 = 3;
  do {
    iVar2 = ConvertHandle((pMVar4->_s_0).get_in_me);
    (pMVar4->_s_0).get_in_me = iVar2;
    pMVar4 = (Misn01Mission_u_100 *)((int)pMVar4 + 4);
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  bVar1 = AiMission::PostLoad((AiMission *)this);
  return bVar1;
}
