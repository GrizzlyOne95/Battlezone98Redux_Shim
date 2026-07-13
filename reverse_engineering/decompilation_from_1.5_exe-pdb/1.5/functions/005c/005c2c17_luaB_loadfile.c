/*
 * Entry: 005c2c17
 * Name: luaB_loadfile
 * Namespace: Global
 * Signature: int luaB_loadfile(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl luaB_loadfile(lua_State *param_1)

{
  char *pcVar1;
  int iVar2;
  
  pcVar1 = luaL_optlstring(param_1,1,(char *)0x0,(uint *)0x0);
  iVar2 = luaL_loadfile(param_1,pcVar1);
  iVar2 = load_aux(param_1,iVar2);
  return iVar2;
}
