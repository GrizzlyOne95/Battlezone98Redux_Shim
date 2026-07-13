/*
 * Entry: 0044f050
 * Name: CreateStrip
 * Namespace: Global
 * Signature: int CreateStrip(int param_1, int param_2, int param_3, int param_4, int param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl CreateStrip(int param_1,int param_2,int param_3,int param_4,int param_5)

{
  tagSTRIP *ptVar1;
  longlong lVar2;
  int *piVar3;
  uint in_EAX;
  int iVar4;
  
  ptVar1 = stripList;
  iVar4 = stripListSize;
  if (stripListMax <= stripListSize) {
    if (stripList == (tagSTRIP *)0x0) {
      stripListMax = 0x400;
      stripListSize = 0;
      stripList = operator_new__(0x3000);
      iVar4 = stripListSize;
    }
    else {
      lVar2 = (ulonglong)(stripListMax + 0x400) * 0xc;
      stripList = operator_new__(-(uint)((int)((ulonglong)lVar2 >> 0x20) != 0) | (uint)lVar2);
      memcpy(stripList,ptVar1,stripListMax * 0xc);
      operator_delete__(ptVar1);
      stripListMax = stripListMax + 0x400;
      iVar4 = stripListSize;
    }
  }
  ptVar1 = stripList + iVar4;
  ptVar1->x0 = (short)param_1;
  ptVar1->x1 = (short)param_2;
  ptVar1->z0 = (short)param_3;
  ptVar1->z1 = (short)param_4;
  piVar3 = xSlab;
  ptVar1->flags = in_EAX | 0x8000;
  piVar3[xSlabSize] = iVar4;
  xSlabSize = xSlabSize + 1;
  stripListSize = iVar4 + 1;
  return iVar4;
}
