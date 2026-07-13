/*
 * Entry: 005074ae
 * Name: AI_BuildingRemoveUnderUpgrade
 * Namespace: Global
 * Signature: void AI_BuildingRemoveUnderUpgrade(tagBUILDING * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl AI_BuildingRemoveUnderUpgrade(tagBUILDING *param_1)

{
  if ((ai_game_initialised != 0) && (teamdata[param_1->team].aicontrol != '\0')) {
    tlog_gdm("AI_BuildingRemoveUnderUpgrade Team %d Building %d\n");
    Debug_Assert((int)param_1->buildingtype->upgradeto,0x331,".\\Schedule\\Ai.cpp",
                 "building->buildingtype->upgradeto");
    AIBuild_ConstructionEnd(param_1->team,(uint)param_1->buildingtype->upgradeto->prereqtype);
  }
  return;
}
