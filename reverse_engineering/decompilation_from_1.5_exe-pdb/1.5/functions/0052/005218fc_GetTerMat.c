/*
 * Entry: 005218fc
 * Name: GetTerMat
 * Namespace: Global
 * Signature: int GetTerMat(long param_1, long param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl GetTerMat(long param_1,long param_2)

{
  ushort *puVar1;
  
  puVar1 = GetTilePtr(param_1,param_2);
  return (uint)(*puVar1 >> 0xc);
}
