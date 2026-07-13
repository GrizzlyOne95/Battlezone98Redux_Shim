/*
 * Entry: 005b6a9d
 * Name: lua_error
 * Namespace: Global
 * Signature: int lua_error(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl lua_error(lua_State *param_1)

{
  luaG_errormsg(param_1);
  return 0;
}
