/*
 * Entry: 005b6960
 * Name: lua_load
 * Namespace: Global
 * Signature: int lua_load(lua_State * param_1, _func___cdecl_char_ptr_lua_State_ptr_void_ptr_uint_ptr * param_2, void * param_3, char * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl
lua_load(lua_State *param_1,_func___cdecl_char_ptr_lua_State_ptr_void_ptr_uint_ptr *param_2,
        void *param_3,char *param_4)

{
  int iVar1;
  Zio local_18;
  
  if (param_4 == (char *)0x0) {
    param_4 = "?";
  }
  luaZ_init(param_1,&local_18,param_2,param_3);
  iVar1 = luaD_protectedparser(param_1,&local_18,param_4);
  return iVar1;
}
