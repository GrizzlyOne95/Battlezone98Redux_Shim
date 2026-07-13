/*
 * Entry: 00514d1b
 * Name: NR_Cmatrix
 * Namespace: Global
 * Signature: uchar * * NR_Cmatrix(int param_1, int param_2, int param_3, int param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

uchar ** __cdecl NR_Cmatrix(int param_1,int param_2,int param_3,int param_4)

{
  uchar *puVar1;
  void *pvVar2;
  uchar **ppuVar3;
  int iVar4;
  
  iVar4 = (param_2 - param_1) * 4;
  pvVar2 = calloc(1,((param_4 - param_3) + 1) * ((param_2 - param_1) + 1) + 4 + iVar4);
  if (pvVar2 == (void *)0x0) {
    NR_Error("allocation failure in NR_Cmatrix()");
  }
  ppuVar3 = (uchar **)((int)pvVar2 + param_1 * -4);
  puVar1 = (uchar *)((int)pvVar2 + iVar4 + 4);
  for (; param_1 <= param_2; param_1 = param_1 + 1) {
    ppuVar3[param_1] = puVar1;
    ppuVar3[param_1] = ppuVar3[param_1] + -param_3;
    puVar1 = puVar1 + (param_4 - param_3) + 1;
  }
  return ppuVar3;
}
