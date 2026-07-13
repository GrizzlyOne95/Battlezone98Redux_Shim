/*
 * Entry: 005bffa3
 * Name: str_dump
 * Namespace: Global
 * Signature: int str_dump(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

int __cdecl str_dump(lua_State *param_1)

{
  int iVar1;
  luaL_Buffer local_214;
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  luaL_checktype(param_1,1,6);
  lua_settop(param_1,1);
  luaL_buffinit(param_1,&local_214);
  iVar1 = lua_dump(param_1,writer,&local_214);
  if (iVar1 != 0) {
    luaL_error(param_1,"unable to dump given function");
  }
  luaL_pushresult(&local_214);
  return 1;
}
