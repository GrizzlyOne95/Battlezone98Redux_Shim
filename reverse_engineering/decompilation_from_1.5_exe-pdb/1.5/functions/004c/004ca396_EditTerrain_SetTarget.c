/*
 * Entry: 004ca396
 * Name: EditTerrain_SetTarget
 * Namespace: Global
 * Signature: void EditTerrain_SetTarget(VECTOR_3D * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl EditTerrain_SetTarget(VECTOR_3D *param_1)

{
  editTerrain.viewCenter.x = param_1->x;
  editTerrain.viewCenter.y = param_1->y;
  editTerrain.viewCenter.z = param_1->z;
  return;
}
