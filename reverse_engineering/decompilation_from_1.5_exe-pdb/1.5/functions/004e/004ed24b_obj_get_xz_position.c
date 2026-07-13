/*
 * Entry: 004ed24b
 * Name: obj_get_xz_position
 * Namespace: Global
 * Signature: VECTOR_2D obj_get_xz_position(_OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

VECTOR_2D __cdecl obj_get_xz_position(_OBJ76 *param_1)

{
  VECTOR_3D *pVVar1;
  VECTOR_2D VVar2;
  VECTOR_3D local_10;
  
  pVVar1 = obj_get_world_position(&local_10,param_1);
  VVar2.z = pVVar1->z;
  VVar2.x = pVVar1->x;
  return VVar2;
}
