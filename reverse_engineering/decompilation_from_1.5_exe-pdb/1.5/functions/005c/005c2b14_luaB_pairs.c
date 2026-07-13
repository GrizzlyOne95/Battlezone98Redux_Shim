/*
 * Entry: 005c2b14
 * Name: luaB_pairs
 * Namespace: Global
 * Signature: int luaB_pairs(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl luaB_pairs(lua_State *param_1)

{
  luaL_checktype(param_1,1,5);
  lua_pushvalue(param_1,-0x2713);
  lua_pushvalue(param_1,1);
  lua_pushnil(param_1);
  return 3;
}
