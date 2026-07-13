/*
 * Entry: 005bc3ce
 * Name: countint
 * Namespace: Global
 * Signature: int countint(lua_TValue * param_1, int * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl countint(lua_TValue *param_1,int *param_2)

{
  int *piVar1;
  int iVar2;
  lua_TValue *unaff_retaddr;
  
  iVar2 = arrayindex(unaff_retaddr);
  if (iVar2 - 1U < 0x4000000) {
    iVar2 = luaO_log2(iVar2 - 1);
    piVar1 = (int *)((int)&param_1->value + iVar2 * 4 + 4);
    *piVar1 = *piVar1 + 1;
    return 1;
  }
  return 0;
}
