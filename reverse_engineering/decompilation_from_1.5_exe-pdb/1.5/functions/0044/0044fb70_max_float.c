/*
 * Entry: 0044fb70
 * Name: max<float>
 * Namespace: Global
 * Signature: float max<float>(float param_1, float param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

float __cdecl max<float>(float param_1,float param_2)

{
  if (param_1 < param_2) {
    return param_2;
  }
  return param_1;
}
