/*
 * Entry: 0044f140
 * Name: UpdateSlab
 * Namespace: Global
 * Signature: void UpdateSlab(int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl UpdateSlab(int param_1)

{
  int *piVar1;
  int iVar2;
  tagSTRIP *ptVar3;
  int iVar4;
  int iVar5;
  
  ptVar3 = stripList;
  iVar2 = xSlabSize;
  piVar1 = xSlab;
  iVar5 = 0;
  iVar4 = 0;
  xSlabSize = 0;
  if (0 < iVar2) {
    do {
      if ((ptVar3[piVar1[iVar4]].flags & 0x8000U) == 0) {
        iVar5 = iVar5 + -1;
      }
      else {
        ptVar3[piVar1[iVar4]].x1 = (short)param_1 + 1;
        piVar1[iVar5] = piVar1[iVar4];
      }
      iVar4 = iVar4 + 1;
      iVar5 = iVar5 + 1;
      xSlabSize = iVar5;
    } while (iVar4 < iVar2);
  }
  return;
}
