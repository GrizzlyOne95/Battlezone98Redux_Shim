/*
 * Entry: 0041c379
 * Name: MAT_3D_ToString
 * Namespace: Global
 * Signature: int MAT_3D_ToString(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

int __cdecl MAT_3D_ToString(lua_State *param_1)

{
  MAT_3D *pMVar1;
  char local_108 [256];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  pMVar1 = GetMatrix(param_1,1);
  if (pMVar1 != (MAT_3D *)0x0) {
    sprintf_s<256>(&local_108,
                   "{right_x=%f, right_y=%f, right_z=%f, up_x=%f, up_y=%f, up_z=%f, front_x=%f, front_y=%f, front_z=%f, posit_x=%f, posit_y=%f, posit_z=%f}"
                  );
    lua_pushstring(param_1,local_108);
  }
  return (uint)(pMVar1 != (MAT_3D *)0x0);
}
