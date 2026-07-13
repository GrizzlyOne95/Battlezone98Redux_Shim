/*
 * Entry: 004afba6
 * Name: rand<float>
 * Namespace: Global
 * Signature: float rand<float>(float param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

float __cdecl rand<float>(float param_1)

{
  int iVar1;
  
  iVar1 = rand();
  return (float)iVar1 * param_1 * 3.051851e-05;
}
