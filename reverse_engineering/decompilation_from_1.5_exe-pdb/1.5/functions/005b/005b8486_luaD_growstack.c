/*
 * Entry: 005b8486
 * Name: luaD_growstack
 * Namespace: Global
 * Signature: void luaD_growstack(lua_State * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl luaD_growstack(lua_State *param_1,int param_2)

{
  int iVar1;
  
  iVar1 = param_1->stacksize;
  if (iVar1 < param_2) {
    iVar1 = iVar1 + param_2;
  }
  else {
    iVar1 = iVar1 * 2;
  }
  luaD_reallocstack(param_1,iVar1);
  return;
}
