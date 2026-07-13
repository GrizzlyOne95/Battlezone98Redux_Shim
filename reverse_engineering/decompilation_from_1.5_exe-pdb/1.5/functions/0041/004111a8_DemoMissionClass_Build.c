/*
 * Entry: 004111a8
 * Name: DemoMissionClass::Build
 * Namespace: DemoMissionClass
 * Signature: AiMission * Build(DemoMissionClass * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

AiMission * __thiscall DemoMissionClass::Build(DemoMissionClass *this)

{
  DemoMission *pDVar1;
  
  pDVar1 = operator_new(0xe8);
  if (pDVar1 != (DemoMission *)0x0) {
    pDVar1 = DemoMission::DemoMission(pDVar1);
    return (AiMission *)pDVar1;
  }
  return (AiMission *)0x0;
}
