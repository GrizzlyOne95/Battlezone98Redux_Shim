/*
 * Entry: 00411035
 * Name: DemoMission::PostLoad
 * Namespace: DemoMission
 * Signature: bool PostLoad(DemoMission * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall DemoMission::PostLoad(DemoMission *this)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  DemoMission_u_112 *pDVar4;
  
  if (missionSave) {
    bVar1 = AiMission::PostLoad((AiMission *)this);
    return bVar1;
  }
  pDVar4 = &this->field18_0x70;
  iVar3 = 0x11;
  do {
    iVar2 = ConvertHandle((pDVar4->_s_0).get_in_me);
    (pDVar4->_s_0).get_in_me = iVar2;
    pDVar4 = (DemoMission_u_112 *)((int)pDVar4 + 4);
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  bVar1 = AiMission::PostLoad((AiMission *)this);
  return bVar1;
}
