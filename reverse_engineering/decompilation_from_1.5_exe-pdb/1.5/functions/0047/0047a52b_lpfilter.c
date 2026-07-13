/*
 * Entry: 0047a52b
 * Name: lpfilter
 * Namespace: Global
 * Signature: float lpfilter(float param_1, float param_2, float param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

float __cdecl lpfilter(float param_1,float param_2,float param_3)

{
  if ((0.0 <= param_3) && (param_3 <= 1.0)) {
    return (param_2 - param_1) * param_3 + param_1;
  }
  return param_2;
}
