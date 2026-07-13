/*
 * Entry: 0054c7f7
 * Name: Slerp
 * Namespace: Global
 * Signature: QUAT * Slerp(QUAT * __return_storage_ptr__, QUAT * param_1, QUAT * param_2, float param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

QUAT * __cdecl Slerp(QUAT *__return_storage_ptr__,QUAT *param_1,QUAT *param_2,float param_3)

{
  float fVar1;
  float fVar2;
  SINCOS SVar3;
  SINCOS SVar4;
  float fVar5;
  float local_14;
  float local_c;
  
  fVar1 = param_2->w * param_1->w +
          (param_1->n).y * (param_2->n).y +
          (param_1->n).z * (param_2->n).z + (param_1->n).x * (param_2->n).x;
  if (fVar1 + 1.0 <= 0.0001) {
    (__return_storage_ptr__->n).x = -(param_1->n).y;
    (__return_storage_ptr__->n).y = (param_1->n).x;
    (__return_storage_ptr__->n).z = param_1->w;
    __return_storage_ptr__->w = (param_1->n).z;
    SVar3 = SinCos((1.0 - param_3) * 1.5707964);
    SinCos(param_3 * 1.5707964);
    local_14 = SVar3.Sin;
    __return_storage_ptr__->w = local_14 * param_1->w + __return_storage_ptr__->w * local_c;
    (__return_storage_ptr__->n).x =
         (param_1->n).x * local_14 + (__return_storage_ptr__->n).x * local_c;
    (__return_storage_ptr__->n).y =
         (__return_storage_ptr__->n).y * local_c + (param_1->n).y * local_14;
    (__return_storage_ptr__->n).z =
         local_c * (__return_storage_ptr__->n).z + (param_1->n).z * local_14;
  }
  else {
    if (1.0 - fVar1 <= 0.0001) {
      local_14 = 1.0 - param_3;
    }
    else {
      fVar5 = Acos(fVar1);
      SVar3 = SinCos(fVar5);
      fVar1 = 1.0 / local_c;
      SVar4 = SinCos((1.0 - param_3) * fVar5);
      SinCos(fVar5 * param_3);
      local_14 = SVar4.Sin;
      local_14 = local_14 * fVar1;
      local_c = SVar3.Sin;
      param_3 = local_c * fVar1;
    }
    __return_storage_ptr__->w = local_14 * param_1->w + param_2->w * param_3;
    (__return_storage_ptr__->n).x = (param_2->n).x * param_3 + (param_1->n).x * local_14;
    (__return_storage_ptr__->n).y = param_3 * (param_2->n).y + (param_1->n).y * local_14;
    (__return_storage_ptr__->n).z = param_3 * (param_2->n).z + (param_1->n).z * local_14;
  }
  fVar1 = (__return_storage_ptr__->n).z;
  fVar5 = (__return_storage_ptr__->n).y;
  fVar2 = (__return_storage_ptr__->n).x;
  fVar1 = fVar1 * fVar1 + fVar5 * fVar5 + fVar2 * fVar2 +
          __return_storage_ptr__->w * __return_storage_ptr__->w;
  if (0.0001 < 1.0 - fVar1) {
    fVar1 = (1.0 / SQRT(fVar1)) * 0.9999;
    (__return_storage_ptr__->n).x = (__return_storage_ptr__->n).x * fVar1;
    (__return_storage_ptr__->n).y = (__return_storage_ptr__->n).y * fVar1;
    (__return_storage_ptr__->n).z = (__return_storage_ptr__->n).z * fVar1;
    __return_storage_ptr__->w = fVar1 * __return_storage_ptr__->w;
  }
  return __return_storage_ptr__;
}
