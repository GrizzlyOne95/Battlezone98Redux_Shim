/*
 * Entry: 0051f8f5
 * Name: DepthAttenuation
 * Namespace: Global
 * Signature: float DepthAttenuation(float param_1, float param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

float __cdecl DepthAttenuation(float param_1,float param_2)

{
  int local_c;
  
  local_c = SUB84((double)(param_2 + (float)Float2Int),0);
  if (TerrainView.Fog_End <= local_c) {
    return 1.0;
  }
  if (local_c <= TerrainView.Fog_Start) {
    return param_1;
  }
  return (1.0 - param_1) * fogTable[local_c] + param_1;
}
