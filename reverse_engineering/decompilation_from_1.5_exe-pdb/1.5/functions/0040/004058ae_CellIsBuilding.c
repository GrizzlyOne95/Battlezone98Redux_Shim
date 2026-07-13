/*
 * Entry: 004058ae
 * Name: CellIsBuilding
 * Namespace: Global
 * Signature: bool CellIsBuilding(int param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __cdecl CellIsBuilding(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  
  iVar2 = param_2 - GridMinZ;
  if ((-1 < iVar2) && (iVar2 < GridMaxZ - GridMinZ)) {
    iVar1 = param_1 - GridMinX;
    if ((-1 < iVar1) && (iVar1 < GridMaxX - GridMinX)) {
      iVar2 = Material((uint)cellType[iVar1 + (GridMaxX - GridMinX) * iVar2]);
      return (bool)('\x01' - (iVar2 != 5));
    }
  }
  return false;
}
