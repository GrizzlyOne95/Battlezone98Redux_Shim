/*
 * Entry: 004051b4
 * Name: PerimeterUnblock
 * Namespace: Global
 * Signature: void PerimeterUnblock(int param_1, int param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl PerimeterUnblock(int param_1,int param_2,int param_3)

{
  bool bVar1;
  
  bVar1 = CellIsCliff(param_2,param_3);
  if (!bVar1) {
    cellType[param_1] = cellType[param_1] & 0xf7;
  }
  return;
}
