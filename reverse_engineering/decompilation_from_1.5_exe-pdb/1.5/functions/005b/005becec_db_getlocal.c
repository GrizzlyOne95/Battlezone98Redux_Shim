/*
 * Entry: 005becec
 * Name: db_getlocal
 * Namespace: Global
 * Signature: int db_getlocal(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

int __cdecl db_getlocal(lua_State *param_1)

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
    iVar2 = luaL_checkinteger(param_1,local_74 + 2);
    pcVar3 = lua_getlocal(plVar1,&local_6c,iVar2);
    if (pcVar3 == (char *)0x0) {
      lua_pushnil(param_1);
      iVar2 = 1;
    }
    else {
      lua_xmove(plVar1,param_1,1);
      lua_pushstring(param_1,pcVar3);
      lua_pushvalue(param_1,-2);
      iVar2 = 2;
    }
  }
  return iVar2;
}
