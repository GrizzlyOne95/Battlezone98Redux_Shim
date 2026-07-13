/*
 * Entry: 005bfee1
 * Name: str_char
 * Namespace: Global
 * Signature: int str_char(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

int __cdecl str_char(lua_State *param_1)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  luaL_Buffer local_214;
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)(local_214.buffer + 0x70);
  iVar1 = lua_gettop(param_1);
  luaL_buffinit(param_1,&local_214);
  iVar3 = 1;
  if (0 < iVar1) {
    do {
      uVar2 = luaL_checkinteger(param_1,iVar3);
      if ((uVar2 & 0xff) != uVar2) {
        luaL_argerror(param_1,iVar3,"invalid value");
      }
      if (&local_8 <= local_214.p) {
        luaL_prepbuffer(&local_214);
      }
      *local_214.p = (char)uVar2;
      local_214.p = (char *)((int)local_214.p + 1);
      iVar3 = iVar3 + 1;
    } while (iVar3 <= iVar1);
  }
  luaL_pushresult(&local_214);
  return 1;
}
