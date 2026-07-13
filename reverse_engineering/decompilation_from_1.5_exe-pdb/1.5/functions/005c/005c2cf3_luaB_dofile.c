/*
 * Entry: 005c2cf3
 * Name: luaB_dofile
 * Namespace: Global
 * Signature: int luaB_dofile(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl luaB_dofile(lua_State *param_1)

{
  char *pcVar1;
  int iVar2;
  int iVar3;
  
  pcVar1 = luaL_optlstring(param_1,1,(char *)0x0,(uint *)0x0);
  iVar2 = lua_gettop(param_1);
  iVar3 = luaL_loadfile(param_1,pcVar1);
  if (iVar3 != 0) {
    lua_error(param_1);
  }
  lua_call(param_1,0,-1);
  iVar3 = lua_gettop(param_1);
  return iVar3 - iVar2;
}
