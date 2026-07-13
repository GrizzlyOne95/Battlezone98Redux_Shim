/*
 * Entry: 0041c2d5
 * Name: Handle_ToString
 * Namespace: Global
 * Signature: int Handle_ToString(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

int __cdecl Handle_ToString(lua_State *param_1)

{
  char local_18 [16];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  GetHandle(param_1,1);
  sprintf_s<16>(&local_18,"%08X");
  lua_pushstring(param_1,local_18);
  return 1;
}
