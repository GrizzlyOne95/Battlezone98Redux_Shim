/*
 * Entry: 00508ae4
 * Name: AI_Parts_SubtractBuildingFromTeam
 * Namespace: Global
 * Signature: void AI_Parts_SubtractBuildingFromTeam(tagBUILDING * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl AI_Parts_SubtractBuildingFromTeam(tagBUILDING *param_1)

{
  tag_team *ptVar1;
  int iVar2;
  int iVar3;
  
  ptVar1 = AI_map->team[param_1->team];
  iVar2 = param_1->tiley / AI_map->gridside;
  iVar3 = param_1->tilex / AI_map->gridside;
  Debug_Assert((uint)(-1 < iVar2),0x68,".\\Schedule\\Ai_parts.cpp","build_gridrow >= 0");
  Debug_Assert((uint)(-1 < iVar3),0x69,".\\Schedule\\Ai_parts.cpp","build_gridcolumn >= 0");
  Debug_Assert((uint)(iVar2 < (ptVar1->strategic_targets).grid_rows),0x6a,
               ".\\Schedule\\Ai_parts.cpp","build_gridrow < team->strategic_targets.grid_rows");
  Debug_Assert((uint)(iVar3 < (ptVar1->strategic_targets).grid_columns),0x6b,
               ".\\Schedule\\Ai_parts.cpp","build_gridcolumn < team->strategic_targets.grid_columns"
              );
  return;
}
