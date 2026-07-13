/*
 * Entry: 005bf7d3
 * Name: math_log10
 * Namespace: Global
 * Signature: int math_log10(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl math_log10(lua_State *param_1)

{
  double dVar1;
  undefined4 unaff_retaddr;
  
  dVar1 = luaL_checknumber(param_1,1);
  lua_pushnumber(param_1,(double)CONCAT44(unaff_retaddr,
                                          (int)((ulonglong)(dVar1 * 0.3010299956639812) >> 0x20)));
  return 1;
}
