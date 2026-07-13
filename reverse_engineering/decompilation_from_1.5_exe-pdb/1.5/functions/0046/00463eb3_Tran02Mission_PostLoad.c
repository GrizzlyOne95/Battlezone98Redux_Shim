/*
 * Entry: 00463eb3
 * Name: Tran02Mission::PostLoad
 * Namespace: Tran02Mission
 * Signature: bool PostLoad(Tran02Mission * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall Tran02Mission::PostLoad(Tran02Mission *this)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  Tran02Mission_u_100 *pTVar4;
  
  if (missionSave) {
    bVar1 = AiMission::PostLoad((AiMission *)this);
    return bVar1;
  }
  pTVar4 = &this->field18_0x64;
  iVar3 = 4;
  do {
    iVar2 = ConvertHandle((pTVar4->_s_0).turret);
    (pTVar4->_s_0).turret = iVar2;
    pTVar4 = (Tran02Mission_u_100 *)((int)pTVar4 + 4);
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  bVar1 = AiMission::PostLoad((AiMission *)this);
  return bVar1;
}
