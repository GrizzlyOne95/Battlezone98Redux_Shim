/*
 * Entry: 00417b04
 * Name: GetTimeStep
 * Namespace: Global
 * Signature: int GetTimeStep(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl GetTimeStep(lua_State *param_1)

{
  float fVar1;
  undefined4 unaff_retaddr;
  
  fVar1 = TimeStep();
  lua_pushnumber(param_1,(double)CONCAT44(unaff_retaddr,(int)((ulonglong)(double)fVar1 >> 0x20)));
  return 1;
}
