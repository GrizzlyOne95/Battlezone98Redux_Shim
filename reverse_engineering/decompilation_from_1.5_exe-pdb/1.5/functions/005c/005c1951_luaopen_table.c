/*
 * Entry: 005c1951
 * Name: luaopen_table
 * Namespace: Global
 * Signature: int luaopen_table(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl luaopen_table(lua_State *param_1)

{
  luaL_register(param_1,"table",tab_funcs);
  return 1;
}
