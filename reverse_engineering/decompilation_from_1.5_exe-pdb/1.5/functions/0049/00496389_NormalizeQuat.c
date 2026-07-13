/*
 * Entry: 00496389
 * Name: NormalizeQuat
 * Namespace: Global
 * Signature: void NormalizeQuat(QUAT * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl NormalizeQuat(QUAT *param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  
  fVar1 = (param_1->n).z;
  fVar2 = (param_1->n).y;
  fVar3 = (param_1->n).x;
  fVar1 = fVar3 * fVar3 + fVar2 * fVar2 + fVar1 * fVar1 + param_1->w * param_1->w;
  if (ABS(fVar1) < 0.0001) {
    fVar1 = 0.0001;
  }
  fVar1 = 1.0 / SQRT(fVar1);
  (param_1->n).x = (param_1->n).x * fVar1;
  (param_1->n).y = (param_1->n).y * fVar1;
  (param_1->n).z = (param_1->n).z * fVar1;
  param_1->w = fVar1 * param_1->w;
  return;
}
