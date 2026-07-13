/*
 * Entry: 005bf5d8
 * Name: math_asin
 * Namespace: Global
 * Signature: int math_asin(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl math_asin(lua_State *param_1)

{
  float10 fVar1;
  undefined4 unaff_retaddr;
  
  luaL_checknumber(param_1,1);
  fVar1 = (float10)__CIasin();
  lua_pushnumber(param_1,(double)CONCAT44(unaff_retaddr,(int)((ulonglong)(double)fVar1 >> 0x20)));
  return 1;
}
