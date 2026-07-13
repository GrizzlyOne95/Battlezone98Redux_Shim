/*
 * Entry: 005c29d3
 * Name: luaB_rawset
 * Namespace: Global
 * Signature: int luaB_rawset(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl luaB_rawset(lua_State *param_1)

{
  luaL_checktype(param_1,1,5);
  luaL_checkany(param_1,2);
  luaL_checkany(param_1,3);
  lua_settop(param_1,3);
  lua_rawset(param_1,1);
  return 1;
}
