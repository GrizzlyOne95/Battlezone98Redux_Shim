/*
 * Entry: 004047d0
 * Name: sinf
 * Namespace: Global
 * Signature: float sinf(float param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

float __cdecl sinf(float param_1)

{
  float10 fVar1;
  
  fVar1 = (float10)fsin((float10)param_1);
  return (float)fVar1;
}
