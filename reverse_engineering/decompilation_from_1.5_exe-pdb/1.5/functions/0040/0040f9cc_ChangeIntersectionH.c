/*
 * Entry: 0040f9cc
 * Name: ChangeIntersectionH
 * Namespace: Global
 * Signature: void ChangeIntersectionH(int param_1, int param_2, VECTOR_2D param_3, VECTOR_2D param_4, float * param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
ChangeIntersectionH(int param_1,int param_2,VECTOR_2D param_3,VECTOR_2D param_4,float *param_5)

{
  float fVar1;
  float *in_ECX;
  
  if ((float)param_1 <= (float)param_2) {
    fVar1 = 0.9;
  }
  else {
    fVar1 = 0.1;
  }
  if ((param_3.z == 0.0) ||
     (fVar1 = (((float)param_1 + fVar1) - (float)param_2) / param_3.z, fVar1 < 0.0)) {
    fVar1 = 1e+30;
  }
  if (*in_ECX <= fVar1) {
    return;
  }
  *in_ECX = fVar1;
  return;
}
