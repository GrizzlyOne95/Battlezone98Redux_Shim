/*
 * Entry: 0044f1b0
 * Name: ProcessStrip
 * Namespace: Global
 * Signature: int ProcessStrip(int param_1, int param_2, int param_3, int param_4, int param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl ProcessStrip(int param_1,int param_2,int param_3,int param_4,int param_5)

{
  int iVar1;
  int iVar2;
  tagSTRIP *ptVar3;
  int unaff_ESI;
  int iVar4;
  int unaff_EDI;
  
  iVar4 = 0;
  iVar2 = -1;
  if (0 < xSlabSize) {
    do {
      iVar1 = xSlab[iVar4];
      ptVar3 = stripList + iVar1;
      if (ptVar3->x1 < param_2) {
        if (((((ptVar3->flags & 0xffff7fffU) == param_4) && (ptVar3->z0 == param_3)) &&
            (ptVar3->z1 == unaff_EDI)) && (iVar1 != iVar2)) {
          ptVar3->flags = ptVar3->flags | 0x8000;
          return unaff_EDI;
        }
        if (((ptVar3->z0 < unaff_EDI) && (param_3 < ptVar3->z1)) && (iVar1 != iVar2)) {
          if (iVar2 < 0) {
            iVar2 = CreateStrip(param_1,param_2,param_3,unaff_EDI,unaff_ESI);
            ptVar3 = stripList + xSlab[iVar4];
          }
          ptVar3->flags = ptVar3->flags & 0xffff7fff;
        }
      }
      iVar4 = iVar4 + 1;
    } while (iVar4 < xSlabSize);
    if (iVar2 != -1) {
      return unaff_EDI;
    }
  }
  CreateStrip(param_1,param_2,param_3,unaff_EDI,unaff_ESI);
  return unaff_EDI;
}
