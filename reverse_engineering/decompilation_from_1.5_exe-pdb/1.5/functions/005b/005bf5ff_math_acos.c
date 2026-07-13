/*
 * Entry: 005bf5ff
 * Name: math_acos
 * Namespace: Global
 * Signature: int math_acos(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl math_acos(lua_State *param_1)

{
  float10 fVar1;
  undefined4 unaff_retaddr;
  
  luaL_checknumber(param_1,1);
  fVar1 = (float10)__CIacos();
  lua_pushnumber(param_1,(double)CONCAT44(unaff_retaddr,(int)((ulonglong)(double)fVar1 >> 0x20)));
  return 1;
}
