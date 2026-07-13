/*
 * Entry: 00417abf
 * Name: GetTime
 * Namespace: Global
 * Signature: int GetTime(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl GetTime(lua_State *param_1)

{
  float fVar1;
  undefined4 unaff_retaddr;
  
  fVar1 = Get_Time();
  lua_pushnumber(param_1,(double)CONCAT44(unaff_retaddr,(int)((ulonglong)(double)fVar1 >> 0x20)));
  return 1;
}
