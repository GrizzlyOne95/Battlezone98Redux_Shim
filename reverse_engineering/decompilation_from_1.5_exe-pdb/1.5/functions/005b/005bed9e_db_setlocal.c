/*
 * Entry: 005bed9e
 * Name: db_setlocal
 * Namespace: Global
 * Signature: int db_setlocal(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

int __cdecl db_setlocal(lua_State *param_1)

{
  lua_State *plVar1;
  int iVar2;
  char *pcVar3;
  int *unaff_EDI;
  lua_Debug *plVar4;
  int local_74;
  lua_Debug local_6c;
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  plVar1 = getthread(param_1,unaff_EDI);
  plVar4 = &local_6c;
  iVar2 = luaL_checkinteger(param_1,local_74 + 1);
  iVar2 = lua_getstack(plVar1,iVar2,plVar4);
  if (iVar2 == 0) {
    iVar2 = luaL_argerror(param_1,local_74 + 1,"level out of range");
  }
  else {
    luaL_checkany(param_1,local_74 + 3);
    lua_settop(param_1,local_74 + 3);
    lua_xmove(param_1,plVar1,1);
    iVar2 = luaL_checkinteger(param_1,local_74 + 2);
    pcVar3 = lua_setlocal(plVar1,&local_6c,iVar2);
    lua_pushstring(param_1,pcVar3);
    iVar2 = 1;
  }
  return iVar2;
}
