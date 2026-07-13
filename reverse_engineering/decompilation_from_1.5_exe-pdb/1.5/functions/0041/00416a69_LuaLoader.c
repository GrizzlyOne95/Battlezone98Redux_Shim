/*
 * Entry: 00416a69
 * Name: LuaLoader
 * Namespace: Global
 * Signature: int LuaLoader(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

int __cdecl LuaLoader(lua_State *param_1)

{
  char *pcVar1;
  int iVar2;
  uint uVar3;
  char *pcVar4;
  char local_118 [256];
  char local_18 [16];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  pcVar1 = lua_tolstring(param_1,-1,(uint *)0x0);
  local_18[0] = '\0';
  local_18[1] = '\0';
  local_18[2] = '\0';
  local_18[3] = '\0';
  local_18[4] = '\0';
  local_18[5] = '\0';
  local_18[6] = '\0';
  local_18[7] = '\0';
  local_18[8] = '\0';
  local_18[9] = '\0';
  local_18[10] = '\0';
  local_18[0xb] = '\0';
  local_18[0xc] = '\0';
  local_18[0xd] = '\0';
  local_18[0xe] = '\0';
  local_18[0xf] = '\0';
  sprintf(local_18,"%.11s.lua",pcVar1);
  iVar2 = ItemExists(local_18);
  if (iVar2 == 0) {
    _snprintf(local_118,0x100,"\n\tno asset \'%s\'");
    lua_pushstring(param_1,local_118);
  }
  else {
    pcVar1 = UseItem(local_18);
    uVar3 = GetItemSize(local_18);
    pcVar4 = "Lua package load error:\n%s";
    iVar2 = luaL_loadbuffer(param_1,pcVar1,uVar3,local_18);
    LuaCheckStatus(iVar2,param_1,pcVar4);
    UnlockItem(local_18);
  }
  return 1;
}
