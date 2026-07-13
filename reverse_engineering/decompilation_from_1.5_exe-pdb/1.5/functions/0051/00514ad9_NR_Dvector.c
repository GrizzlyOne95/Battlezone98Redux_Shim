/*
 * Entry: 00514ad9
 * Name: NR_Dvector
 * Namespace: Global
 * Signature: double * NR_Dvector(int param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

double * __cdecl NR_Dvector(int param_1,int param_2)

{
  void *pvVar1;
  
  pvVar1 = calloc(1,(param_2 - param_1) * 8 + 8);
  if (pvVar1 == (void *)0x0) {
    NR_Error("allocation failure in NR_Dvector()");
  }
  return (double *)((int)pvVar1 + param_1 * -8);
}
