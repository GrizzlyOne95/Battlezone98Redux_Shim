/*
 * Entry: 00510817
 * Name: Geom_Sin
 * Namespace: Global
 * Signature: float Geom_Sin(int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

float __cdecl Geom_Sin(int param_1)

{
  return costable[0x100U - ((int)((param_1 >> 6) + (param_1 >> 0x1f & 0xffU)) >> 8) & 0x3ff];
}
