/*
 * Entry: 00405869
 * Name: CellRegion
 * Namespace: Global
 * Signature: uchar CellRegion(int param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

uchar __cdecl CellRegion(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  
  iVar2 = param_2 - GridMinZ;
  if ((-1 < iVar2) && (iVar2 < GridMaxZ - GridMinZ)) {
    iVar1 = param_1 - GridMinX;
    if ((-1 < iVar1) && (iVar1 < GridMaxX - GridMinX)) {
      return cellRegion[iVar1 + (GridMaxX - GridMinX) * iVar2];
    }
  }
  return '\0';
}
