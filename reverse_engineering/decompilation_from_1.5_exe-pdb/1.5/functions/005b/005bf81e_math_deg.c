/*
 * Entry: 005bf81e
 * Name: math_deg
 * Namespace: Global
 * Signature: int math_deg(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl math_deg(lua_State *param_1)

{
  double dVar1;
  undefined4 unaff_retaddr;
  
  dVar1 = luaL_checknumber(param_1,1);
  lua_pushnumber(param_1,(double)CONCAT44(unaff_retaddr,
                                          (int)((ulonglong)(dVar1 * 57.29577951308232) >> 0x20)));
  return 1;
}
