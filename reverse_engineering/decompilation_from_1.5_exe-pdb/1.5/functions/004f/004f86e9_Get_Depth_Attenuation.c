/*
 * Entry: 004f86e9
 * Name: Get_Depth_Attenuation
 * Namespace: Global
 * Signature: float Get_Depth_Attenuation(float param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

float __cdecl Get_Depth_Attenuation(float param_1)

{
  float fVar1;
  float fVar2;
  
  fVar1 = Depth_Att1 * param_1 + Depth_Att0;
  fVar2 = 0.0;
  if ((0.0 <= fVar1) && (fVar2 = 1.0, fVar1 <= 1.0)) {
    return fVar1;
  }
  return fVar2;
}
