/*
 * Entry: 005c31e3
 * Name: luaB_coresume
 * Namespace: Global
 * Signature: int luaB_coresume(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl luaB_coresume(lua_State *param_1)

{
  lua_State *plVar1;
  int iVar2;
  int unaff_EDI;
  
  plVar1 = lua_tothread(param_1,1);
  if (plVar1 == (lua_State *)0x0) {
    luaL_argerror(param_1,1,"coroutine expected");
  }
  plVar1 = param_1;
  iVar2 = lua_gettop(param_1);
  iVar2 = auxresume((lua_State *)(iVar2 + -1),plVar1,unaff_EDI);
  if (iVar2 < 0) {
    lua_pushboolean(param_1,0);
    lua_insert(param_1,-2);
    iVar2 = 2;
  }
  else {
    lua_pushboolean(param_1,1);
    lua_insert(param_1,-1 - iVar2);
    iVar2 = iVar2 + 1;
  }
  return iVar2;
}
