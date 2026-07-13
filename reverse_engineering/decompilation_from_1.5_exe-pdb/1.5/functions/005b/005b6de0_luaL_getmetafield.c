/*
 * Entry: 005b6de0
 * Name: luaL_getmetafield
 * Namespace: Global
 * Signature: int luaL_getmetafield(lua_State * param_1, int param_2, char * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl luaL_getmetafield(lua_State *param_1,int param_2,char *param_3)

{
  int iVar1;
  
  iVar1 = lua_getmetatable(param_1,param_2);
  if (iVar1 == 0) {
    return 0;
  }
  lua_pushstring(param_1,param_3);
  lua_rawget(param_1,-2);
  iVar1 = lua_type(param_1,-1);
  if (iVar1 != 0) {
    lua_remove(param_1,-2);
  }
  else {
    lua_settop(param_1,-3);
  }
  return (uint)(iVar1 != 0);
}
