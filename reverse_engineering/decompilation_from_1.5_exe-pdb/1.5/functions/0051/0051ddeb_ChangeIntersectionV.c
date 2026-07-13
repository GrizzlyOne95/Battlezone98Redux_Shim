/*
 * Entry: 0051ddeb
 * Name: ChangeIntersectionV
 * Namespace: Global
 * Signature: void ChangeIntersectionV(long param_1, long param_2, VECTOR_3D_LONG param_3, VECTOR_3D param_4, float * param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
ChangeIntersectionV(long param_1,long param_2,VECTOR_3D_LONG param_3,VECTOR_3D param_4,
                   float *param_5)

{
  float fVar1;
  float *in_ECX;
  
  if ((double)param_1 <= (double)param_3._12_8_) {
    fVar1 = (float)param_1 + 0.9;
  }
  else {
    fVar1 = (float)param_1 + 0.1;
  }
  if ((param_4.y == 0.0) ||
     (fVar1 = (fVar1 - (float)(double)param_3._12_8_) / param_4.y, fVar1 < 0.0)) {
    fVar1 = 1e+30;
  }
  if (*in_ECX <= fVar1) {
    return;
  }
  *in_ECX = fVar1;
  return;
}
