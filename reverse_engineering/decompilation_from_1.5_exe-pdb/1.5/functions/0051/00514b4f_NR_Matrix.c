/*
 * Entry: 00514b4f
 * Name: NR_Matrix
 * Namespace: Global
 * Signature: float * * NR_Matrix(int param_1, int param_2, int param_3, int param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

float ** __cdecl NR_Matrix(int param_1,int param_2,int param_3,int param_4)

{
  void *pvVar1;
  float **ppfVar2;
  float *pfVar3;
  int iVar4;
  
  iVar4 = (param_2 - param_1) * 4;
  pvVar1 = calloc(1,((param_4 - param_3) + 1) * (iVar4 + 4) + 4 + iVar4);
  if (pvVar1 == (void *)0x0) {
    NR_Error("allocation failure in NR_Matrix()");
  }
  pfVar3 = (float *)((int)pvVar1 + iVar4 + 4);
  ppfVar2 = (float **)((int)pvVar1 + param_1 * -4);
  for (; param_1 <= param_2; param_1 = param_1 + 1) {
    ppfVar2[param_1] = pfVar3;
    ppfVar2[param_1] = ppfVar2[param_1] + -param_3;
    pfVar3 = pfVar3 + (param_4 - param_3) + 1;
  }
  return ppfVar2;
}
