/*
 * Entry: 005c344e
 * Name: luaopen_base
 * Namespace: Global
 * Signature: int luaopen_base(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl luaopen_base(lua_State *param_1)

{
  lua_State *unaff_ESI;
  
  base_open(unaff_ESI);
  luaL_register(param_1,"coroutine",co_funcs);
  return 2;
}
