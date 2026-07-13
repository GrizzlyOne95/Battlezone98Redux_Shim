/*
 * Entry: 0044be72
 * Name: MPMissionClass::Build
 * Namespace: MPMissionClass
 * Signature: AiMission * Build(MPMissionClass * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

AiMission * __thiscall MPMissionClass::Build(MPMissionClass *this)

{
  MPMission *this_00;
  AiMission *pAVar1;
  
  this_00 = operator_new(0x40);
  if (this_00 != (MPMission *)0x0) {
    pAVar1 = (AiMission *)MPMission::MPMission(this_00);
    return pAVar1;
  }
  return (AiMission *)0x0;
}
