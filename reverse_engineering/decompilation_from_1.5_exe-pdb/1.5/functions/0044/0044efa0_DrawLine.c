/*
 * Entry: 0044efa0
 * Name: DrawLine
 * Namespace: Global
 * Signature: void DrawLine(float param_1, float param_2, float param_3, float param_4, long param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl DrawLine(float param_1,float param_2,float param_3,float param_4,long param_5)

{
  long in_EAX;
  
  WorldLine(Terrain.Grid_Size * param_1,param_2 * Terrain.Grid_Size,param_3 * Terrain.Grid_Size,
            param_4 * Terrain.Grid_Size,in_EAX);
  return;
}
