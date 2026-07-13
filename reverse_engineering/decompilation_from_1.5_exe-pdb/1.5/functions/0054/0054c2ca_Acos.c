/*
 * Entry: 0054c2ca
 * Name: Acos
 * Namespace: Global
 * Signature: float Acos(float param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

float __cdecl Acos(float param_1)

{
  float10 fVar1;
  
  fVar1 = (float10)fpatan((float10)SQRT(1.0 - param_1 * param_1),(float10)param_1);
  return (float)fVar1;
}
