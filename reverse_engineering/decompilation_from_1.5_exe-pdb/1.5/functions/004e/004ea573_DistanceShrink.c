/*
 * Entry: 004ea573
 * Name: DistanceShrink
 * Namespace: Global
 * Signature: float DistanceShrink(float param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

float __cdecl DistanceShrink(float param_1)

{
  if (param_1 < 5.0) {
    return 1.0;
  }
  if (param_1 < 10.0) {
    return 0.9;
  }
  if (param_1 < 50.0) {
    return 0.8;
  }
  if (param_1 < 150.0) {
    return 0.6;
  }
  if (param_1 < 350.0) {
    return 0.4;
  }
  return 0.2;
}
