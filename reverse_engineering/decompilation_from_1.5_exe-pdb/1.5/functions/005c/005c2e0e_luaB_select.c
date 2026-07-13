/*
 * Entry: 005c2e0e
 * Name: luaB_select
 * Namespace: Global
 * Signature: int luaB_select(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl luaB_select(lua_State *param_1)

{
  int iVar1;
  int iVar2;
  char *pcVar3;
  
  iVar1 = lua_gettop(param_1);
  iVar2 = lua_type(param_1,1);
  if ((iVar2 == 4) && (pcVar3 = lua_tolstring(param_1,1,(uint *)0x0), *pcVar3 == '#')) {
    lua_pushinteger(param_1,iVar1 + -1);
    return 1;
  }
  iVar2 = luaL_checkinteger(param_1,1);
  if (iVar2 < 0) {
    iVar2 = iVar2 + iVar1;
  }
  else if (iVar1 < iVar2) {
    iVar2 = iVar1;
  }
  if (iVar2 < 1) {
    luaL_argerror(param_1,1,"index out of range");
  }
  return iVar1 - iVar2;
}
