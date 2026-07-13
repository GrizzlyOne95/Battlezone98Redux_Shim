/*
 * Entry: 0044e379
 * Name: ceilf
 * Namespace: Global
 * Signature: float ceilf(float param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

float __cdecl ceilf(float param_1)

{
  double dVar1;
  
  dVar1 = ceil((double)param_1);
  return (float)dVar1;
}
