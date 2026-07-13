/*
 * Entry: 005bc4b3
 * Name: setarrayvector
 * Namespace: Global
 * Signature: void setarrayvector(lua_State * param_1, Table * param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl setarrayvector(lua_State *param_1,Table *param_2,int param_3)

{
  void *pvVar1;
  int iVar2;
  int iVar3;
  int unaff_ESI;
  int unaff_EDI;
  
  if (unaff_EDI + 1U < 0x10000000) {
    pvVar1 = luaM_realloc_(param_1,*(void **)(unaff_ESI + 0xc),*(int *)(unaff_ESI + 0x1c) << 4,
                           unaff_EDI << 4);
  }
  else {
    pvVar1 = luaM_toobig(param_1);
  }
  iVar3 = *(int *)(unaff_ESI + 0x1c);
  *(void **)(unaff_ESI + 0xc) = pvVar1;
  if (iVar3 < unaff_EDI) {
    iVar2 = iVar3 << 4;
    iVar3 = unaff_EDI - iVar3;
    do {
      *(undefined4 *)(*(int *)(unaff_ESI + 0xc) + 8 + iVar2) = 0;
      iVar2 = iVar2 + 0x10;
      iVar3 = iVar3 + -1;
    } while (iVar3 != 0);
  }
  *(int *)(unaff_ESI + 0x1c) = unaff_EDI;
  return;
}
