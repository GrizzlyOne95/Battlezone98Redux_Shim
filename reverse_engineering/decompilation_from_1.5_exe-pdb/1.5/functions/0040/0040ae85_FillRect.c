/*
 * Entry: 0040ae85
 * Name: FillRect
 * Namespace: Global
 * Signature: void FillRect(int * param_1, tagRECT * param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl FillRect(int *param_1,tagRECT *param_2,int param_3)

{
  int *in_EAX;
  int iVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  int iVar5;
  
  iVar5 = in_EAX[1];
  if (iVar5 < in_EAX[3]) {
    iVar1 = gridColumns * iVar5;
    iVar4 = in_EAX[2];
    do {
      iVar2 = *in_EAX;
      if (iVar2 < iVar4) {
        piVar3 = param_1 + iVar1 + iVar2;
        do {
          *piVar3 = (int)param_2;
          iVar4 = in_EAX[2];
          iVar2 = iVar2 + 1;
          piVar3 = piVar3 + 1;
        } while (iVar2 < iVar4);
      }
      iVar1 = iVar1 + gridColumns;
      iVar5 = iVar5 + 1;
    } while (iVar5 < in_EAX[3]);
  }
  return;
}
