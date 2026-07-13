/*
 * Entry: 005c335c
 * Name: auxopen
 * Namespace: Global
 * Signature: void auxopen(lua_State * param_1, char * param_2, _func___cdecl_int_lua_State_ptr * param_3, _func___cdecl_int_lua_State_ptr * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
auxopen(lua_State *param_1,char *param_2,_func___cdecl_int_lua_State_ptr *param_3,
       _func___cdecl_int_lua_State_ptr *param_4)

{
  lua_pushcclosure(param_1,param_4,0);
  lua_pushcclosure(param_1,param_3,1);
  lua_setfield(param_1,-2,param_2);
  return;
}
