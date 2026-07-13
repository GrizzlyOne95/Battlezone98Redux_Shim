/*
 * Entry: 005c13fc
 * Name: setn
 * Namespace: Global
 * Signature: int setn(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl setn(lua_State *param_1)

{
  luaL_checktype(param_1,1,5);
  luaL_error(param_1,"\'setn\' is obsolete");
  lua_pushvalue(param_1,1);
  return 1;
}
