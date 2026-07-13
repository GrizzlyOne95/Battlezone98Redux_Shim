/*
 * Entry: 005bf8a0
 * Name: math_ldexp
 * Namespace: Global
 * Signature: int math_ldexp(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl math_ldexp(lua_State *param_1)

{
  int _Y;
  undefined4 unaff_ESI;
  double dVar1;
  
  _Y = luaL_checkinteger(param_1,2);
  dVar1 = luaL_checknumber(param_1,1);
  dVar1 = ldexp(dVar1,_Y);
  lua_pushnumber(param_1,(double)CONCAT44(unaff_ESI,(int)((ulonglong)dVar1 >> 0x20)));
  return 1;
}
