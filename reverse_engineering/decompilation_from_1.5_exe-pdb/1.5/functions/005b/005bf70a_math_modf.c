/*
 * Entry: 005bf70a
 * Name: math_modf
 * Namespace: Global
 * Signature: int math_modf(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl math_modf(lua_State *param_1)

{
  double dVar1;
  double *_Y;
  undefined4 uVar2;
  undefined4 uStack_10;
  undefined8 local_c;
  
  _Y = (double *)&local_c;
  dVar1 = luaL_checknumber(param_1,1);
  dVar1 = modf(dVar1,_Y);
  uVar2 = SUB84(dVar1,0);
  uStack_10 = (undefined4)((ulonglong)dVar1 >> 0x20);
  lua_pushnumber(param_1,(double)CONCAT44(uVar2,local_c._4_4_));
  lua_pushnumber(param_1,(double)CONCAT44(uVar2,uStack_10));
  return 2;
}
