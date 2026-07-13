/*
 * Entry: 004185fe
 * Name: StartCockpitTimerUp
 * Namespace: Global
 * Signature: int StartCockpitTimerUp(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl StartCockpitTimerUp(lua_State *param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar1 = luaL_checkinteger(param_1,1);
  iVar2 = luaL_optinteger(param_1,2,0x7fffffff);
  iVar3 = luaL_optinteger(param_1,3,0x7fffffff);
  StartCockpitTimerUp(iVar1,iVar2,iVar3);
  return 0;
}
