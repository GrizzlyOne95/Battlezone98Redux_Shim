/*
 * Entry: 004e9d31
 * Name: ClassGetVelocity
 * Namespace: Global
 * Signature: void ClassGetVelocity(_OBJ76 * param_1, VECTOR_3D * param_2, float * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl ClassGetVelocity(_OBJ76 *param_1,VECTOR_3D *param_2,float *param_3)

{
  int iVar1;
  OBJECT_CLASS_T unaff_ESI;
  
  iVar1 = ClassIDtoIndex(unaff_ESI);
  if (funk[iVar1].velocity_fn == (_func___cdecl_void__OBJ76_ptr_VECTOR_3D_ptr_float_ptr *)0x0) {
    param_2->x = 0.0;
    param_2->y = 0.0;
    param_2->z = 0.0;
    *param_3 = 0.0;
  }
  else {
    (*funk[iVar1].velocity_fn)(param_1,param_2,param_3);
  }
  return;
}
