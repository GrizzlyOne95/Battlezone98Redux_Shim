/*
 * Entry: 005b5cfd
 * Name: lua_atpanic
 * Namespace: Global
 * Signature: _func___cdecl_int_lua_State_ptr * lua_atpanic(lua_State * param_1, _func___cdecl_int_lua_State_ptr * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_func___cdecl_int_lua_State_ptr * __cdecl
lua_atpanic(lua_State *param_1,_func___cdecl_int_lua_State_ptr *param_2)

{
  _func___cdecl_int_lua_State_ptr *p_Var1;
  
  p_Var1 = param_1->l_G->panic;
  param_1->l_G->panic = param_2;
  return p_Var1;
}
