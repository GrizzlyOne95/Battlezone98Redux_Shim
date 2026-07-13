/*
 * Entry: 0054bfcf
 * Name: Matrix_to_Quaternion
 * Namespace: Global
 * Signature: QUAT * Matrix_to_Quaternion(QUAT * __return_storage_ptr__, MAT_3D * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

QUAT * __cdecl Matrix_to_Quaternion(QUAT *__return_storage_ptr__,MAT_3D *param_1)

{
  QUAT_INDEX QVar1;
  QUAT_INDEX QVar2;
  float fVar3;
  float *in_ECX;
  uint local_8;
  
  fVar3 = in_ECX[4] + *in_ECX + in_ECX[8];
  if (fVar3 <= 0.0) {
    local_8 = (uint)(*in_ECX < in_ECX[4]);
    if (in_ECX[local_8 * 4] < in_ECX[8]) {
      local_8 = 2;
    }
    QVar1 = QIndex[local_8];
    QVar2 = QIndex[QVar1];
    fVar3 = SQRT(((in_ECX[local_8 * 4] + 1.0) - in_ECX[QVar1 * 4]) - in_ECX[QVar2 * 4]);
    (&(__return_storage_ptr__->n).x)[local_8] = fVar3 * 0.5;
    fVar3 = 0.5 / fVar3;
    __return_storage_ptr__->w = (in_ECX[QVar2 * 3 + QVar1] - in_ECX[QVar1 * 3 + QVar2]) * fVar3;
    (&(__return_storage_ptr__->n).x)[QVar1] =
         (in_ECX[local_8 * 3 + QVar1] + in_ECX[QVar1 * 3 + local_8]) * fVar3;
    (&(__return_storage_ptr__->n).x)[QVar2] =
         (in_ECX[local_8 * 3 + QVar2] + in_ECX[QVar2 * 3 + local_8]) * fVar3;
  }
  else {
    fVar3 = SQRT(fVar3 + 1.0);
    __return_storage_ptr__->w = fVar3 * 0.5;
    fVar3 = 0.5 / fVar3;
    (__return_storage_ptr__->n).x = (in_ECX[7] - in_ECX[5]) * fVar3;
    (__return_storage_ptr__->n).y = (in_ECX[2] - in_ECX[6]) * fVar3;
    (__return_storage_ptr__->n).z = (in_ECX[3] - in_ECX[1]) * fVar3;
  }
  return __return_storage_ptr__;
}
