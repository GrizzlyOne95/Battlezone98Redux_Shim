/*
 * Entry: 005b74cd
 * Name: luaL_newstate
 * Namespace: Global
 * Signature: lua_State * luaL_newstate(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

lua_State * __cdecl luaL_newstate(void)

{
  lua_State *plVar1;
  
  plVar1 = lua_newstate(l_alloc,(void *)0x0);
  if (plVar1 != (lua_State *)0x0) {
    lua_atpanic(plVar1,panic);
  }
  return plVar1;
}
