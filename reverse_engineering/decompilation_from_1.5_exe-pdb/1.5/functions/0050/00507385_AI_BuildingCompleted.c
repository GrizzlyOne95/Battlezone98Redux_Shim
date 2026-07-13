/*
 * Entry: 00507385
 * Name: AI_BuildingCompleted
 * Namespace: Global
 * Signature: void AI_BuildingCompleted(tagBUILDING * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl AI_BuildingCompleted(tagBUILDING *param_1)

{
  if (teamdata[param_1->team].aicontrol != '\0') {
    tlog_gdm("AI_BuildingCompleted Team %d Building %d\n");
    AIBuild_ConstructionEnd(param_1->team,(uint)param_1->buildingtype->prereqtype);
    AI_Parts_AddBuildingToTeam(param_1);
  }
  return;
}
