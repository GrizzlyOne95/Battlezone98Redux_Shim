/*
 * Entry: 004ed79e
 * Name: Fmod1
 * Namespace: Global
 * Signature: float Fmod1(float param_1, float param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

float __cdecl Fmod1(float param_1,float param_2)

{
  float fVar1;
  
  fVar1 = param_1 - (param_1 / param_2) * param_2;
  if (fVar1 < 0.0) {
    fVar1 = fVar1 + param_2;
  }
  return fVar1;
}
