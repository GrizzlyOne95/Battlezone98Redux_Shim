/*
 * Entry: 005bf4c7
 * Name: luaopen_debug
 * Namespace: Global
 * Signature: int luaopen_debug(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl luaopen_debug(lua_State *param_1)

{
  luaL_register(param_1,"debug",dblib);
  return 1;
}
