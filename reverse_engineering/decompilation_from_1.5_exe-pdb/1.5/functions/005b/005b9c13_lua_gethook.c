/*
 * Entry: 005b9c13
 * Name: lua_gethook
 * Namespace: Global
 * Signature: _func___cdecl_void_lua_State_ptr_lua_Debug_ptr * lua_gethook(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_func___cdecl_void_lua_State_ptr_lua_Debug_ptr * __cdecl lua_gethook(lua_State *param_1)

{
  return param_1->hook;
}
