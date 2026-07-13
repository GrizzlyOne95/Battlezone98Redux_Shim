/*
 * Entry: 004ed0b7
 * Name: set_obj_front
 * Namespace: Global
 * Signature: void set_obj_front(_OBJ76 * param_1, VECTOR_3D param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl set_obj_front(_OBJ76 *param_1,VECTOR_3D param_2)

{
  (param_1->transform).front_x = param_2.x;
  (param_1->transform).front_y = param_2.y;
  (param_1->transform).front_z = param_2.z;
  return;
}
