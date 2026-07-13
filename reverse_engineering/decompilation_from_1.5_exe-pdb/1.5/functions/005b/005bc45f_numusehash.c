/*
 * Entry: 005bc45f
 * Name: numusehash
 * Namespace: Global
 * Signature: int numusehash(Table * param_1, int * param_2, int * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl numusehash(Table *param_1,int *param_2,int *param_3)

{
  int iVar1;
  int *unaff_EBX;
  int iVar2;
  int iVar3;
  int unaff_EDI;
  undefined4 local_c;
  undefined4 local_8;
  
  local_c = 0;
  local_8 = 0;
  iVar3 = 1 << (*(byte *)(unaff_EDI + 7) & 0x1f);
  if (iVar3 != 0) {
    iVar2 = iVar3 << 5;
    do {
      iVar2 = iVar2 + -0x20;
      iVar3 = iVar3 + -1;
      if (*(int *)(*(int *)(unaff_EDI + 0x10) + iVar2 + 8) != 0) {
        iVar1 = countint((lua_TValue *)param_1,unaff_EBX);
        local_8 = local_8 + iVar1;
        local_c = local_c + 1;
      }
    } while (iVar3 != 0);
  }
  *param_2 = *param_2 + local_8;
  return local_c;
}
