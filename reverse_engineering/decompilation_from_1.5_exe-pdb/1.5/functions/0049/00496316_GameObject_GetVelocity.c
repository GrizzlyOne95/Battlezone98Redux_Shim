/*
 * Entry: 00496316
 * Name: GameObject_GetVelocity
 * Namespace: Global
 * Signature: void GameObject_GetVelocity(_OBJ76 * param_1, VECTOR_3D * param_2, float * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl GameObject_GetVelocity(_OBJ76 *param_1,VECTOR_3D *param_2,float *param_3)

{
  float fVar1;
  void *pvVar2;
  
  if (param_1 == (_OBJ76 *)0x0) {
    pvVar2 = (void *)0x0;
  }
  else {
    pvVar2 = param_1->gameObj;
  }
  if (pvVar2 == (void *)0x0) {
    fVar1 = 0.0;
    param_2->x = 0.0;
    param_2->y = 0.0;
    param_2->z = 0.0;
  }
  else {
    param_2->x = *(float *)((int)pvVar2 + 0x120);
    param_2->y = *(float *)((int)pvVar2 + 0x124);
    param_2->z = *(float *)((int)pvVar2 + 0x128);
    fVar1 = *(float *)((int)pvVar2 + 0x110);
  }
  *param_3 = fVar1;
  return;
}
