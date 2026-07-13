/*
 * Entry: 00514a38
 * Name: NR_Cvector
 * Namespace: Global
 * Signature: uchar * NR_Cvector(int param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

uchar * __cdecl NR_Cvector(int param_1,int param_2)

{
  void *pvVar1;
  
  pvVar1 = calloc(1,(param_2 - param_1) + 1);
  if (pvVar1 == (void *)0x0) {
    NR_Error("allocation failure in NR_Cvector()");
  }
  return (uchar *)((int)pvVar1 - param_1);
}
