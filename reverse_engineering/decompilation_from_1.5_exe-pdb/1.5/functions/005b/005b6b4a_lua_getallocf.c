/*
 * Entry: 005b6b4a
 * Name: lua_getallocf
 * Namespace: Global
 * Signature: _func___cdecl_void_ptr_void_ptr_void_ptr_uint_uint * lua_getallocf(lua_State * param_1, void * * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_func___cdecl_void_ptr_void_ptr_void_ptr_uint_uint * __cdecl
lua_getallocf(lua_State *param_1,void **param_2)

{
  if (param_2 != (void **)0x0) {
    *param_2 = param_1->l_G->ud;
  }
  return param_1->l_G->frealloc;
}
