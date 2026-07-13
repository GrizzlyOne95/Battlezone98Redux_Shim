/*
 * Entry: 005b6d60
 * Name: luaL_newmetatable
 * Namespace: Global
 * Signature: int luaL_newmetatable(lua_State * param_1, char * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl luaL_newmetatable(lua_State *param_1,char *param_2)

{
  int iVar1;
  
  lua_getfield(param_1,-10000,param_2);
  iVar1 = lua_type(param_1,-1);
  if (iVar1 == 0) {
    lua_settop(param_1,-2);
    lua_createtable(param_1,0,0);
    lua_pushvalue(param_1,-1);
    lua_setfield(param_1,-10000,param_2);
  }
  return (uint)(iVar1 == 0);
}
