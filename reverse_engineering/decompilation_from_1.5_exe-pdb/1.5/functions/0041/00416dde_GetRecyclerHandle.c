/*
 * Entry: 00416dde
 * Name: GetRecyclerHandle
 * Namespace: Global
 * Signature: int GetRecyclerHandle(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl GetRecyclerHandle(lua_State *param_1)

{
  int iVar1;
  
  iVar1 = lua_isnumber(param_1,1);
  if (iVar1 == 0) {
    iVar1 = GetTeamSlot(TEAM_SLOT_RECYCLER);
  }
  else {
    iVar1 = lua_tointeger(param_1,1);
    iVar1 = GetTeamSlot(TEAM_SLOT_RECYCLER,iVar1);
  }
  PushHandle(param_1,iVar1);
  return 1;
}
