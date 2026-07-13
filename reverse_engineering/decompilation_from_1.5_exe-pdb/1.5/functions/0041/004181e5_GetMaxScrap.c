/*
 * Entry: 004181e5
 * Name: GetMaxScrap
 * Namespace: Global
 * Signature: int GetMaxScrap(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl GetMaxScrap(lua_State *param_1)

{
  int iVar1;
  
  iVar1 = luaL_checkinteger(param_1,1);
  iVar1 = GetMaxScrap(iVar1);
  lua_pushinteger(param_1,iVar1);
  return 1;
}
