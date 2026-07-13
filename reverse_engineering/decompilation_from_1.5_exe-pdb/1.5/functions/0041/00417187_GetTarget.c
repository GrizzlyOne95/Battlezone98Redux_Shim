/*
 * Entry: 00417187
 * Name: GetTarget
 * Namespace: Global
 * Signature: int GetTarget(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl GetTarget(lua_State *param_1)

{
  int iVar1;
  
  iVar1 = GetHandle(param_1,1);
  iVar1 = GetTarget(iVar1);
  PushHandle(param_1,iVar1);
  return 1;
}
