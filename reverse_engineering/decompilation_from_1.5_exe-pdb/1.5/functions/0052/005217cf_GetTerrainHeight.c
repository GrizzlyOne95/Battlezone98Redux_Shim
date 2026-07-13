/*
 * Entry: 005217cf
 * Name: GetTerrainHeight
 * Namespace: Global
 * Signature: float GetTerrainHeight(int param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

float __cdecl GetTerrainHeight(int param_1,int param_2)

{
  ushort *puVar1;
  
  puVar1 = GetZonePtr(param_1,param_2);
  return (float)(*puVar1 & 0xfff) * 0.01;
}
