/*
 * Entry: 004f0606
 * Name: Camera_Get_Position
 * Namespace: Global
 * Signature: VECTOR_3D * Camera_Get_Position(VECTOR_3D * __return_storage_ptr__, CAMERA * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

VECTOR_3D * __cdecl Camera_Get_Position(VECTOR_3D *__return_storage_ptr__,CAMERA *param_1)

{
  __return_storage_ptr__->x = (float)param_1->View_Pyramid[0].x;
  __return_storage_ptr__->y = (float)param_1->View_Pyramid[0].y;
  __return_storage_ptr__->z = (float)param_1->View_Pyramid[0].z;
  return __return_storage_ptr__;
}
