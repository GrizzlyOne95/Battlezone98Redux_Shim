/*
 * Entry: 00476739
 * Name: sign
 * Namespace: Global
 * Signature: float sign(float param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

float __cdecl sign(float param_1)

{
  float fVar1;
  
  fVar1 = 0.0;
  if (param_1 != 0.0) {
    if (0.0 < param_1) {
      return 1.0;
    }
    fVar1 = -1.0;
  }
  return fVar1;
}
