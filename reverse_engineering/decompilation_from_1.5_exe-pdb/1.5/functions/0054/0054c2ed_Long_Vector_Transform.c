/*
 * Entry: 0054c2ed
 * Name: Long_Vector_Transform
 * Namespace: Global
 * Signature: VECTOR_3D_LONG * Long_Vector_Transform(VECTOR_3D_LONG * __return_storage_ptr__, VECTOR_3D * param_1, MAT_3D * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

VECTOR_3D_LONG * __cdecl
Long_Vector_Transform(VECTOR_3D_LONG *__return_storage_ptr__,VECTOR_3D *param_1,MAT_3D *param_2)

{
  float *in_ECX;
  float *in_EDX;
  
  __return_storage_ptr__->x =
       (double)(*in_ECX * *in_EDX + in_EDX[6] * in_ECX[2] + in_EDX[3] * in_ECX[1] +
               (float)*(double *)(in_EDX + 10));
  __return_storage_ptr__->y =
       (double)(in_EDX[7] * in_ECX[2] + in_EDX[1] * *in_ECX + in_EDX[4] * in_ECX[1] +
               (float)*(double *)(in_EDX + 0xc));
  __return_storage_ptr__->z =
       (double)(in_EDX[8] * in_ECX[2] + in_EDX[2] * *in_ECX + in_EDX[5] * in_ECX[1] +
               (float)*(double *)(in_EDX + 0xe));
  return __return_storage_ptr__;
}
