/*
 * Entry: 00581c0e
 * Name: Gradient
 * Namespace: Global
 * Signature: float Gradient(int param_1, float param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

float __cdecl Gradient(int param_1,float param_2)

{
  uint in_EAX;
  
  return g[in_EAX & 0xf] * (float)param_1;
}
