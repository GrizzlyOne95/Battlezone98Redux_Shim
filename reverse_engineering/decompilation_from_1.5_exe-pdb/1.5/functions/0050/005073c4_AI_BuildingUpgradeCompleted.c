/*
 * Entry: 005073c4
 * Name: AI_BuildingUpgradeCompleted
 * Namespace: Global
 * Signature: void AI_BuildingUpgradeCompleted(tagBUILDING * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl AI_BuildingUpgradeCompleted(tagBUILDING *param_1)

{
  if (teamdata[param_1->team].aicontrol != '\0') {
    tlog_gdm("AI_BuildingUpgradeCompleted Team %d Building %d\n");
    Debug_Assert((int)param_1->buildingtype->upgradeto,0x2d6,".\\Schedule\\Ai.cpp",
                 "building->buildingtype->upgradeto");
    AIBuild_ConstructionEnd(param_1->team,(uint)param_1->buildingtype->upgradeto->prereqtype);
  }
  return;
}
