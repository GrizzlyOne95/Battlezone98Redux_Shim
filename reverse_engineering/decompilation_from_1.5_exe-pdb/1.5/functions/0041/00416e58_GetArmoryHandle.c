/*
 * Entry: 00416e58
 * Name: GetArmoryHandle
 * Namespace: Global
 * Signature: int GetArmoryHandle(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl GetArmoryHandle(lua_State *param_1)

{
  int iVar1;
  
  iVar1 = lua_isnumber(param_1,1);
  if (iVar1 == 0) {
    iVar1 = GetTeamSlot(TEAM_SLOT_ARMORY);
  }
  else {
    iVar1 = lua_tointeger(param_1,1);
    iVar1 = GetTeamSlot(TEAM_SLOT_ARMORY,iVar1);
  }
  PushHandle(param_1,iVar1);
  return 1;
}
