/*
 * Entry: 005b61ac
 * Name: lua_tocfunction
 * Namespace: Global
 * Signature: _func___cdecl_int_lua_State_ptr * lua_tocfunction(lua_State * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_func___cdecl_int_lua_State_ptr * __cdecl lua_tocfunction(lua_State *param_1,int param_2)

{
  lua_TValue *plVar1;
  lua_State *unaff_retaddr;
  
  plVar1 = index2adr(unaff_retaddr,(int)param_1);
  if ((plVar1->tt == 6) && (*(char *)((plVar1->value).b + 6) != '\0')) {
    return *(_func___cdecl_int_lua_State_ptr **)((plVar1->value).b + 0x10);
  }
  return (_func___cdecl_int_lua_State_ptr *)0x0;
}
