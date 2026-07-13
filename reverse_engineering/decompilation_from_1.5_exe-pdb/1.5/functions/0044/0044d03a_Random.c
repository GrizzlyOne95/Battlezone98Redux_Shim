/*
 * Entry: 0044d03a
 * Name: Random
 * Namespace: Global
 * Signature: float Random(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

float __cdecl Random(void)

{
  int iVar1;
  
  iVar1 = rand();
  return (float)iVar1 * 6.103702e-05 - 1.0;
}
