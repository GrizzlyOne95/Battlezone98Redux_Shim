/*
 * Entry: 0044f2c0
 * Name: MaterialBuildZone
 * Namespace: Global
 * Signature: int MaterialBuildZone(int param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl MaterialBuildZone(int param_1,int param_2)

{
  uchar uVar1;
  byte bVar2;
  ushort uVar3;
  uint uVar4;
  
  uVar1 = CellRegion(param_1,param_2);
  if (uVar1 == '\0') {
    return 6;
  }
  bVar2 = CellType(param_1,param_2);
  uVar4 = sMaterial[bVar2 & 0xf];
  if ((uVar4 == 0) || (uVar4 == 1)) {
    uVar3 = CellTeam(param_1,param_2);
    uVar4 = uVar4 | (uint)uVar3 << 0x10;
  }
  return uVar4;
}
