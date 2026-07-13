/*
 * Entry: 005b6999
 * Name: lua_dump
 * Namespace: Global
 * Signature: int lua_dump(lua_State * param_1, _func___cdecl_int_lua_State_ptr_void_ptr_uint_void_ptr * param_2, void * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl
lua_dump(lua_State *param_1,_func___cdecl_int_lua_State_ptr_void_ptr_uint_void_ptr *param_2,
        void *param_3)

{
  int iVar1;
  
  if ((param_1->top[-1].tt == 6) && (iVar1 = param_1->top[-1].value.b, *(char *)(iVar1 + 6) == '\0')
     ) {
    iVar1 = luaU_dump(param_1,*(Proto **)(iVar1 + 0x10),param_2,param_3,0);
    return iVar1;
  }
  return 1;
}
