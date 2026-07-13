/*
 * Entry: 00418786
 * Name: GetCurrentWho
 * Namespace: Global
 * Signature: int GetCurrentWho(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl GetCurrentWho(lua_State *param_1)

{
  int iVar1;
  
  iVar1 = GetHandle(param_1,1);
  iVar1 = GetCurrentWho(iVar1);
  PushHandle(param_1,iVar1);
  return 1;
}
