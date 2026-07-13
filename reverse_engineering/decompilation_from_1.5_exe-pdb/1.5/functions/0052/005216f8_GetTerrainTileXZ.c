/*
 * Entry: 005216f8
 * Name: GetTerrainTileXZ
 * Namespace: Global
 * Signature: void GetTerrainTileXZ(tagPOINT * param_1, VECTOR_3D * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl GetTerrainTileXZ(tagPOINT *param_1,VECTOR_3D *param_2)

{
  float fVar1;
  float fVar2;
  uint local_14;
  uint local_c;
  
  fVar1 = (float)Float2Int;
  local_c = SUB84((double)(param_2->x * Terrain.Grid_Scale + fVar1),0);
  fVar2 = Terrain.Grid_Scale * param_2->z;
  param_1->x = local_c & 0xfffffffe;
  local_14 = SUB84((double)(fVar2 + fVar1),0);
  param_1->y = local_14 & 0xfffffffe;
  return;
}
