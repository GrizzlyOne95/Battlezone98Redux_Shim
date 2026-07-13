/*
 * Entry: 00418065
 * Name: GetPilot
 * Namespace: Global
 * Signature: int GetPilot(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl GetPilot(lua_State *param_1)

{
  int iVar1;
  
  iVar1 = luaL_checkinteger(param_1,1);
  iVar1 = GetPilot(iVar1);
  lua_pushinteger(param_1,iVar1);
  return 1;
}
