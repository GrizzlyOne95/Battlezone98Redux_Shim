/*
 * Entry: 00514c35
 * Name: NR_Dmatrix
 * Namespace: Global
 * Signature: double * * NR_Dmatrix(int param_1, int param_2, int param_3, int param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

double ** __cdecl NR_Dmatrix(int param_1,int param_2,int param_3,int param_4)

{
  void *pvVar1;
  double **ppdVar2;
  double *pdVar3;
  int iVar4;
  
  iVar4 = (param_2 - param_1) * 4;
  pvVar1 = calloc(1,iVar4 + 4 + ((param_4 - param_3) + 1) * ((param_2 - param_1) + 1) * 8);
  if (pvVar1 == (void *)0x0) {
    NR_Error("allocation failure in NR_Dmatrix()");
  }
  pdVar3 = (double *)((int)pvVar1 + iVar4 + 4);
  ppdVar2 = (double **)((int)pvVar1 + param_1 * -4);
  for (; param_1 <= param_2; param_1 = param_1 + 1) {
    ppdVar2[param_1] = pdVar3;
    ppdVar2[param_1] = ppdVar2[param_1] + -param_3;
    pdVar3 = pdVar3 + (param_4 - param_3) + 1;
  }
  return ppdVar2;
}
