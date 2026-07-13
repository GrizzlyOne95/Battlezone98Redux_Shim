/*
 * Entry: 005be97c
 * Name: db_getmetatable
 * Namespace: Global
 * Signature: int db_getmetatable(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl db_getmetatable(lua_State *param_1)

{
  int iVar1;
  
  luaL_checkany(param_1,1);
  iVar1 = lua_getmetatable(param_1,1);
  if (iVar1 == 0) {
    lua_pushnil(param_1);
  }
  return 1;
}
