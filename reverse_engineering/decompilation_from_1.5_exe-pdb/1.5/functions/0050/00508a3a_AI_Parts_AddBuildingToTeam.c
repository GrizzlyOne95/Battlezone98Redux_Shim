/*
 * Entry: 00508a3a
 * Name: AI_Parts_AddBuildingToTeam
 * Namespace: Global
 * Signature: void AI_Parts_AddBuildingToTeam(tagBUILDING * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl AI_Parts_AddBuildingToTeam(tagBUILDING *param_1)

{
  tag_team *ptVar1;
  void *pvVar2;
  int iVar3;
  int iVar4;
  
  ptVar1 = AI_map->team[param_1->team];
  iVar3 = param_1->tiley / AI_map->gridside;
  iVar4 = param_1->tilex / AI_map->gridside;
  Debug_Assert((uint)(-1 < iVar3),0x40,".\\Schedule\\Ai_parts.cpp","build_gridrow >= 0");
  Debug_Assert((uint)(-1 < iVar4),0x41,".\\Schedule\\Ai_parts.cpp","build_gridcolumn >= 0");
  Debug_Assert((uint)(iVar3 < (ptVar1->strategic_targets).grid_rows),0x42,
               ".\\Schedule\\Ai_parts.cpp","build_gridrow < team->strategic_targets.grid_rows");
  Debug_Assert((uint)(iVar4 < (ptVar1->strategic_targets).grid_columns),0x43,
               ".\\Schedule\\Ai_parts.cpp","build_gridcolumn < team->strategic_targets.grid_columns"
              );
  pvVar2 = (ptVar1->strategic_targets).grid[iVar3][iVar4];
  if ((ptVar1->strategic_targets).max_our_buildings < *(float *)((int)pvVar2 + 100)) {
    (ptVar1->strategic_targets).max_our_buildings = *(float *)((int)pvVar2 + 100);
  }
  return;
}
