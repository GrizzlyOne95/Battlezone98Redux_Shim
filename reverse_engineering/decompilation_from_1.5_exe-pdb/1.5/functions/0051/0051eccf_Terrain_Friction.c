/*
 * Entry: 0051eccf
 * Name: Terrain_Friction
 * Namespace: Global
 * Signature: float Terrain_Friction(long param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

float __cdecl Terrain_Friction(long param_1)

{
  return *(float *)(&SurfaceTable + param_1 * 0x14);
}
