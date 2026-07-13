/*
 * Entry: 005b6db7
 * Name: luaL_checkstack
 * Namespace: Global
 * Signature: void luaL_checkstack(lua_State * param_1, int param_2, char * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl luaL_checkstack(lua_State *param_1,int param_2,char *param_3)

{
  int iVar1;
  
  iVar1 = lua_checkstack(param_1,param_2);
  if (iVar1 == 0) {
    luaL_error(param_1,"stack overflow (%s)");
  }
  return;
}
