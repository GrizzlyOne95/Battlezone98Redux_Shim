/*
 * Entry: 005c12d6
 * Name: foreach
 * Namespace: Global
 * Signature: int foreach(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl foreach(lua_State *param_1)

{
  int iVar1;
  
  luaL_checktype(param_1,1,5);
  luaL_checktype(param_1,2,6);
  lua_pushnil(param_1);
  iVar1 = lua_next(param_1,1);
  while( true ) {
    if (iVar1 == 0) {
      return 0;
    }
    lua_pushvalue(param_1,2);
    lua_pushvalue(param_1,-3);
    lua_pushvalue(param_1,-3);
    lua_call(param_1,2,1);
    iVar1 = lua_type(param_1,-1);
    if (iVar1 != 0) break;
    lua_settop(param_1,-3);
    iVar1 = lua_next(param_1,1);
  }
  return 1;
}
