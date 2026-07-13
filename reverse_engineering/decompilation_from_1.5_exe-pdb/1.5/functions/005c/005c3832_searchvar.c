/*
 * Entry: 005c3832
 * Name: searchvar
 * Namespace: Global
 * Signature: int searchvar(FuncState * param_1, TString * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl searchvar(FuncState *param_1,TString *param_2)

{
  int iVar1;
  int *in_ECX;
  ushort *puVar2;
  
  iVar1 = *(byte *)((int)in_ECX + 0x32) - 1;
  if (-1 < iVar1) {
    puVar2 = (ushort *)((int)in_ECX + iVar1 * 2 + 0xac);
    do {
      if (param_1 == *(FuncState **)((uint)*puVar2 * 0xc + *(int *)(*in_ECX + 0x18))) {
        return iVar1;
      }
      iVar1 = iVar1 + -1;
      puVar2 = puVar2 + -1;
    } while (-1 < iVar1);
  }
  return -1;
}
