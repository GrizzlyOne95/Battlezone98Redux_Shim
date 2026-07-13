/*
 * Entry: 0044eed0
 * Name: CellRegionChange
 * Namespace: Global
 * Signature: int CellRegionChange(long param_1, long param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl CellRegionChange(long param_1,long param_2)

{
  byte bVar1;
  uchar uVar2;
  
  bVar1 = CellType(param_1,param_2);
  if ((bVar1 & 8) != 0) {
    return (uint)(cellRegion0 == '\0');
  }
  uVar2 = CellRegion(param_1,param_2);
  return (uint)(uVar2 == cellRegion0);
}
