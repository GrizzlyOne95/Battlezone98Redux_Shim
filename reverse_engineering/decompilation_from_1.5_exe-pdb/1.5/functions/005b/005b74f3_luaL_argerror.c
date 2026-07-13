/*
 * Entry: 005b74f3
 * Name: luaL_argerror
 * Namespace: Global
 * Signature: int luaL_argerror(lua_State * param_1, int param_2, char * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

int __cdecl luaL_argerror(lua_State *param_1,int param_2,char *param_3)

{
  int iVar1;
  bool bVar2;
  char *pcVar3;
  lua_Debug local_6c;
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  iVar1 = lua_getstack(param_1,0,&local_6c);
  if (iVar1 == 0) {
    pcVar3 = "bad argument #%d (%s)";
LAB_005b752a:
    iVar1 = luaL_error(param_1,pcVar3);
  }
  else {
    lua_getinfo(param_1,"n",&local_6c);
    iVar1 = 7;
    bVar2 = true;
    pcVar3 = "method";
    do {
      if (iVar1 == 0) break;
      iVar1 = iVar1 + -1;
      bVar2 = *local_6c.namewhat == *pcVar3;
      local_6c.namewhat = local_6c.namewhat + 1;
      pcVar3 = pcVar3 + 1;
    } while (bVar2);
    if (bVar2) {
      if (param_2 == 1) {
        pcVar3 = "calling \'%s\' on bad self (%s)";
        goto LAB_005b752a;
      }
    }
    if (local_6c.name == (char *)0x0) {
      local_6c.name = "?";
    }
    iVar1 = luaL_error(param_1,"bad argument #%d to \'%s\' (%s)");
  }
  return iVar1;
}
