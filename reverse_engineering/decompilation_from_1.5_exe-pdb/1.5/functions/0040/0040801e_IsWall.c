/*
 * Entry: 0040801e
 * Name: IsWall
 * Namespace: Global
 * Signature: bool IsWall(int param_1, int param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __cdecl IsWall(int param_1,int param_2,int param_3)

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
