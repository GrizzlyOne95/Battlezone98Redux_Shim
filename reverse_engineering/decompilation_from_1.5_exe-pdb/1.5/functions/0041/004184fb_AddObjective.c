/*
 * Entry: 004184fb
 * Name: AddObjective
 * Namespace: Global
 * Signature: int AddObjective(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl AddObjective(lua_State *param_1)

{
  char *pcVar1;
  char *pcVar2;
  long lVar3;
  double dVar4;
  
  pcVar1 = luaL_checklstring(param_1,1,(uint *)0x0);
  pcVar2 = luaL_optlstring(param_1,2,"WHITE",(uint *)0x0);
  lVar3 = GetColor(pcVar2);
  dVar4 = luaL_optnumber(param_1,3,8.0);
  AddObjective(pcVar1,lVar3,(float)dVar4);
  return 0;
}
