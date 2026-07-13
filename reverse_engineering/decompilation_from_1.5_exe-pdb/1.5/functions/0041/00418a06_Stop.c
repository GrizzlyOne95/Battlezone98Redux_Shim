/*
 * Entry: 00418a06
 * Name: Stop
 * Namespace: Global
 * Signature: int Stop(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl Stop(lua_State *param_1)

{
  int iVar1;
  int iVar2;
  
  iVar1 = GetHandle(param_1,1);
  iVar2 = luaL_optinteger(param_1,2,1);
  Stop(iVar1,iVar2);
  return 0;
}
