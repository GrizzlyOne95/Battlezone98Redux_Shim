/*
 * Entry: 005a2be0
 * Name: unitnorm
 * Namespace: Global
 * Signature: float unitnorm(float param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

float __cdecl unitnorm(float param_1)

{
  return (float)((uint)param_1 & 0xbf800000 | 0x3f800000);
}
