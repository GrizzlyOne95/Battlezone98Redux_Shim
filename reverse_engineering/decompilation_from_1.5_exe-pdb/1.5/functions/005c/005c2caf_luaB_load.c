/*
 * Entry: 005c2caf
 * Name: luaB_load
 * Namespace: Global
 * Signature: int luaB_load(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl luaB_load(lua_State *param_1)

{
  char *pcVar1;
  int iVar2;
  
  pcVar1 = luaL_optlstring(param_1,2,"=(load)",(uint *)0x0);
  luaL_checktype(param_1,1,6);
  lua_settop(param_1,3);
  iVar2 = lua_load(param_1,generic_reader,(void *)0x0,pcVar1);
  iVar2 = load_aux(param_1,iVar2);
  return iVar2;
}
