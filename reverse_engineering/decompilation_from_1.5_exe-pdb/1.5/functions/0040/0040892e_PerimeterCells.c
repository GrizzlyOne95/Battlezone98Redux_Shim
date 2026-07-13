/*
 * Entry: 0040892e
 * Name: PerimeterCells
 * Namespace: Global
 * Signature: void PerimeterCells(float param_1, float param_2, float param_3, float param_4, bool param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl PerimeterCells(float param_1,float param_2,float param_3,float param_4,bool param_5)

{
  code *pcVar1;
  
  pcVar1 = PerimeterBlock;
  if (!param_5) {
    pcVar1 = PerimeterUnblock;
  }
  UpdateCells(param_1,param_2,param_3,param_4,pcVar1);
  return;
}
