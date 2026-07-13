/*
 * Entry: 004179a2
 * Name: IsAlly
 * Namespace: Global
 * Signature: int IsAlly(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl IsAlly(lua_State *param_1)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  
  iVar2 = GetHandle(param_1,1);
  iVar3 = GetHandle(param_1,2);
  bVar1 = IsAlly(iVar2,iVar3);
  lua_pushboolean(param_1,(uint)bVar1);
  return 1;
}
