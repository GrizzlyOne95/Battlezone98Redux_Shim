/*
 * Entry: 00522088
 * Name: RecomputeTerrainValues
 * Namespace: Global
 * Signature: void RecomputeTerrainValues(int param_1, int param_2, int param_3, int param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl RecomputeTerrainValues(int param_1,int param_2,int param_3,int param_4)

{
  long unaff_EBX;
  long unaff_ESI;
  int iVar1;
  
  for (; iVar1 = param_2, param_1 <= param_3; param_1 = param_1 + 1) {
    for (; iVar1 <= param_4; iVar1 = iVar1 + 1) {
      ComputeNormal(unaff_ESI,unaff_EBX);
      ComputeCoplanarFlags(param_1,iVar1);
    }
  }
  terrainChanged = 1;
  return;
}
