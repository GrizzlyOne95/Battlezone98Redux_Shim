/*
 * Entry: 005c29a4
 * Name: luaB_rawget
 * Namespace: Global
 * Signature: int luaB_rawget(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl luaB_rawget(lua_State *param_1)

{
  luaL_checktype(param_1,1,5);
  luaL_checkany(param_1,2);
  lua_settop(param_1,2);
  lua_rawget(param_1,1);
  return 1;
}
