/*
 * Entry: 0042d7f1
 * Name: Misn09Mission::PostLoad
 * Namespace: Misn09Mission
 * Signature: bool PostLoad(Misn09Mission * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall Misn09Mission::PostLoad(Misn09Mission *this)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  Misn09Mission_u_236 *pMVar4;
  
  if (missionSave) {
    bVar1 = AiMission::PostLoad((AiMission *)this);
    return bVar1;
  }
  pMVar4 = &this->field18_0xec;
  iVar3 = 0x36;
  do {
    iVar2 = ConvertHandle((pMVar4->_s_0).user);
    (pMVar4->_s_0).user = iVar2;
    pMVar4 = (Misn09Mission_u_236 *)((int)pMVar4 + 4);
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  bVar1 = AiMission::PostLoad((AiMission *)this);
  return bVar1;
}
