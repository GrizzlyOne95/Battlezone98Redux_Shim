/*
 * Entry: 005bf6a7
 * Name: math_floor
 * Namespace: Global
 * Signature: int math_floor(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl math_floor(lua_State *param_1)

{
  float10 fVar1;
  double dVar2;
  undefined4 unaff_retaddr;
  
  dVar2 = luaL_checknumber(param_1,1);
  fVar1 = (float10)floor(SUB84(dVar2,0),(int)((ulonglong)dVar2 >> 0x20));
  lua_pushnumber(param_1,(double)CONCAT44(unaff_retaddr,(int)((ulonglong)(double)fVar1 >> 0x20)));
  return 1;
}
