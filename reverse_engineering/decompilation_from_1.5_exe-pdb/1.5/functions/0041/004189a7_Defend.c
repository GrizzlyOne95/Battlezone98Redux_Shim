/*
 * Entry: 004189a7
 * Name: Defend
 * Namespace: Global
 * Signature: int Defend(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl Defend(lua_State *param_1)

{
  int iVar1;
  int iVar2;
  
  iVar1 = GetHandle(param_1,1);
  iVar2 = luaL_optinteger(param_1,2,1);
  Defend(iVar1,iVar2);
  return 0;
}
