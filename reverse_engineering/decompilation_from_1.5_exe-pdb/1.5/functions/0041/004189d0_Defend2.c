/*
 * Entry: 004189d0
 * Name: Defend2
 * Namespace: Global
 * Signature: int Defend2(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl Defend2(lua_State *param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar1 = GetHandle(param_1,1);
  iVar2 = GetHandle(param_1,2);
  iVar3 = luaL_optinteger(param_1,3,1);
  Defend2(iVar1,iVar2,iVar3);
  return 0;
}
