/*
 * Entry: 0040fa28
 * Name: ChangeIntersectionV
 * Namespace: Global
 * Signature: void ChangeIntersectionV(int param_1, int param_2, VECTOR_2D param_3, VECTOR_2D param_4, float * param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
ChangeIntersectionV(int param_1,int param_2,VECTOR_2D param_3,VECTOR_2D param_4,float *param_5)

{
  float fVar1;
  float *in_ECX;
  
  if ((float)param_1 <= param_3.x) {
    fVar1 = 0.9;
  }
  else {
    fVar1 = 0.1;
  }
  if ((param_4.x == 0.0) ||
     (fVar1 = (((float)param_1 + fVar1) - param_3.x) / param_4.x, fVar1 < 0.0)) {
    fVar1 = 1e+30;
  }
  if (*in_ECX <= fVar1) {
    return;
  }
  *in_ECX = fVar1;
  return;
}
