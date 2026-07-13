/*
 * Entry: 005bf648
 * Name: math_atan2
 * Namespace: Global
 * Signature: int math_atan2(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl math_atan2(lua_State *param_1)

{
  undefined4 unaff_ESI;
  float10 fVar1;
  double dVar2;
  double dVar3;
  
  dVar2 = luaL_checknumber(param_1,1);
  dVar3 = luaL_checknumber(param_1,2);
  fVar1 = (float10)fpatan((float10)dVar2,(float10)dVar3);
  lua_pushnumber(param_1,(double)CONCAT44(unaff_ESI,(int)((ulonglong)(double)fVar1 >> 0x20)));
  return 1;
}
