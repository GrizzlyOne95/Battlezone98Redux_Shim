/*
 * Entry: 004f0594
 * Name: Camera_World_to_Camera
 * Namespace: Global
 * Signature: VECTOR_3D * Camera_World_to_Camera(VECTOR_3D * __return_storage_ptr__, CAMERA * param_1, double param_2, double param_3, double param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

VECTOR_3D * __cdecl
Camera_World_to_Camera
          (VECTOR_3D *__return_storage_ptr__,CAMERA *param_1,double param_2,double param_3,
          double param_4)

{
  __return_storage_ptr__->x =
       (param_1->Matrix).right_x * (float)param_2 +
       (param_1->Matrix).front_x * (float)param_4 + (param_1->Matrix).up_x * (float)param_3 +
       (float)(param_1->Matrix).posit_x;
  __return_storage_ptr__->y =
       (param_1->Matrix).front_y * (float)param_4 +
       (param_1->Matrix).up_y * (float)param_3 + (param_1->Matrix).right_y * (float)param_2 +
       (float)(param_1->Matrix).posit_y;
  __return_storage_ptr__->z =
       (param_1->Matrix).front_z * (float)param_4 +
       (param_1->Matrix).up_z * (float)param_3 + (param_1->Matrix).right_z * (float)param_2 +
       (float)(param_1->Matrix).posit_z;
  return __return_storage_ptr__;
}
