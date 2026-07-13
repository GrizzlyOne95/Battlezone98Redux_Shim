/*
 * Entry: 00418087
 * Name: AddMaxPilot
 * Namespace: Global
 * Signature: int AddMaxPilot(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl AddMaxPilot(lua_State *param_1)

{
  int iVar1;
  int iVar2;
  
  iVar1 = luaL_checkinteger(param_1,1);
  iVar2 = luaL_checkinteger(param_1,2);
  iVar1 = AddMaxPilot(iVar1,iVar2);
  lua_pushinteger(param_1,iVar1);
  return 1;
}
