/*
 * Entry: 004d1542
 * Name: Interpolate
 * Namespace: Global
 * Signature: float Interpolate(float param_1, float param_2, float param_3, float param_4, float param_5, float param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

float __cdecl
Interpolate(float param_1,float param_2,float param_3,float param_4,float param_5,float param_6)

{
  float fVar1;
  
  fVar1 = (param_4 - param_3) * param_1 + param_3;
  return (((param_5 - param_6) * param_1 + param_6) - fVar1) * param_2 + fVar1;
}
