/*
 * Entry: 00514df9
 * Name: NR_Submatrix
 * Namespace: Global
 * Signature: float * * NR_Submatrix(float * * param_1, int param_2, int param_3, int param_4, int param_5, int param_6, int param_7)
 * Symbol source: IMPORTED
 * Export status: ok
 */

float ** __cdecl
NR_Submatrix(float **param_1,int param_2,int param_3,int param_4,int param_5,int param_6,int param_7
            )

{
  void *pvVar1;
  float **ppfVar2;
  float **ppfVar3;
  
  pvVar1 = calloc(1,(param_3 - param_2) * 4 + 4);
  if (pvVar1 == (void *)0x0) {
    NR_Error("allocation failure in submatrix()");
  }
  ppfVar3 = (float **)((int)pvVar1 + param_6 * -4);
  if (param_2 <= param_3) {
    ppfVar2 = ppfVar3 + param_6;
    do {
      *ppfVar2 = param_1[param_2] + (param_4 - param_7);
      param_2 = param_2 + 1;
      ppfVar2 = ppfVar2 + 1;
    } while (param_2 <= param_3);
  }
  return ppfVar3;
}
