/*
 * Entry: 0051ff2d
 * Name: GetTileTextureIndex
 * Namespace: Global
 * Signature: int GetTileTextureIndex(long param_1, long param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl GetTileTextureIndex(long param_1,long param_2)

{
  ushort uVar1;
  ushort *puVar2;
  
  puVar2 = GetTilePtr(param_1,param_2);
  uVar1 = *puVar2;
  return (uint)(TileIndex[uVar1 >> 0xc][uVar1 >> 8 & 0xf][uVar1 & 3][uVar1 >> 7 & 1] >> 2);
}
