/*
 * Entry: 00418165
 * Name: GetScrap
 * Namespace: Global
 * Signature: int GetScrap(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl GetScrap(lua_State *param_1)

{
  int iVar1;
  
  iVar1 = luaL_checkinteger(param_1,1);
  iVar1 = GetScrap(iVar1);
  lua_pushinteger(param_1,iVar1);
  return 1;
}
