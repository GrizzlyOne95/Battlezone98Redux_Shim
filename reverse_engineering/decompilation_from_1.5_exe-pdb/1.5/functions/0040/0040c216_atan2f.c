/*
 * Entry: 0040c216
 * Name: atan2f
 * Namespace: Global
 * Signature: float atan2f(float param_1, float param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

float __cdecl atan2f(float param_1,float param_2)

{
  float10 fVar1;
  
  fVar1 = (float10)fpatan((float10)param_1,(float10)param_2);
  return (float)fVar1;
}
