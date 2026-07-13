/*
 * Entry: 0051ecf9
 * Name: Terrain_DmgRate
 * Namespace: Global
 * Signature: float Terrain_DmgRate(long param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

float __cdecl Terrain_DmgRate(long param_1)

{
  return (float)*(int *)(&DAT_00caee30 + param_1 * 0x14);
}
