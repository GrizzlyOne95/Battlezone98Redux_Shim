/*
 * Entry: 004170eb
 * Name: GetPerceivedTeam
 * Namespace: Global
 * Signature: int GetPerceivedTeam(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl GetPerceivedTeam(lua_State *param_1)

{
  int iVar1;
  
  iVar1 = GetHandle(param_1,1);
  iVar1 = GetPerceivedTeam(iVar1);
  lua_pushinteger(param_1,iVar1);
  return 1;
}
