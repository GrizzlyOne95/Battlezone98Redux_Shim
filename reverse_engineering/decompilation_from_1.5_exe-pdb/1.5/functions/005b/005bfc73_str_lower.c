/*
 * Entry: 005bfc73
 * Name: str_lower
 * Namespace: Global
 * Signature: int str_lower(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

int __cdecl str_lower(lua_State *param_1)

{
  char *pcVar1;
  int iVar2;
  uint uVar3;
  uint local_218;
  luaL_Buffer local_214;
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)(local_214.buffer + 0x70);
  pcVar1 = luaL_checklstring(param_1,1,&local_218);
  luaL_buffinit(param_1,&local_214);
  uVar3 = 0;
  if (local_218 != 0) {
    do {
      if (&local_8 <= local_214.p) {
        luaL_prepbuffer(&local_214);
      }
      iVar2 = tolower((uint)(byte)pcVar1[uVar3]);
      *local_214.p = (char)iVar2;
      local_214.p = (char *)((int)local_214.p + 1);
      uVar3 = uVar3 + 1;
    } while (uVar3 < local_218);
  }
  luaL_pushresult(&local_214);
  return 1;
}
