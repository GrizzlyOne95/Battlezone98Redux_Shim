/*
 * Entry: 00417a3d
 * Name: SetObjectiveOn
 * Namespace: Global
 * Signature: int SetObjectiveOn(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl SetObjectiveOn(lua_State *param_1)

{
  int iVar1;
  
  iVar1 = GetHandle(param_1,1);
  SetObjectiveOn(iVar1);
  return 0;
}
