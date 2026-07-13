/*
 * Entry: 005bf866
 * Name: math_frexp
 * Namespace: Global
 * Signature: int math_frexp(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl math_frexp(lua_State *param_1)

{
  double dVar1;
  int *_Y;
  int extraout_var;
  int iVar2;
  
  _Y = (int *)&stack0xfffffff8;
  dVar1 = luaL_checknumber(param_1,1);
  iVar2 = extraout_var;
  dVar1 = frexp(dVar1,_Y);
  lua_pushnumber(param_1,(double)CONCAT44(iVar2,(int)((ulonglong)dVar1 >> 0x20)));
  lua_pushinteger(param_1,iVar2);
  return 2;
}
