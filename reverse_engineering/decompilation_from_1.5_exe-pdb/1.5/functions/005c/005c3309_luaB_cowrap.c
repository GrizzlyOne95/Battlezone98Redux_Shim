/*
 * Entry: 005c3309
 * Name: luaB_cowrap
 * Namespace: Global
 * Signature: int luaB_cowrap(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl luaB_cowrap(lua_State *param_1)

{
  luaB_cocreate(param_1);
  lua_pushcclosure(param_1,luaB_auxwrap,1);
  return 1;
}
