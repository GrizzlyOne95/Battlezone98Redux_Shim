/*
 * Entry: 005be9eb
 * Name: db_getfenv
 * Namespace: Global
 * Signature: int db_getfenv(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl db_getfenv(lua_State *param_1)

{
  luaL_checkany(param_1,1);
  lua_getfenv(param_1,1);
  return 1;
}
