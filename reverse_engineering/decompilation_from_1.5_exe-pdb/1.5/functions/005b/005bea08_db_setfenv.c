/*
 * Entry: 005bea08
 * Name: db_setfenv
 * Namespace: Global
 * Signature: int db_setfenv(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl db_setfenv(lua_State *param_1)

{
  int iVar1;
  
  luaL_checktype(param_1,2,5);
  lua_settop(param_1,2);
  iVar1 = lua_setfenv(param_1,1);
  if (iVar1 == 0) {
    luaL_error(param_1,"\'setfenv\' cannot change environment of given object");
  }
  return 1;
}
