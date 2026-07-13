/*
 * Entry: 0041714b
 * Name: GetUserTarget
 * Namespace: Global
 * Signature: int GetUserTarget(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl GetUserTarget(lua_State *param_1)

{
  int iVar1;
  
  iVar1 = GetUserTarget();
  PushHandle(param_1,iVar1);
  return 1;
}
