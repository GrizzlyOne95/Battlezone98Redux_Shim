/*
 * Entry: 005b6cbd
 * Name: luaL_where
 * Namespace: Global
 * Signature: void luaL_where(lua_State * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __cdecl luaL_where(lua_State *param_1,int param_2)

{
  int iVar1;
  lua_Debug local_6c;
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  iVar1 = lua_getstack(param_1,param_2,&local_6c);
  if ((iVar1 != 0) && (lua_getinfo(param_1,"Sl",&local_6c), 0 < local_6c.currentline)) {
    lua_pushfstring(param_1,"%s:%d: ");
    return;
  }
  lua_pushlstring(param_1,"",0);
  return;
}
