/*
 * Entry: 005b692f
 * Name: lua_cpcall
 * Namespace: Global
 * Signature: int lua_cpcall(lua_State * param_1, _func___cdecl_int_lua_State_ptr * param_2, void * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl lua_cpcall(lua_State *param_1,_func___cdecl_int_lua_State_ptr *param_2,void *param_3)

{
  int iVar1;
  _func___cdecl_int_lua_State_ptr *local_c;
  void *local_8;
  
  local_c = param_2;
  local_8 = param_3;
  iVar1 = luaD_pcall(param_1,f_Ccall,&local_c,(int)param_1->top - (int)param_1->stack,0);
  return iVar1;
}
