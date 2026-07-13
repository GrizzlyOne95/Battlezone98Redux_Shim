/*
 * Entry: 005218e4
 * Name: GetTerY
 * Namespace: Global
 * Signature: int GetTerY(long param_1, long param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl GetTerY(long param_1,long param_2)

{
  ushort *puVar1;
  
  puVar1 = GetZonePtr(param_1,param_2);
  return *puVar1 & 0xfff;
}
