/*
 * Entry: 00416fb7
 * Name: IsBuilding
 * Namespace: Global
 * Signature: int IsBuilding(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl IsBuilding(lua_State *param_1)

{
  bool bVar1;
  int iVar2;
  
  iVar2 = GetHandle(param_1,1);
  bVar1 = IsBuilding(iVar2);
  lua_pushboolean(param_1,(uint)bVar1);
  return 1;
}
