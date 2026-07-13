/*
 * Entry: 0050746c
 * Name: AI_BuildingRemoveUnderConstruction
 * Namespace: Global
 * Signature: void AI_BuildingRemoveUnderConstruction(tagBUILDING * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl AI_BuildingRemoveUnderConstruction(tagBUILDING *param_1)

{
  if ((ai_game_initialised != 0) && (teamdata[param_1->team].aicontrol != '\0')) {
    tlog_gdm("AI_BuildingRemoveUnderConstruction Team %d Building %d\n");
    AIBuild_ConstructionEnd(param_1->team,(uint)param_1->buildingtype->prereqtype);
  }
  return;
}
