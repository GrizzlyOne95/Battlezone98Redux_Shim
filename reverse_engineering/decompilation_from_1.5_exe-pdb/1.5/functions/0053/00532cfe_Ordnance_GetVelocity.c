/*
 * Entry: 00532cfe
 * Name: Ordnance_GetVelocity
 * Namespace: Global
 * Signature: void Ordnance_GetVelocity(_OBJ76 * param_1, VECTOR_3D * param_2, float * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Ordnance_GetVelocity(_OBJ76 *param_1,VECTOR_3D *param_2,float *param_3)

{
  void *pvVar1;
  
  if (param_1 == (_OBJ76 *)0x0) {
    pvVar1 = (void *)0x0;
  }
  else {
    pvVar1 = param_1->class_ptr;
  }
  param_2->x = *(float *)((int)pvVar1 + 0x34);
  param_2->y = *(float *)((int)pvVar1 + 0x38);
  param_2->z = *(float *)((int)pvVar1 + 0x3c);
  *param_3 = *(float *)((int)pvVar1 + 0x24);
  return;
}
