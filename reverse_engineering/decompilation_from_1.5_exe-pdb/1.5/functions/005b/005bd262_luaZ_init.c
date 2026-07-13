/*
 * Entry: 005bd262
 * Name: luaZ_init
 * Namespace: Global
 * Signature: void luaZ_init(lua_State * param_1, Zio * param_2, _func___cdecl_char_ptr_lua_State_ptr_void_ptr_uint_ptr * param_3, void * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
luaZ_init(lua_State *param_1,Zio *param_2,
         _func___cdecl_char_ptr_lua_State_ptr_void_ptr_uint_ptr *param_3,void *param_4)

{
  param_2->n = 0;
  param_2->p = (char *)0x0;
  param_2->L = param_1;
  param_2->reader = param_3;
  param_2->data = param_4;
  return;
}
