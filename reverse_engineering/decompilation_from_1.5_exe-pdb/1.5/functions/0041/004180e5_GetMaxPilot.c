/*
 * Entry: 004180e5
 * Name: GetMaxPilot
 * Namespace: Global
 * Signature: int GetMaxPilot(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl GetMaxPilot(lua_State *param_1)

{
  int iVar1;
  
  iVar1 = luaL_checkinteger(param_1,1);
  iVar1 = GetMaxPilot(iVar1);
  lua_pushinteger(param_1,iVar1);
  return 1;
}
