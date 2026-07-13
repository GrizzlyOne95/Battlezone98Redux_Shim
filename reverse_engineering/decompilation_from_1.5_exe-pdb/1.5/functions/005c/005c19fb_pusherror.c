/*
 * Entry: 005c19fb
 * Name: pusherror
 * Namespace: Global
 * Signature: void pusherror(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __cdecl pusherror(lua_State *param_1)

{
  DWORD DVar1;
  lua_State *unaff_EDI;
  CHAR local_88 [128];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  DVar1 = GetLastError();
  DVar1 = FormatMessageA(0x1200,(LPCVOID)0x0,DVar1,0,local_88,0x80,(va_list *)0x0);
  if (DVar1 == 0) {
    lua_pushfstring(unaff_EDI,"system error %d\n");
  }
  else {
    lua_pushstring(unaff_EDI,local_88);
  }
  return;
}
