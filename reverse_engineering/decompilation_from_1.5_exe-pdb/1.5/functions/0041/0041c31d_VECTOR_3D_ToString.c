/*
 * Entry: 0041c31d
 * Name: VECTOR_3D_ToString
 * Namespace: Global
 * Signature: int VECTOR_3D_ToString(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

int __cdecl VECTOR_3D_ToString(lua_State *param_1)

{
  char local_48 [64];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  RequireVector(param_1,1);
  sprintf_s<64>(&local_48,"{x=%f, y=%f, z=%f}");
  lua_pushstring(param_1,local_48);
  return 1;
}
