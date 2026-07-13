/*
 * Entry: 005c2add
 * Name: luaB_next
 * Namespace: Global
 * Signature: int luaB_next(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl luaB_next(lua_State *param_1)

{
  int iVar1;
  
  luaL_checktype(param_1,1,5);
  lua_settop(param_1,2);
  iVar1 = lua_next(param_1,1);
  if (iVar1 != 0) {
    return 2;
  }
  lua_pushnil(param_1);
  return 1;
}
