/*
 * Entry: 0040aecd
 * Name: FillRects
 * Namespace: Global
 * Signature: void FillRects(int * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl FillRects(int *param_1,int param_2)

{
  long *plVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int *piVar6;
  int local_8;
  
  if (0 < rectCount) {
    plVar1 = &rects[0].right;
    local_8 = rectCount;
    do {
      iVar4 = plVar1[-1];
      if (iVar4 < plVar1[1]) {
        iVar5 = *plVar1;
        iVar2 = gridColumns * iVar4;
        do {
          iVar3 = ((tagRECT *)(plVar1 + -2))->left;
          if (iVar3 < iVar5) {
            piVar6 = param_1 + iVar2 + iVar3;
            do {
              *piVar6 = param_2;
              iVar5 = *plVar1;
              iVar3 = iVar3 + 1;
              piVar6 = piVar6 + 1;
            } while (iVar3 < iVar5);
          }
          iVar2 = iVar2 + gridColumns;
          iVar4 = iVar4 + 1;
        } while (iVar4 < plVar1[1]);
      }
      plVar1 = plVar1 + 4;
      local_8 = local_8 + -1;
    } while (local_8 != 0);
  }
  return;
}
