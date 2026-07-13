/*
 * Entry: 004ca032
 * Name: EditTerrain::WorldToGrid
 * Namespace: EditTerrain
 * Signature: void WorldToGrid(EditTerrain * this, FLOAT2INT * param_1, FLOAT2INT * param_2, VECTOR_3D * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
EditTerrain::WorldToGrid(EditTerrain *this,FLOAT2INT *param_1,FLOAT2INT *param_2,VECTOR_3D *param_3)

{
  param_1->f = (double)(param_3->x * Terrain.Grid_Scale + 0.5 + (float)Float2Int);
  param_2->f = (double)(param_3->z * Terrain.Grid_Scale + 0.5 + (float)Float2Int);
  return;
}
