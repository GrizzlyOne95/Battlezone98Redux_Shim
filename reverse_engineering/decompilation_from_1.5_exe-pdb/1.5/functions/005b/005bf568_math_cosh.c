/*
 * Entry: 005bf568
 * Name: math_cosh
 * Namespace: Global
 * Signature: int math_cosh(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl math_cosh(lua_State *param_1)

{
  float10 fVar1;
  undefined4 unaff_retaddr;
  
  luaL_checknumber(param_1,1);
  fVar1 = (float10)__CIcosh();
  lua_pushnumber(param_1,(double)CONCAT44(unaff_retaddr,(int)((ulonglong)(double)fVar1 >> 0x20)));
  return 1;
}
