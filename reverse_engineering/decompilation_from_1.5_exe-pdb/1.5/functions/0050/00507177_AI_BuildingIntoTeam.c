/*
 * Entry: 00507177
 * Name: AI_BuildingIntoTeam
 * Namespace: Global
 * Signature: void AI_BuildingIntoTeam(tagBUILDING * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl AI_BuildingIntoTeam(tagBUILDING *param_1)

{
  tlog_gdm("AI   Team %d Building %d");
  AI_Parts_AddBuildingToTeam(param_1);
  return;
}
