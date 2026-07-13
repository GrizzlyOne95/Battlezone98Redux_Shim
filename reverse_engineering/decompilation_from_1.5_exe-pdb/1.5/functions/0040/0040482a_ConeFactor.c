/*
 * Entry: 0040482a
 * Name: ConeFactor
 * Namespace: Global
 * Signature: float ConeFactor(float param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

float __cdecl ConeFactor(float param_1)

{
  if (param_1 < 3.0) {
    return 100.0;
  }
  if (param_1 < 5.0) {
    return 3.0;
  }
  if (param_1 < 15.0) {
    return 2.0;
  }
  return 1.0;
}
