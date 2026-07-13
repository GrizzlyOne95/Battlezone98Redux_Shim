/*
 * Entry: 0049c5d1
 * Name: V3DL_AddMult
 * Namespace: Global
 * Signature: VECTOR_3D_LONG * V3DL_AddMult(VECTOR_3D_LONG * __return_storage_ptr__, VECTOR_3D_LONG param_1, double param_2, VECTOR_3D_LONG param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

VECTOR_3D_LONG * __cdecl
V3DL_AddMult(VECTOR_3D_LONG *__return_storage_ptr__,VECTOR_3D_LONG param_1,double param_2,
            VECTOR_3D_LONG param_3)

{
  undefined4 in_stack_00000008;
  
  __return_storage_ptr__->x =
       (double)CONCAT44(param_3.x._0_4_,param_2._4_4_) *
       (double)CONCAT44(param_2._0_4_,param_1.z._4_4_) +
       (double)CONCAT44(param_1.x._0_4_,in_stack_00000008);
  __return_storage_ptr__->y =
       (double)param_3._4_8_ * (double)CONCAT44(param_2._0_4_,param_1.z._4_4_) +
       (double)param_1._4_8_;
  __return_storage_ptr__->z =
       (double)param_3._12_8_ * (double)CONCAT44(param_2._0_4_,param_1.z._4_4_) +
       (double)param_1._12_8_;
  return __return_storage_ptr__;
}
