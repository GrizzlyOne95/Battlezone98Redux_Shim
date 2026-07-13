/*
 * Entry: 00514bc2
 * Name: NR_Ptr_Matrix
 * Namespace: Global
 * Signature: void * * * NR_Ptr_Matrix(int param_1, int param_2, int param_3, int param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void *** __cdecl NR_Ptr_Matrix(int param_1,int param_2,int param_3,int param_4)

{
  void *pvVar1;
  void ***pppvVar2;
  void **ppvVar3;
  int iVar4;
  
  iVar4 = (param_2 - param_1) * 4;
  pvVar1 = calloc(1,((param_4 - param_3) + 1) * (iVar4 + 4) + 4 + iVar4);
  if (pvVar1 == (void *)0x0) {
    NR_Error("allocation failure in NR_Ptr_Matrix()");
  }
  ppvVar3 = (void **)((int)pvVar1 + iVar4 + 4);
  pppvVar2 = (void ***)((int)pvVar1 + param_1 * -4);
  for (; param_1 <= param_2; param_1 = param_1 + 1) {
    pppvVar2[param_1] = ppvVar3;
    pppvVar2[param_1] = pppvVar2[param_1] + -param_3;
    ppvVar3 = ppvVar3 + (param_4 - param_3) + 1;
  }
  return pppvVar2;
}
