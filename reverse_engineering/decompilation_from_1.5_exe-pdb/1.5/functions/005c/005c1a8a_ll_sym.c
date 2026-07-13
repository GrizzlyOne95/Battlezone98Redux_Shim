/*
 * Entry: 005c1a8a
 * Name: ll_sym
 * Namespace: Global
 * Signature: _func___cdecl_int_lua_State_ptr * ll_sym(lua_State * param_1, void * param_2, char * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_func___cdecl_int_lua_State_ptr * __cdecl ll_sym(lua_State *param_1,void *param_2,char *param_3)

{
  _func___cdecl_int_lua_State_ptr *p_Var1;
  lua_State *unaff_ESI;
  
  p_Var1 = (_func___cdecl_int_lua_State_ptr *)GetProcAddress((HMODULE)param_1,param_2);
  if (p_Var1 == (_func___cdecl_int_lua_State_ptr *)0x0) {
    pusherror(unaff_ESI);
  }
  return p_Var1;
}
