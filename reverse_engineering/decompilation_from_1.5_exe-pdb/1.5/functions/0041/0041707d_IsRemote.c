/*
 * Entry: 0041707d
 * Name: IsRemote
 * Namespace: Global
 * Signature: int IsRemote(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl IsRemote(lua_State *param_1)

{
  bool bVar1;
  int iVar2;
  
  iVar2 = GetHandle(param_1,1);
  bVar1 = IsRemote(iVar2);
  lua_pushboolean(param_1,(uint)bVar1);
  return 1;
}
