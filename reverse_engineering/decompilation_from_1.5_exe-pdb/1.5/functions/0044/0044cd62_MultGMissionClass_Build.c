/*
 * Entry: 0044cd62
 * Name: MultGMissionClass::Build
 * Namespace: MultGMissionClass
 * Signature: AiMission * Build(MultGMissionClass * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

AiMission * __thiscall MultGMissionClass::Build(MultGMissionClass *this)

{
  MultGMission *this_00;
  AiMission *pAVar1;
  
  this_00 = operator_new(0x40);
  if (this_00 != (MultGMission *)0x0) {
    pAVar1 = (AiMission *)MultGMission::MultGMission(this_00);
    return pAVar1;
  }
  return (AiMission *)0x0;
}
