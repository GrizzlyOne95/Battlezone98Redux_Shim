/*
 * Entry: 0044ea00
 * Name: Dist
 * Namespace: Global
 * Signature: float Dist(float param_1, float param_2, float param_3, float param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

float __cdecl Dist(float param_1,float param_2,float param_3,float param_4)

{
  return SQRT((param_4 - param_2) * (param_4 - param_2) + (param_3 - param_1) * (param_3 - param_1))
  ;
}
