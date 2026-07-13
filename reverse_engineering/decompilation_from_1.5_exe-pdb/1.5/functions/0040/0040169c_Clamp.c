/*
 * Entry: 0040169c
 * Name: Clamp
 * Namespace: Global
 * Signature: float Clamp(float param_1, float param_2, float param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

float __cdecl Clamp(float param_1,float param_2,float param_3)

{
  if (param_1 < param_2) {
    return param_2;
  }
  if (param_3 < param_1) {
    return param_3;
  }
  return param_1;
}
