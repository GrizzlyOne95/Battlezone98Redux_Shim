/*
 * Entry: 0041822c
 * Name: Deploy
 * Namespace: Global
 * Signature: int Deploy(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl Deploy(lua_State *param_1)

{
  int iVar1;
  
  iVar1 = GetHandle(param_1,1);
  Deploy(iVar1);
  return 0;
}
