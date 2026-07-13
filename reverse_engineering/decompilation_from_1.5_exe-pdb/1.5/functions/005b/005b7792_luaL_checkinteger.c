/*
 * Entry: 005b7792
 * Name: luaL_checkinteger
 * Namespace: Global
 * Signature: int luaL_checkinteger(lua_State * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl luaL_checkinteger(lua_State *param_1,int param_2)

{
  int iVar1;
  int iVar2;
  
  iVar1 = lua_tointeger(param_1,param_2);
  if (iVar1 == 0) {
    iVar2 = lua_isnumber(param_1,param_2);
    if (iVar2 == 0) {
      tag_error(param_1,param_2,3);
    }
  }
  return iVar1;
}
