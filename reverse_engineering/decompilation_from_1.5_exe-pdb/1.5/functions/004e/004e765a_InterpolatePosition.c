/*
 * Entry: 004e765a
 * Name: InterpolatePosition
 * Namespace: Global
 * Signature: void InterpolatePosition(float * param_1, float param_2, float * param_3, float * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl InterpolatePosition(float *param_1,float param_2,float *param_3,float *param_4)

{
  float fVar1;
  float *in_EAX;
  float *in_ECX;
  float *in_EDX;
  
  fVar1 = 1.0 - (float)param_1;
  *in_EDX = *in_EAX * (float)param_1 + *in_ECX * fVar1;
  in_EDX[1] = in_EAX[1] * (float)param_1 + in_ECX[1] * fVar1;
  in_EDX[2] = (float)param_1 * in_EAX[2] + in_ECX[2] * fVar1;
  return;
}
