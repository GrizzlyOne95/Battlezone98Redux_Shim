/*
 * Entry: 00417842
 * Name: GetWhoShotMe
 * Namespace: Global
 * Signature: int GetWhoShotMe(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl GetWhoShotMe(lua_State *param_1)

{
  int iVar1;
  
  iVar1 = GetHandle(param_1,1);
  iVar1 = GetWhoShotMe(iVar1);
  PushHandle(param_1,iVar1);
  return 1;
}
