/*
 * Entry: 00418383
 * Name: SetAIP
 * Namespace: Global
 * Signature: int SetAIP(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl SetAIP(lua_State *param_1)

{
  char *pcVar1;
  int iVar2;
  
  pcVar1 = luaL_checklstring(param_1,1,(uint *)0x0);
  iVar2 = luaL_optinteger(param_1,2,2);
  SetAIP(pcVar1,iVar2);
  return 0;
}
