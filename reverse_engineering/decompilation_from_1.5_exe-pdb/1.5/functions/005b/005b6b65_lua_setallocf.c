/*
 * Entry: 005b6b65
 * Name: lua_setallocf
 * Namespace: Global
 * Signature: void lua_setallocf(lua_State * param_1, _func___cdecl_void_ptr_void_ptr_void_ptr_uint_uint * param_2, void * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
lua_setallocf(lua_State *param_1,_func___cdecl_void_ptr_void_ptr_void_ptr_uint_uint *param_2,
             void *param_3)

{
  param_1->l_G->ud = param_3;
  param_1->l_G->frealloc = param_2;
  return;
}
