/*
 * Entry: 00404c2e
 * Name: Max
 * Namespace: Global
 * Signature: float Max(float param_1, float param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

float __cdecl Max(float param_1,float param_2)

{
  if (param_1 < param_2) {
    return param_2;
  }
  return param_1;
}
