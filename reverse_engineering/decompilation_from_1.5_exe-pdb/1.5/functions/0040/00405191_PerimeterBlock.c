/*
 * Entry: 00405191
 * Name: PerimeterBlock
 * Namespace: Global
 * Signature: void PerimeterBlock(int param_1, int param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl PerimeterBlock(int param_1,int param_2,int param_3)

{
  bool bVar1;
  
  bVar1 = CellIsCliff(param_2,param_3);
  if (!bVar1) {
    cellType[param_1] = cellType[param_1] | 8;
  }
  return;
}
