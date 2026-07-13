/*
 * Entry: 00404c15
 * Name: Min
 * Namespace: Global
 * Signature: float Min(float param_1, float param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

float __cdecl Min(float param_1,float param_2)

{
  if (param_2 < param_1) {
    return param_2;
  }
  return param_1;
}
