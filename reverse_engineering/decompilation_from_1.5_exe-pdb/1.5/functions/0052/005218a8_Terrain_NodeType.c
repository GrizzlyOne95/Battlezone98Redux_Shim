/*
 * Entry: 005218a8
 * Name: Terrain_NodeType
 * Namespace: Global
 * Signature: long Terrain_NodeType(double param_1, double param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

long __cdecl Terrain_NodeType(double param_1,double param_2)

{
  float fVar1;
  ushort *puVar2;
  undefined4 local_c;
  
  fVar1 = (float)param_1;
  param_1._0_4_ = SUB84((double)(Terrain.Grid_Scale * (float)param_2 + (float)Float2Int),0);
  local_c = SUB84((double)(fVar1 * Terrain.Grid_Scale + (float)Float2Int),0);
  puVar2 = GetTilePtr(local_c,param_1._0_4_);
  return (uint)(*puVar2 >> 0xc);
}
