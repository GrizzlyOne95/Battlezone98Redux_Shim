/*
 * Entry: 00417957
 * Name: IsTeamAllied
 * Namespace: Global
 * Signature: int IsTeamAllied(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl IsTeamAllied(lua_State *param_1)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  
  iVar2 = luaL_checkinteger(param_1,1);
  iVar3 = luaL_checkinteger(param_1,2);
  bVar1 = IsTeamAllied(iVar2,iVar3);
  lua_pushboolean(param_1,(uint)bVar1);
  return 1;
}
