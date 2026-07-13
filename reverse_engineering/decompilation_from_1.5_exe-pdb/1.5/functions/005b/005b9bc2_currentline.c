/*
 * Entry: 005b9bc2
 * Name: currentline
 * Namespace: Global
 * Signature: int currentline(lua_State * param_1, CallInfo * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl currentline(lua_State *param_1,CallInfo *param_2)

{
  int iVar1;
  int iVar2;
  int unaff_ESI;
  lua_State *unaff_retaddr;
  
  iVar2 = currentpc(unaff_retaddr,(CallInfo *)param_1);
  if (iVar2 < 0) {
    return -1;
  }
  iVar1 = *(int *)(*(int *)(**(int **)(unaff_ESI + 4) + 0x10) + 0x14);
  if (iVar1 != 0) {
    return *(int *)(iVar1 + iVar2 * 4);
  }
  return 0;
}
