/*
 * Entry: 005b7c9d
 * Name: luaE_freethread
 * Namespace: Global
 * Signature: void luaE_freethread(lua_State * param_1, lua_State * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl luaE_freethread(lua_State *param_1,lua_State *param_2)

{
  lua_State *plVar1;
  
  plVar1 = param_2;
  luaF_close(param_2,param_2->stack);
  freestack(param_1,plVar1);
  luaM_realloc_(param_1,param_2,0x78,0);
  return;
}
