/*
 * Entry: 00416e96
 * Name: GetConstructorHandle
 * Namespace: Global
 * Signature: int GetConstructorHandle(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl GetConstructorHandle(lua_State *param_1)

{
  int iVar1;
  
  iVar1 = lua_isnumber(param_1,1);
  if (iVar1 == 0) {
    iVar1 = GetTeamSlot(TEAM_SLOT_CONSTRUCT);
  }
  else {
    iVar1 = lua_tointeger(param_1,1);
    iVar1 = GetTeamSlot(TEAM_SLOT_CONSTRUCT,iVar1);
  }
  PushHandle(param_1,iVar1);
  return 1;
}
