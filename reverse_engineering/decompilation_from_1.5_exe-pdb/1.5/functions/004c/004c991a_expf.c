/*
 * Entry: 004c991a
 * Name: expf
 * Namespace: Global
 * Signature: float expf(float param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

float __cdecl expf(float param_1)

{
  float10 fVar1;
  
  fVar1 = (float10)__CIexp();
  return (float)fVar1;
}
