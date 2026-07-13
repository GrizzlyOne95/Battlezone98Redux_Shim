/*
 * Entry: 0044fb90
 * Name: min<float>
 * Namespace: Global
 * Signature: float min<float>(float param_1, float param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

float __cdecl min<float>(float param_1,float param_2)

{
  if (param_1 < param_2) {
    return param_1;
  }
  return param_2;
}
