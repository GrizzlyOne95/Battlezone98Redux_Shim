/*
 * Entry: 004171d0
 * Name: GetOwner
 * Namespace: Global
 * Signature: int GetOwner(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl GetOwner(lua_State *param_1)

{
  int iVar1;
  
  iVar1 = GetHandle(param_1,1);
  iVar1 = GetOwner(iVar1);
  PushHandle(param_1,iVar1);
  return 1;
}
