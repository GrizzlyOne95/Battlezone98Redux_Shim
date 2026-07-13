/*
 * Entry: 0049ca5a
 * Name: GetPerformance
 * Namespace: Global
 * Signature: float GetPerformance(float param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

float __cdecl GetPerformance(float param_1)

{
  if (0.5 <= param_1) {
    return 1.0;
  }
  if (!NAN(param_1) && 0.25 < param_1 != (param_1 == 0.25)) {
    return param_1 * 0.5 + 0.75;
  }
  if (!NAN(param_1) && 0.0 < param_1 != (param_1 == 0.0)) {
    return param_1 + 0.5;
  }
  return 0.0;
}
