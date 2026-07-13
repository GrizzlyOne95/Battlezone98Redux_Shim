/*
 * Entry: 00416d95
 * Name: GetTeamSlot
 * Namespace: Global
 * Signature: int GetTeamSlot(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl GetTeamSlot(lua_State *param_1)

{
  TEAM_SLOT TVar1;
  int iVar2;
  
  TVar1 = luaL_checkinteger(param_1,1);
  iVar2 = lua_isnumber(param_1,2);
  if (iVar2 == 0) {
    iVar2 = GetTeamSlot(TVar1);
  }
  else {
    iVar2 = lua_tointeger(param_1,2);
    iVar2 = GetTeamSlot(TVar1,iVar2);
  }
  PushHandle(param_1,iVar2);
  return 1;
}
