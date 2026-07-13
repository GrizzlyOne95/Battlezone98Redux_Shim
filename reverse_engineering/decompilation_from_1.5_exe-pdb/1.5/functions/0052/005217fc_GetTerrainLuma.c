/*
 * Entry: 005217fc
 * Name: GetTerrainLuma
 * Namespace: Global
 * Signature: int GetTerrainLuma(double param_1, double param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl GetTerrainLuma(double param_1,double param_2)

{
  double dVar1;
  byte *pbVar2;
  
  dVar1 = (double)((float)param_1 * Terrain.Grid_Scale + (float)Float2Int);
  pbVar2 = GetNormalPtr(SUB84(dVar1,0),(int)((ulonglong)dVar1 >> 0x20));
  return (uint)*pbVar2;
}
