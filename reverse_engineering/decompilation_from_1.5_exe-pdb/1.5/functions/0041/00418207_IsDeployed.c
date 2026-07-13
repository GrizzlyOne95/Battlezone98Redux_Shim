/*
 * Entry: 00418207
 * Name: IsDeployed
 * Namespace: Global
 * Signature: int IsDeployed(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl IsDeployed(lua_State *param_1)

{
  bool bVar1;
  int iVar2;
  
  iVar2 = GetHandle(param_1,1);
  bVar1 = IsDeployed(iVar2);
  lua_pushboolean(param_1,(uint)bVar1);
  return 1;
}
