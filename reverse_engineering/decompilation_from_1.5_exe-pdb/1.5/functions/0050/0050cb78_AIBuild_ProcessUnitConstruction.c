/*
 * Entry: 0050cb78
 * Name: AIBuild_ProcessUnitConstruction
 * Namespace: Global
 * Signature: void AIBuild_ProcessUnitConstruction(tag_team * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl AIBuild_ProcessUnitConstruction(tag_team *param_1)

{
  tagBUILDING *ptVar1;
  tagITERATOR local_54;
  
  ITERATE_BUILDINIT_TEAM(&local_54,param_1->team_ID);
  ptVar1 = Iterate_BuildNext(&local_54);
  while (ptVar1 != (tagBUILDING *)0x0) {
    if (((ptVar1->buildingtype->field_0x24 & 2) != 0) &&
       ((ptVar1->order == 1 || (ptVar1->order == 0)))) {
      AIBuild_ProcessBuilding(param_1,ptVar1);
    }
    ptVar1 = Iterate_BuildNext(&local_54);
  }
  return;
}
