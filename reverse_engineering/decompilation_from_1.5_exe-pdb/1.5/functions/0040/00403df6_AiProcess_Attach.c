/*
 * Entry: 00403df6
 * Name: AiProcess::Attach
 * Namespace: AiProcess
 * Signature: void Attach(AiMission * param_1, GameObject * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl AiProcess::Attach(AiMission *param_1,GameObject *param_2)

{
  long lVar1;
  int iVar2;
  int iVar3;
  RtimeClass *pRVar4;
  SObject *pSVar5;
  char *pcVar6;
  int *piVar7;
  
  piVar7 = &param_2->_padding_;
  iVar2 = (**(code **)*piVar7)();
  pcVar6 = (char *)(iVar2 + 0x8c);
  if (pcVar6 != (char *)0x0) {
    iVar3 = (**(code **)(*piVar7 + 4))();
    lVar1 = GameObject::userTeamNumber;
    if (iVar3 != 0) {
      iVar3 = (**(code **)(*piVar7 + 4))();
      if (iVar3 != lVar1) {
        pcVar6 = (char *)(iVar2 + 0xac);
      }
    }
    pRVar4 = RtimeClass::GetRtimeClass(pcVar6);
    if (pRVar4 != (RtimeClass *)0x0) {
      pSVar5 = (*pRVar4->m_pfnCreateObject)();
      (**(code **)(pSVar5->_padding_ + 0x18))(param_1,param_2);
    }
  }
  return;
}
