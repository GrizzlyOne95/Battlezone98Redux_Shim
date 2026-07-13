/*
 * Entry: 005c2b84
 * Name: luaB_ipairs
 * Namespace: Global
 * Signature: int luaB_ipairs(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl luaB_ipairs(lua_State *param_1)

{
  luaL_checktype(param_1,1,5);
  lua_pushvalue(param_1,-0x2713);
  lua_pushvalue(param_1,1);
  lua_pushinteger(param_1,0);
  return 3;
}
