/*
 * Entry: 004ed0d1
 * Name: set_obj_right
 * Namespace: Global
 * Signature: void set_obj_right(_OBJ76 * param_1, VECTOR_3D param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl set_obj_right(_OBJ76 *param_1,VECTOR_3D param_2)

{
  (param_1->transform).right_x = param_2.x;
  (param_1->transform).right_y = param_2.y;
  (param_1->transform).right_z = param_2.z;
  return;
}
