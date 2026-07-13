/*
 * Entry: 005c32b4
 * Name: luaB_cocreate
 * Namespace: Global
 * Signature: int luaB_cocreate(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl luaB_cocreate(lua_State *param_1)

{
  lua_State *plVar1;
  int iVar2;
  
  plVar1 = lua_newthread(param_1);
  iVar2 = lua_type(param_1,1);
  if (iVar2 == 6) {
    iVar2 = lua_iscfunction(param_1,1);
    if (iVar2 == 0) goto LAB_005c32f1;
  }
  luaL_argerror(param_1,1,"Lua function expected");
LAB_005c32f1:
  lua_pushvalue(param_1,1);
  lua_xmove(param_1,plVar1,1);
  return 1;
}
