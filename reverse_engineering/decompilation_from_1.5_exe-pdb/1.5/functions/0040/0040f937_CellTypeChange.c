/*
 * Entry: 0040f937
 * Name: CellTypeChange
 * Namespace: Global
 * Signature: int CellTypeChange(long param_1, long param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl CellTypeChange(long param_1,long param_2)

{
  byte bVar1;
  ushort uVar2;
  
  bVar1 = CellType(param_1,param_2);
  if ((cellTypeMask & (cellType0 ^ bVar1)) != 0) {
    return 1;
  }
  uVar2 = CellTeam(param_1,param_2);
  return (uint)((cellTeamMask & (cellTeam0 ^ uVar2)) != 0);
}
