/*
 * Entry: 005bfbe0
 * Name: str_reverse
 * Namespace: Global
 * Signature: int str_reverse(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

int __cdecl str_reverse(lua_State *param_1)

{
  char *pcVar1;
  uint local_218;
  luaL_Buffer local_214;
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)(local_214.buffer + 0x70);
  pcVar1 = luaL_checklstring(param_1,1,&local_218);
  luaL_buffinit(param_1,&local_214);
  while (local_218 != 0) {
    local_218 = local_218 - 1;
    if (&local_8 <= local_214.p) {
      luaL_prepbuffer(&local_214);
    }
    *local_214.p = pcVar1[local_218];
    local_214.p = (char *)((int)local_214.p + 1);
  }
  local_218 = 0xffffffff;
  luaL_pushresult(&local_214);
  return 1;
}
