/*
 * Entry: 005b77cf
 * Name: luaL_optinteger
 * Namespace: Global
 * Signature: int luaL_optinteger(lua_State * param_1, int param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl luaL_optinteger(lua_State *param_1,int param_2,int param_3)

{
  int iVar1;
  
  iVar1 = lua_type(param_1,param_2);
  if (iVar1 < 1) {
    return param_3;
  }
  iVar1 = luaL_checkinteger(param_1,param_2);
  return iVar1;
}
