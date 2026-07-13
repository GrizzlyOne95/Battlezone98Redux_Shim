/*
 * Entry: 00418187
 * Name: AddMaxScrap
 * Namespace: Global
 * Signature: int AddMaxScrap(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl AddMaxScrap(lua_State *param_1)

{
  int iVar1;
  int iVar2;
  
  iVar1 = luaL_checkinteger(param_1,1);
  iVar2 = luaL_checkinteger(param_1,2);
  iVar1 = AddMaxScrap(iVar1,iVar2);
  lua_pushinteger(param_1,iVar1);
  return 1;
}
