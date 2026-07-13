/*
 * Entry: 005b7679
 * Name: luaL_checkany
 * Namespace: Global
 * Signature: void luaL_checkany(lua_State * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl luaL_checkany(lua_State *param_1,int param_2)

{
  int iVar1;
  
  iVar1 = lua_type(param_1,param_2);
  if (iVar1 == -1) {
    luaL_argerror(param_1,param_2,"value expected");
  }
  return;
}
