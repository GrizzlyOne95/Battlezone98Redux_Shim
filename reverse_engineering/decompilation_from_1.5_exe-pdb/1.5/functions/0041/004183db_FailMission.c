/*
 * Entry: 004183db
 * Name: FailMission
 * Namespace: Global
 * Signature: int FailMission(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl FailMission(lua_State *param_1)

{
  char *pcVar1;
  double dVar2;
  
  dVar2 = luaL_checknumber(param_1,1);
  pcVar1 = luaL_optlstring(param_1,2,(char *)0x0,(uint *)0x0);
  FailMission((float)dVar2,pcVar1);
  return 0;
}
