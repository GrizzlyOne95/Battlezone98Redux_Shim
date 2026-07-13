/*
 * Entry: 0050741a
 * Name: AI_BuildingRemove
 * Namespace: Global
 * Signature: void AI_BuildingRemove(tagBUILDING * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl AI_BuildingRemove(tagBUILDING *param_1)

{
  if ((ai_game_initialised != 0) && (teamdata[param_1->team].aicontrol != '\0')) {
    tlog_gdm("AI_BuildingRemove Team %d Building %d\n");
    if (param_1->order == 3) {
      AIBuild_ConstructionEnd(param_1->team,(uint)(param_1->unittypetobuild->prereq).prereqtype);
    }
    AI_Parts_SubtractBuildingFromTeam(param_1);
  }
  return;
}
