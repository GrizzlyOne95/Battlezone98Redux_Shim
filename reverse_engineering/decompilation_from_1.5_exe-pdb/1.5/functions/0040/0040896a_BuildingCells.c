/*
 * Entry: 0040896a
 * Name: BuildingCells
 * Namespace: Global
 * Signature: void BuildingCells(float param_1, float param_2, float param_3, float param_4, bool param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl BuildingCells(float param_1,float param_2,float param_3,float param_4,bool param_5)

{
  code *pcVar1;
  
  pcVar1 = BuildingBlock;
  if (!param_5) {
    pcVar1 = BuildingUnblock;
  }
  UpdateCells(param_1,param_2,param_3,param_4,pcVar1);
  return;
}
