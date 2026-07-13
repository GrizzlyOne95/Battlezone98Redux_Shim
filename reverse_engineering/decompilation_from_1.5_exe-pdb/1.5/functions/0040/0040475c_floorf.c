/*
 * Entry: 0040475c
 * Name: floorf
 * Namespace: Global
 * Signature: float floorf(float param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

float __cdecl floorf(float param_1)

{
  float10 fVar1;
  
  fVar1 = (float10)floor((double)param_1);
  return (float)fVar1;
}
