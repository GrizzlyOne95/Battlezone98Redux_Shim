/*
 * Entry: 0045dce6
 * Name: RandFloat
 * Namespace: Global
 * Signature: float RandFloat(float param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

float __cdecl RandFloat(float param_1)

{
  int iVar1;
  
  iVar1 = rand();
  return (float)iVar1 * param_1 * 3.051851e-05;
}
