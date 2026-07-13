/*
 * Entry: 00416f92
 * Name: IsCraft
 * Namespace: Global
 * Signature: int IsCraft(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl IsCraft(lua_State *param_1)

{
  bool bVar1;
  int iVar2;
  
  iVar2 = GetHandle(param_1,1);
  bVar1 = IsCraft(iVar2);
  lua_pushboolean(param_1,(uint)bVar1);
  return 1;
}
