/*
 * Entry: 005b9be7
 * Name: lua_sethook
 * Namespace: Global
 * Signature: int lua_sethook(lua_State * param_1, _func___cdecl_void_lua_State_ptr_lua_Debug_ptr * param_2, int param_3, int param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl
lua_sethook(lua_State *param_1,_func___cdecl_void_lua_State_ptr_lua_Debug_ptr *param_2,int param_3,
           int param_4)

{
  if ((param_2 == (_func___cdecl_void_lua_State_ptr_lua_Debug_ptr *)0x0) || (param_3 == 0)) {
    param_3 = 0;
    param_2 = (_func___cdecl_void_lua_State_ptr_lua_Debug_ptr *)0x0;
  }
  param_1->hook = param_2;
  param_1->basehookcount = param_4;
  param_1->hookcount = param_4;
  param_1->hookmask = (uchar)param_3;
  return 1;
}
