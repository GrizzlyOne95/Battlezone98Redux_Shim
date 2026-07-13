/*
 * Entry: 005bf548
 * Name: math_cos
 * Namespace: Global
 * Signature: int math_cos(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl math_cos(lua_State *param_1)

{
  float10 fVar1;
  double dVar2;
  undefined4 unaff_retaddr;
  
  dVar2 = luaL_checknumber(param_1,1);
  fVar1 = (float10)fcos((float10)dVar2);
  lua_pushnumber(param_1,(double)CONCAT44(unaff_retaddr,(int)((ulonglong)(double)fVar1 >> 0x20)));
  return 1;
}
