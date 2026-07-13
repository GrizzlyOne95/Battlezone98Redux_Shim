/*
 * Entry: 005b7dff
 * Name: luaL_openlibs
 * Namespace: Global
 * Signature: void luaL_openlibs(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl luaL_openlibs(lua_State *param_1)

{
  code *pcVar1;
  luaL_Reg *plVar2;
  
  pcVar1 = luaopen_base;
  plVar2 = lualibs;
  do {
    lua_pushcclosure(param_1,pcVar1,0);
    lua_pushstring(param_1,plVar2->name);
    lua_call(param_1,1,0);
    pcVar1 = plVar2[1].func;
    plVar2 = plVar2 + 1;
  } while (pcVar1 != (_func___cdecl_int_lua_State_ptr *)0x0);
  return;
}
