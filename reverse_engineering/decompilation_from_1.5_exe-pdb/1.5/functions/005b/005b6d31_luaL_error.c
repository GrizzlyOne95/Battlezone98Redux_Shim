/*
 * Entry: 005b6d31
 * Name: luaL_error
 * Namespace: Global
 * Signature: int luaL_error(lua_State * param_1, char * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl luaL_error(lua_State *param_1,char *param_2)

{
  int iVar1;
  
  luaL_where(param_1,1);
  lua_pushvfstring(param_1,param_2,&stack0x0000000c);
  lua_concat(param_1,2);
  iVar1 = lua_error(param_1);
  return iVar1;
}
