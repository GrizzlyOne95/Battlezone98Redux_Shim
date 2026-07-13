/*
 * Entry: 00514ca8
 * Name: NR_Imatrix
 * Namespace: Global
 * Signature: int * * NR_Imatrix(int param_1, int param_2, int param_3, int param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int ** __cdecl NR_Imatrix(int param_1,int param_2,int param_3,int param_4)

{
  void *pvVar1;
  int **ppiVar2;
  int *piVar3;
  int iVar4;
  
  iVar4 = (param_2 - param_1) * 4;
  pvVar1 = calloc(1,iVar4 + 4 + ((param_4 - param_3) + 1) * ((param_2 - param_1) + 1) * 8);
  if (pvVar1 == (void *)0x0) {
    NR_Error("allocation failure in NR_Imatrix()");
  }
  piVar3 = (int *)((int)pvVar1 + iVar4 + 4);
  ppiVar2 = (int **)((int)pvVar1 + param_1 * -4);
  for (; param_1 <= param_2; param_1 = param_1 + 1) {
    ppiVar2[param_1] = piVar3;
    ppiVar2[param_1] = ppiVar2[param_1] + -param_3;
    piVar3 = piVar3 + (param_4 - param_3) + 1;
  }
  return ppiVar2;
}
