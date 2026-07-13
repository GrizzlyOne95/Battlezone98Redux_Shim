/*
 * Entry: 00417ed9
 * Name: CountUnitsNearObject
 * Namespace: Global
 * Signature: int CountUnitsNearObject(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl CountUnitsNearObject(lua_State *param_1)

{
  int iVar1;
  int iVar2;
  char *pcVar3;
  double dVar4;
  
  iVar1 = GetHandle(param_1,1);
  dVar4 = luaL_checknumber(param_1,2);
  iVar2 = luaL_optinteger(param_1,3,-1);
  pcVar3 = luaL_optlstring(param_1,4,(char *)0x0,(uint *)0x0);
  iVar1 = CountUnitsNearObject(iVar1,(float)dVar4,iVar2,pcVar3);
  lua_pushinteger(param_1,iVar1);
  return 1;
}
