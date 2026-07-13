/*
 * Entry: 005c26f8
 * Name: luaB_error
 * Namespace: Global
 * Signature: int luaB_error(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl luaB_error(lua_State *param_1)

{
  int iVar1;
  int iVar2;
  
  iVar1 = luaL_optinteger(param_1,2,1);
  lua_settop(param_1,1);
  iVar2 = lua_isstring(param_1,1);
  if ((iVar2 != 0) && (0 < iVar1)) {
    luaL_where(param_1,iVar1);
    lua_pushvalue(param_1,1);
    lua_concat(param_1,2);
  }
  iVar1 = lua_error(param_1);
  return iVar1;
}
