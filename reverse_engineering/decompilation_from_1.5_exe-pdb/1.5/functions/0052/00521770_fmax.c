/*
 * Entry: 00521770
 * Name: fmax
 * Namespace: Global
 * Signature: float fmax(float param_1, float param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

float __cdecl fmax(float param_1,float param_2)

{
  if (param_1 < param_2) {
    return param_2;
  }
  return param_1;
}
