/*
 * Entry: 005b7a70
 * Name: luaL_register
 * Namespace: Global
 * Signature: void luaL_register(lua_State * param_1, char * param_2, luaL_Reg * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl luaL_register(lua_State *param_1,char *param_2,luaL_Reg *param_3)

{
  luaL_openlib(param_1,param_2,param_3,0);
  return;
}
