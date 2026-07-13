/*
 * Entry: 00514f5f
 * Name: NR_Convert_Matrix
 * Namespace: Global
 * Signature: float * * NR_Convert_Matrix(float * param_1, int param_2, int param_3, int param_4, int param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

float ** __cdecl NR_Convert_Matrix(float *param_1,int param_2,int param_3,int param_4,int param_5)

{
  void *pvVar1;
  float *pfVar2;
  float **ppfVar3;
  float **ppfVar4;
  int iVar5;
  
  iVar5 = param_3 - param_2;
  pvVar1 = calloc(1,(iVar5 + 1) * 4);
  if (pvVar1 == (void *)0x0) {
    NR_Error("allocation failure in convert_matrix()");
  }
  ppfVar4 = (float **)((int)pvVar1 + param_2 * -4);
  if (-1 < iVar5) {
    ppfVar3 = ppfVar4 + param_2;
    pfVar2 = param_1 + -param_4;
    iVar5 = iVar5 + 1;
    do {
      *ppfVar3 = pfVar2;
      ppfVar3 = ppfVar3 + 1;
      pfVar2 = pfVar2 + (param_5 - param_4) + 1;
      iVar5 = iVar5 + -1;
    } while (iVar5 != 0);
  }
  return ppfVar4;
}
