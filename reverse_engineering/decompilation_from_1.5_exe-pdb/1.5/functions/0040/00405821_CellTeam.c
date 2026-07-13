/*
 * Entry: 00405821
 * Name: CellTeam
 * Namespace: Global
 * Signature: ushort CellTeam(int param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ushort __cdecl CellTeam(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  
  iVar2 = param_2 - GridMinZ;
  if ((-1 < iVar2) && (iVar2 < GridMaxZ - GridMinZ)) {
    iVar1 = param_1 - GridMinX;
    if ((-1 < iVar1) && (iVar1 < GridMaxX - GridMinX)) {
      return cellTeam[(GridMaxX - GridMinX) * iVar2 + iVar1];
    }
  }
  return 0;
}
