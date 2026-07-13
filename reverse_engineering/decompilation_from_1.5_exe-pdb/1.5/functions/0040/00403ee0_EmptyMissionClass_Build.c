/*
 * Entry: 00403ee0
 * Name: EmptyMissionClass::Build
 * Namespace: EmptyMissionClass
 * Signature: AiMission * Build(EmptyMissionClass * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

AiMission * __thiscall EmptyMissionClass::Build(EmptyMissionClass *this)

{
  EmptyMission *this_00;
  AiMission *pAVar1;
  
  this_00 = operator_new(0x40);
  if (this_00 != (EmptyMission *)0x0) {
    pAVar1 = (AiMission *)EmptyMission::EmptyMission(this_00);
    return pAVar1;
  }
  return (AiMission *)0x0;
}
