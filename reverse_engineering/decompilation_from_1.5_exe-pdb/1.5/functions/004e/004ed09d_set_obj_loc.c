/*
 * Entry: 004ed09d
 * Name: set_obj_loc
 * Namespace: Global
 * Signature: void set_obj_loc(_OBJ76 * param_1, VECTOR_3D param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl set_obj_loc(_OBJ76 *param_1,VECTOR_3D param_2)

{
  (param_1->transform).posit_x = (double)param_2.x;
  (param_1->transform).posit_y = (double)param_2.y;
  (param_1->transform).posit_z = (double)param_2.z;
  return;
}
