/*
 * Entry: 00417160
 * Name: SetTarget
 * Namespace: Global
 * Signature: int SetTarget(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl SetTarget(lua_State *param_1)

{
  int iVar1;
  int iVar2;
  
  iVar1 = GetHandle(param_1,1);
  iVar2 = GetHandle(param_1,2);
  SetTarget(iVar1,iVar2);
  return 0;
}
