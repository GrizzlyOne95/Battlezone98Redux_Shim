/*
 * Entry: 0050cc81
 * Name: AIBuild_ProcessFacilityUpgrade
 * Namespace: Global
 * Signature: void AIBuild_ProcessFacilityUpgrade(tag_team * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl AIBuild_ProcessFacilityUpgrade(tag_team *param_1)

{
  tagBUILDING *ptVar1;
  int iVar2;
  tagITERATOR local_5c;
  int local_c;
  int local_8;
  
  ITERATE_BUILDINIT_TEAM(&local_5c,param_1->team_ID);
  ptVar1 = Iterate_BuildNext(&local_5c);
  while (ptVar1 != (tagBUILDING *)0x0) {
    iVar2 = Build_CanUpgrade(ptVar1);
    if (iVar2 != 0) {
      iVar2 = AIBuild_BuildListWhatToMakeWith
                        (param_1,(uint)ptVar1->buildingtype->prereqtype,1,&local_c,&local_8,&local_8
                        );
      if (iVar2 != 0) {
        (ptVar1->ai).account = local_c;
        (ptVar1->ai).refundable = ptVar1->buildingtype->upgradeto->cost;
        Build_UpgradeBuilding(ptVar1);
      }
    }
    ptVar1 = Iterate_BuildNext(&local_5c);
  }
  return;
}
