/*
 * Entry: 0051083f
 * Name: Geom_Cos
 * Namespace: Global
 * Signature: float Geom_Cos(int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

float __cdecl Geom_Cos(int param_1)

{
  return costable[(int)((param_1 >> 6) + (param_1 >> 0x1f & 0xffU)) >> 8 & 0x3ff];
}
