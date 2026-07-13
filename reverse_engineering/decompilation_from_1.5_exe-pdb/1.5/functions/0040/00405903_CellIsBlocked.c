/*
 * Entry: 00405903
 * Name: CellIsBlocked
 * Namespace: Global
 * Signature: bool CellIsBlocked(int param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __cdecl CellIsBlocked(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  
  iVar2 = param_2 - GridMinZ;
  if ((-1 < iVar2) && (iVar2 < GridMaxZ - GridMinZ)) {
    iVar1 = param_1 - GridMinX;
    if ((-1 < iVar1) && (iVar1 < GridMaxX - GridMinX)) {
      iVar2 = Material((uint)cellType[iVar1 + (GridMaxX - GridMinX) * iVar2]);
      if ((iVar2 != 6) && (iVar2 != 5)) {
        return false;
      }
      return true;
    }
  }
  return true;
}
