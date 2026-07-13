/*
 * Entry: 004170a2
 * Name: GetTeamNum
 * Namespace: Global
 * Signature: int GetTeamNum(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl GetTeamNum(lua_State *param_1)

{
  int iVar1;
  
  iVar1 = GetHandle(param_1,1);
  iVar1 = GetTeamNum(iVar1);
  lua_pushinteger(param_1,iVar1);
  return 1;
}
