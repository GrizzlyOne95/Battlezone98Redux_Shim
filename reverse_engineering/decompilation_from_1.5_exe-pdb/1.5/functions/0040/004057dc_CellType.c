/*
 * Entry: 004057dc
 * Name: CellType
 * Namespace: Global
 * Signature: uchar CellType(int param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

uchar __cdecl CellType(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  
  iVar2 = param_2 - GridMinZ;
  if ((-1 < iVar2) && (iVar2 < GridMaxZ - GridMinZ)) {
    iVar1 = param_1 - GridMinX;
    if ((-1 < iVar1) && (iVar1 < GridMaxX - GridMinX)) {
      return cellType[iVar1 + (GridMaxX - GridMinX) * iVar2];
    }
  }
  return '\0';
}
