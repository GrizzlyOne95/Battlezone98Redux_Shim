/*
 * Entry: 004ed787
 * Name: Fmod
 * Namespace: Global
 * Signature: float Fmod(float param_1, float param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

float __cdecl Fmod(float param_1,float param_2)

{
  return param_1 - (param_1 / param_2) * param_2;
}
