/*
 * Entry: 005bf6cd
 * Name: math_fmod
 * Namespace: Global
 * Signature: int math_fmod(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl math_fmod(lua_State *param_1)

{
  undefined4 unaff_ESI;
  float10 fVar1;
  
  luaL_checknumber(param_1,1);
  luaL_checknumber(param_1,2);
  fVar1 = (float10)__CIfmod();
  lua_pushnumber(param_1,(double)CONCAT44(unaff_ESI,(int)((ulonglong)(double)fVar1 >> 0x20)));
  return 1;
}
