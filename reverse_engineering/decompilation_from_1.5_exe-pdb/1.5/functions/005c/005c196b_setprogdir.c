/*
 * Entry: 005c196b
 * Name: setprogdir
 * Namespace: Global
 * Signature: void setprogdir(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __cdecl setprogdir(lua_State *param_1)

{
  DWORD DVar1;
  char *pcVar2;
  lua_State *unaff_EDI;
  char *pcVar3;
  CHAR *pCVar4;
  CHAR local_110 [264];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  DVar1 = GetModuleFileNameA((HMODULE)0x0,local_110,0x105);
  if (((DVar1 != 0) && (DVar1 != 0x105)) &&
     (pcVar2 = strrchr(local_110,0x5c), pcVar2 != (char *)0x0)) {
    *pcVar2 = '\0';
    pCVar4 = local_110;
    pcVar3 = "!";
    pcVar2 = lua_tolstring(unaff_EDI,-1,(uint *)0x0);
    luaL_gsub(unaff_EDI,pcVar2,pcVar3,pCVar4);
    lua_remove(unaff_EDI,-2);
    return;
  }
  luaL_error(unaff_EDI,"unable to get ModuleFileName");
  return;
}
