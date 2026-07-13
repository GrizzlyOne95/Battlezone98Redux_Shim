/*
 * Entry: 004051d7
 * Name: BuildingUnblock
 * Namespace: Global
 * Signature: void BuildingUnblock(int param_1, int param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl BuildingUnblock(int param_1,int param_2,int param_3)

{
  bool bVar1;
  int unaff_EBP;
  int unaff_ESI;
  
  cellType[param_1] = cellType[param_1] & 0xf4;
  bVar1 = CellIsSteep(param_2,param_3);
  if (bVar1) {
    cellType[param_1] = cellType[param_1] | 2;
  }
  else {
    bVar1 = CellIsSlope(unaff_ESI,unaff_EBP);
    if (bVar1) {
      cellType[param_1] = cellType[param_1] | 1;
    }
  }
  return;
}
