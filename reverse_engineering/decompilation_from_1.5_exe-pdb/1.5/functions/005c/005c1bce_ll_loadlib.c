/*
 * Entry: 005c1bce
 * Name: ll_loadlib
 * Namespace: Global
 * Signature: int ll_loadlib(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl ll_loadlib(lua_State *param_1)

{
  lua_State *plVar1;
  char *pcVar2;
  int iVar3;
  lua_State *plVar4;
  
  plVar1 = (lua_State *)luaL_checklstring(param_1,1,(uint *)0x0);
  plVar4 = param_1;
  pcVar2 = luaL_checklstring(param_1,2,(uint *)0x0);
  iVar3 = ll_loadfunc(plVar1,pcVar2,(char *)plVar4);
  if (iVar3 == 0) {
    iVar3 = 1;
  }
  else {
    lua_pushnil(param_1);
    lua_insert(param_1,-2);
    pcVar2 = "open";
    if (iVar3 != 1) {
      pcVar2 = "init";
    }
    lua_pushstring(param_1,pcVar2);
    iVar3 = 3;
  }
  return iVar3;
}
