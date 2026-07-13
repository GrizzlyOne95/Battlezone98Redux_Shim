/*
 * Entry: 005a6aa0
 * Name: _float32_unpack
 * Namespace: Global
 * Signature: float _float32_unpack(long param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

float __cdecl _float32_unpack(long param_1)

{
  double dVar1;
  
  dVar1 = (double)(param_1 & 0x1fffff);
  if (param_1 < 0) {
    dVar1 = -dVar1;
  }
  dVar1 = ldexp(dVar1,(param_1 >> 0x15 & 0x3ffU) - 0x314);
  return (float)dVar1;
}
