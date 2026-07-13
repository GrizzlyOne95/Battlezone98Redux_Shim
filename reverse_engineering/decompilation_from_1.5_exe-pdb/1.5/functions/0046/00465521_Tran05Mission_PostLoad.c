/*
 * Entry: 00465521
 * Name: Tran05Mission::PostLoad
 * Namespace: Tran05Mission
 * Signature: bool PostLoad(Tran05Mission * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall Tran05Mission::PostLoad(Tran05Mission *this)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  Tran05Mission_u_124 *pTVar4;
  
  if (missionSave) {
    bVar1 = AiMission::PostLoad((AiMission *)this);
    return bVar1;
  }
  pTVar4 = &this->field18_0x7c;
  iVar3 = 0x11;
  do {
    iVar2 = ConvertHandle((pTVar4->_s_0).player);
    (pTVar4->_s_0).player = iVar2;
    pTVar4 = (Tran05Mission_u_124 *)((int)pTVar4 + 4);
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  bVar1 = AiMission::PostLoad((AiMission *)this);
  return bVar1;
}
