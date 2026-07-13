/*
 * Entry: 00514d8a
 * Name: NR_Smatrix
 * Namespace: Global
 * Signature: ushort * * NR_Smatrix(int param_1, int param_2, int param_3, int param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ushort ** __cdecl NR_Smatrix(int param_1,int param_2,int param_3,int param_4)

{
  void *pvVar1;
  ushort **ppuVar2;
  ushort *puVar3;
  int iVar4;
  
  iVar4 = (param_2 - param_1) * 4;
  pvVar1 = calloc(1,iVar4 + 4 + ((param_4 - param_3) + 1) * ((param_2 - param_1) + 1) * 2);
  if (pvVar1 == (void *)0x0) {
    NR_Error("allocation failure in NR_Smatrix()");
  }
  puVar3 = (ushort *)((int)pvVar1 + iVar4 + 4);
  ppuVar2 = (ushort **)((int)pvVar1 + param_1 * -4);
  for (; param_1 <= param_2; param_1 = param_1 + 1) {
    ppuVar2[param_1] = puVar3;
    ppuVar2[param_1] = ppuVar2[param_1] + -param_3;
    puVar3 = puVar3 + (param_4 - param_3) + 1;
  }
  return ppuVar2;
}
