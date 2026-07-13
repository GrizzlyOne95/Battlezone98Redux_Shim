/*
 * Entry: 005b8304
 * Name: luaD_rawrunprotected
 * Namespace: Global
 * Signature: int luaD_rawrunprotected(lua_State * param_1, _func___cdecl_void_lua_State_ptr_void_ptr * param_2, void * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl
luaD_rawrunprotected
          (lua_State *param_1,_func___cdecl_void_lua_State_ptr_void_ptr *param_2,void *param_3)

{
  int iVar1;
  lua_longjmp local_4c;
  
  local_4c.previous = param_1->errorJmp;
  param_1->errorJmp = &local_4c;
  local_4c.status = 0;
  iVar1 = setjmp3(local_4c.b,0);
  if (iVar1 == 0) {
    (*param_2)(param_1,param_3);
  }
  param_1->errorJmp = local_4c.previous;
  return local_4c.status;
}
