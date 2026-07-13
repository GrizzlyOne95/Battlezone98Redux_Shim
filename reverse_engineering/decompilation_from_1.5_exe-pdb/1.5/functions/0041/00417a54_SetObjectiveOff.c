/*
 * Entry: 00417a54
 * Name: SetObjectiveOff
 * Namespace: Global
 * Signature: int SetObjectiveOff(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl SetObjectiveOff(lua_State *param_1)

{
  int iVar1;
  
  iVar1 = GetHandle(param_1,1);
  SetObjectiveOff(iVar1);
  return 0;
}
