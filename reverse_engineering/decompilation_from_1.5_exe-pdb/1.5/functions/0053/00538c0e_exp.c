/*
 * Entry: 00538c0e
 * Name: exp
 * Namespace: Global
 * Signature: float exp(float param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

float __cdecl exp(float param_1)

{
  float10 fVar1;
  
  fVar1 = (float10)__CIexp();
  return (float)fVar1;
}
