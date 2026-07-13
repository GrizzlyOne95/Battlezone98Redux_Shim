/*
 * Entry: 004963ea
 * Name: MySlerp
 * Namespace: Global
 * Signature: QUAT * MySlerp(QUAT * __return_storage_ptr__, QUAT * param_1, QUAT * param_2, float param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

QUAT * __cdecl MySlerp(QUAT *__return_storage_ptr__,QUAT *param_1,QUAT *param_2,float param_3)

{
  float fVar1;
  float10 fVar2;
  float10 fVar3;
  float10 fVar4;
  float local_14;
  float local_10;
  float local_c;
  
  fVar4 = (float10)param_2->w * (float10)param_1->w +
          (float10)(param_1->n).y * (float10)(param_2->n).y +
          (float10)(param_1->n).z * (float10)(param_2->n).z +
          (float10)(param_1->n).x * (float10)(param_2->n).x;
  if ((float10)0 <= fVar4) {
    local_14 = (param_2->n).x;
    local_10 = (param_2->n).y;
    local_c = (param_2->n).z;
    fVar1 = param_2->w;
  }
  else {
    fVar4 = -fVar4;
    local_14 = -(param_2->n).x;
    local_10 = -(param_2->n).y;
    local_c = -(param_2->n).z;
    fVar1 = -param_2->w;
  }
  if ((float10)1 - fVar4 <= (float10)9.999999747378752e-05) {
    fVar4 = (float10)1 - (float10)param_3;
    fVar2 = (float10)param_3;
  }
  else {
    fVar2 = (float10)__CIacos();
    fVar3 = (float10)fsin(fVar2);
    fVar3 = (float10)1 / fVar3;
    fVar4 = (float10)fsin(((float10)1 - (float10)param_3) * fVar2);
    fVar4 = fVar4 * fVar3;
    fVar2 = (float10)fsin(fVar2 * (float10)param_3);
    fVar2 = fVar2 * fVar3;
  }
  (__return_storage_ptr__->n).x =
       (float)(fVar2 * (float10)local_14 + (float10)(param_1->n).x * fVar4);
  (__return_storage_ptr__->n).y =
       (float)(fVar2 * (float10)local_10 + (float10)(param_1->n).y * fVar4);
  (__return_storage_ptr__->n).z =
       (float)(fVar2 * (float10)local_c + (float10)(param_1->n).z * fVar4);
  __return_storage_ptr__->w = (float)(fVar4 * (float10)param_1->w + fVar2 * (float10)fVar1);
  return __return_storage_ptr__;
}
