/*
 * Entry: 00417bda
 * Name: IsWithin
 * Namespace: Global
 * Signature: int IsWithin(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl IsWithin(lua_State *param_1)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  double dVar4;
  
  iVar2 = GetHandle(param_1,1);
  iVar3 = GetHandle(param_1,2);
  dVar4 = luaL_checknumber(param_1,3);
  bVar1 = IsWithin(iVar2,iVar3,(float)dVar4);
  lua_pushboolean(param_1,(uint)bVar1);
  return 1;
}
