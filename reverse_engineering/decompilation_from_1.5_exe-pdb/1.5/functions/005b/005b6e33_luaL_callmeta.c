/*
 * Entry: 005b6e33
 * Name: luaL_callmeta
 * Namespace: Global
 * Signature: int luaL_callmeta(lua_State * param_1, int param_2, char * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl luaL_callmeta(lua_State *param_1,int param_2,char *param_3)

{
  int iVar1;
  
  if (param_2 + 9999U < 10000) {
    iVar1 = lua_gettop(param_1);
    param_2 = param_2 + 1 + iVar1;
  }
  iVar1 = luaL_getmetafield(param_1,param_2,param_3);
  if (iVar1 != 0) {
    lua_pushvalue(param_1,param_2);
    lua_call(param_1,1,1);
  }
  return (uint)(iVar1 != 0);
}
