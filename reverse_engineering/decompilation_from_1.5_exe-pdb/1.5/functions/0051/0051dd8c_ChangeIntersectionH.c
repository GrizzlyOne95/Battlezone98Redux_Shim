/*
 * Entry: 0051dd8c
 * Name: ChangeIntersectionH
 * Namespace: Global
 * Signature: void ChangeIntersectionH(long param_1, long param_2, VECTOR_3D_LONG param_3, VECTOR_3D param_4, float * param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
ChangeIntersectionH(long param_1,long param_2,VECTOR_3D_LONG param_3,VECTOR_3D param_4,
                   float *param_5)

{
  float fVar1;
  float *in_ECX;
  
  if ((double)param_1 <= (double)CONCAT44(param_3.x._0_4_,param_2)) {
    fVar1 = (float)param_1 + 0.9;
  }
  else {
    fVar1 = (float)param_1 + 0.1;
  }
  if ((param_3.z._4_4_ == 0.0) ||
     (fVar1 = (fVar1 - (float)(double)CONCAT44(param_3.x._0_4_,param_2)) / param_3.z._4_4_,
     fVar1 < 0.0)) {
    fVar1 = 1e+30;
  }
  if (*in_ECX <= fVar1) {
    return;
  }
  *in_ECX = fVar1;
  return;
}
