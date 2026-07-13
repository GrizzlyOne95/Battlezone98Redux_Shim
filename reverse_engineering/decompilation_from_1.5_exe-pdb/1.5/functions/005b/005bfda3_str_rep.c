/*
 * Entry: 005bfda3
 * Name: str_rep
 * Namespace: Global
 * Signature: int str_rep(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

int __cdecl str_rep(lua_State *param_1)

{
  char *pcVar1;
  int iVar2;
  uint local_218;
  luaL_Buffer local_214;
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  pcVar1 = luaL_checklstring(param_1,1,&local_218);
  iVar2 = luaL_checkinteger(param_1,2);
  luaL_buffinit(param_1,&local_214);
  for (; 0 < iVar2; iVar2 = iVar2 + -1) {
    luaL_addlstring(&local_214,pcVar1,local_218);
  }
  luaL_pushresult(&local_214);
  return 1;
}
