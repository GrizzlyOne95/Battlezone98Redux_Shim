/*
 * Entry: 0051dd1a
 * Name: TerrainOutCode
 * Namespace: Global
 * Signature: long TerrainOutCode(long param_1, long param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

long __cdecl TerrainOutCode(long param_1,long param_2)

{
  uint uVar1;
  uint uVar2;
  
  uVar1 = (param_1 + -1) - GridMaxX;
  uVar2 = (param_2 + -1) - GridMaxZ;
  return (((uint)CARRY4(param_1 - GridMinX,param_1 - GridMinX) * 2 + (uint)CARRY4(uVar1,uVar1)) * 2
         + (uint)CARRY4(param_2 - GridMinZ,param_2 - GridMinZ)) * 2 + (uint)CARRY4(uVar2,uVar2) ^ 5;
}
