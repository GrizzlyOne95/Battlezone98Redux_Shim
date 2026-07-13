/*
 * Entry: 00418a67
 * Name: Retreat
 * Namespace: Global
 * Signature: int Retreat(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl Retreat(lua_State *param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  char *pcVar4;
  
  iVar1 = GetHandle(param_1,1);
  iVar2 = luaL_optinteger(param_1,3,1);
  iVar3 = lua_isstring(param_1,2);
  if (iVar3 == 0) {
    iVar3 = GetHandle(param_1,2);
    Retreat(iVar1,iVar3,iVar2);
  }
  else {
    pcVar4 = lua_tolstring(param_1,2,(uint *)0x0);
    Retreat(iVar1,pcVar4,iVar2);
  }
  return 0;
}
