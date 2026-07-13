/*
 * Entry: 0054c166
 * Name: Atan2
 * Namespace: Global
 * Signature: float Atan2(float param_1, float param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

float __cdecl Atan2(float param_1,float param_2)

{
  float10 fVar1;
  
  fVar1 = (float10)fpatan((float10)param_2,(float10)param_1);
  return (float)fVar1;
}
