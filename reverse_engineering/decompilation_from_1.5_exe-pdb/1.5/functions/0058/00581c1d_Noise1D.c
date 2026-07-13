/*
 * Entry: 00581c1d
 * Name: Noise1D
 * Namespace: Global
 * Signature: float Noise1D(float param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

float __cdecl Noise1D(float param_1)

{
  float fVar1;
  byte bVar2;
  int local_c;
  
  local_c._0_1_ = SUB81((double)(param_1 + (float)Float2Int),0);
  bVar2 = (byte)local_c;
  local_c = SUB84((double)(param_1 + (float)Float2Int),0);
  fVar1 = param_1 - (float)local_c;
  return g[p[bVar2] & 0xf] * fVar1 +
         ((fVar1 - 1.0) * g[p[(byte)(bVar2 + 1)] & 0xf] - g[p[bVar2] & 0xf] * fVar1) *
         ((fVar1 * 6.0 - 15.0) * fVar1 + 10.0) * fVar1 * fVar1 * fVar1;
}
