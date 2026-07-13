/*
 * Entry: 0054d9b5
 * Name: CheckCheater
 * Namespace: Global
 * Signature: int CheckCheater(long param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl CheckCheater(long param_1)

{
  return (uint)((param_1 & 0x30fU) != 0);
}
