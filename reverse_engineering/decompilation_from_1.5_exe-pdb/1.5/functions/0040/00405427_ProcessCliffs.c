/*
 * Entry: 00405427
 * Name: ProcessCliffs
 * Namespace: Global
 * Signature: void ProcessCliffs(int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl ProcessCliffs(int param_1)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int unaff_ESI;
  int iVar5;
  int unaff_EDI;
  int iVar6;
  int local_c;
  
  iVar2 = GetLavaMat();
  local_c = 0;
  iVar5 = GridMinZ;
  iVar6 = GridMinX;
  if (0 < param_1) {
    do {
      bVar1 = CellIsCliff(iVar6,iVar5);
      if (bVar1) {
        cellType[local_c] = cellType[local_c] | 3;
      }
      else {
        cellType[local_c] = cellType[local_c] & 0xfc;
        bVar1 = CellIsSteep(iVar6,iVar5);
        if (bVar1) {
          cellType[local_c] = cellType[local_c] | 2;
        }
        else {
          bVar1 = CellIsSlope(unaff_EDI,unaff_ESI);
          if (bVar1) {
            cellType[local_c] = cellType[local_c] | 1;
          }
        }
      }
      iVar3 = GetTerMat(iVar6,iVar5);
      if (iVar3 == iVar2) {
LAB_0040553c:
        cellType[local_c] = cellType[local_c] | 4;
      }
      else {
        iVar3 = iVar5 + -1;
        iVar4 = GetTerMat(iVar6 + -1,iVar3);
        if ((((iVar4 == iVar2) || (iVar4 = GetTerMat(iVar6,iVar3), iVar4 == iVar2)) ||
            (iVar3 = GetTerMat(iVar6 + 1,iVar3), iVar3 == iVar2)) ||
           ((iVar3 = GetTerMat(iVar6 + -1,iVar5), iVar3 == iVar2 ||
            (iVar3 = GetTerMat(iVar6 + 1,iVar5), iVar3 == iVar2)))) goto LAB_0040553c;
        iVar3 = iVar5 + 1;
        iVar4 = GetTerMat(iVar6 + -1,iVar3);
        if ((iVar4 == iVar2) ||
           ((iVar4 = GetTerMat(iVar6,iVar3), iVar4 == iVar2 ||
            (iVar3 = GetTerMat(iVar6 + 1,iVar3), iVar3 == iVar2)))) goto LAB_0040553c;
      }
      iVar6 = iVar6 + 1;
      if ((GridMaxX <= iVar6) && (iVar5 = iVar5 + 1, iVar6 = GridMinX, GridMaxZ <= iVar5)) {
        iVar5 = GridMinZ;
      }
      local_c = local_c + 1;
    } while (local_c < param_1);
  }
  return;
}
