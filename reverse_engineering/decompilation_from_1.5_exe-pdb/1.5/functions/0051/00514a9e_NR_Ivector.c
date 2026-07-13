/*
 * Entry: 00514a9e
 * Name: NR_Ivector
 * Namespace: Global
 * Signature: int * NR_Ivector(int param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int * __cdecl NR_Ivector(int param_1,int param_2)

{
  void *pvVar1;
  
  pvVar1 = calloc(1,(param_2 - param_1) * 4 + 4);
  if (pvVar1 == (void *)0x0) {
    NR_Error("allocation failure in NR_Ivector()");
  }
  return (int *)((int)pvVar1 + param_1 * -4);
}
