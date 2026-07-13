/*
 * Entry: 005c27f3
 * Name: getfunc
 * Namespace: Global
 * Signature: void getfunc(lua_State * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __cdecl getfunc(lua_State *param_1,int param_2)

{
  int iVar1;
  lua_State *unaff_ESI;
  lua_Debug local_6c;
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  iVar1 = lua_type(unaff_ESI,1);
  if (iVar1 == 6) {
    lua_pushvalue(unaff_ESI,1);
  }
  else {
    if (param_1 == (lua_State *)0x0) {
      iVar1 = luaL_checkinteger(unaff_ESI,1);
    }
    else {
      iVar1 = luaL_optinteger(unaff_ESI,1,1);
    }
    if (iVar1 < 0) {
      luaL_argerror(unaff_ESI,1,"level must be non-negative");
    }
    iVar1 = lua_getstack(unaff_ESI,iVar1,&local_6c);
    if (iVar1 == 0) {
      luaL_argerror(unaff_ESI,1,"invalid level");
    }
    lua_getinfo(unaff_ESI,"f",&local_6c);
    iVar1 = lua_type(unaff_ESI,-1);
    if (iVar1 == 0) {
      luaL_error(unaff_ESI,"no function environment for tail call at level %d");
    }
  }
  return;
}
