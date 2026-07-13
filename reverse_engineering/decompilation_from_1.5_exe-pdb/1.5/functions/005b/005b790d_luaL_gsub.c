/*
 * Entry: 005b790d
 * Name: luaL_gsub
 * Namespace: Global
 * Signature: char * luaL_gsub(lua_State * param_1, char * param_2, char * param_3, char * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

char * __cdecl luaL_gsub(lua_State *param_1,char *param_2,char *param_3,char *param_4)

{
  char cVar1;
  char *pcVar2;
  char *pcVar3;
  luaL_Buffer local_214;
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)(local_214.buffer + 100);
  pcVar2 = param_3;
  do {
    cVar1 = *pcVar2;
    pcVar2 = pcVar2 + 1;
  } while (cVar1 != '\0');
  local_214.lvl = 0;
  local_214.L = param_1;
  local_214.p = local_214.buffer;
  pcVar3 = strstr(param_2,param_3);
  while (pcVar3 != (char *)0x0) {
    luaL_addlstring(&local_214,param_2,(int)pcVar3 - (int)param_2);
    luaL_addstring(&local_214,param_4);
    param_2 = pcVar3 + ((int)pcVar2 - (int)(param_3 + 1));
    pcVar3 = strstr(param_2,param_3);
  }
  luaL_addstring(&local_214,param_2);
  luaL_pushresult(&local_214);
  pcVar2 = lua_tolstring(param_1,-1,(uint *)0x0);
  return pcVar2;
}
