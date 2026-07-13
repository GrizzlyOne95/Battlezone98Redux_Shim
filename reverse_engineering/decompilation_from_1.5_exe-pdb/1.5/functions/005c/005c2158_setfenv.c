/*
 * Entry: 005c2158
 * Name: setfenv
 * Namespace: Global
 * Signature: void setfenv(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __cdecl setfenv(lua_State *param_1)

{
  int iVar1;
  lua_State *unaff_ESI;
  lua_Debug local_6c;
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  iVar1 = lua_getstack(unaff_ESI,1,&local_6c);
  if (iVar1 != 0) {
    iVar1 = lua_getinfo(unaff_ESI,"f",&local_6c);
    if (iVar1 != 0) {
      iVar1 = lua_iscfunction(unaff_ESI,-1);
      if (iVar1 == 0) goto LAB_005c21ac;
    }
  }
  luaL_error(unaff_ESI,"\'module\' not called from a Lua function");
LAB_005c21ac:
  lua_pushvalue(unaff_ESI,-2);
  lua_setfenv(unaff_ESI,-2);
  lua_settop(unaff_ESI,-2);
  return;
}
