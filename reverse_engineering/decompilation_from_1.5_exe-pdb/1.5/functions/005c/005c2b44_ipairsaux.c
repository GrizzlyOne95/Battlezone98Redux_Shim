/*
 * Entry: 005c2b44
 * Name: ipairsaux
 * Namespace: Global
 * Signature: int ipairsaux(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl ipairsaux(lua_State *param_1)

{
  int iVar1;
  
  iVar1 = luaL_checkinteger(param_1,2);
  luaL_checktype(param_1,1,5);
  lua_pushinteger(param_1,iVar1 + 1);
  lua_rawgeti(param_1,1,iVar1 + 1);
  iVar1 = lua_type(param_1,-1);
  return -(uint)(iVar1 != 0) & 2;
}
