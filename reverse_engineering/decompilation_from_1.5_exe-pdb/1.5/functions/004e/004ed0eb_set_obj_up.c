/*
 * Entry: 004ed0eb
 * Name: set_obj_up
 * Namespace: Global
 * Signature: void set_obj_up(_OBJ76 * param_1, VECTOR_3D param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl set_obj_up(_OBJ76 *param_1,VECTOR_3D param_2)

{
  (param_1->transform).up_x = param_2.x;
  (param_1->transform).up_y = param_2.y;
  (param_1->transform).up_z = param_2.z;
  return;
}
