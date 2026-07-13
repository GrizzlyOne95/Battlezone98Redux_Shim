/*
 * Entry: 0044efe0
 * Name: DrawStrip
 * Namespace: Global
 * Signature: void DrawStrip(Strip * param_1, int param_2, long param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl DrawStrip(Strip *param_1,int param_2,long param_3)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  
  fVar1 = param_1->x0 * Terrain.Grid_Size;
  fVar2 = param_1->z0 * Terrain.Grid_Size;
  fVar3 = param_1->x1 * Terrain.Grid_Size;
  fVar4 = param_1->z1 * Terrain.Grid_Size;
  if (param_2 != 0) {
    WorldRect(fVar1,fVar2,fVar3,fVar4,param_3);
    return;
  }
  WorldRectOutline(fVar1,fVar2,fVar3,fVar4,param_3);
  return;
}
