/*
 * Entry: 00417001
 * Name: IsDamaged
 * Namespace: Global
 * Signature: int IsDamaged(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl IsDamaged(lua_State *param_1)

{
  bool bVar1;
  int iVar2;
  double dVar3;
  
  iVar2 = GetHandle(param_1,1);
  dVar3 = luaL_optnumber(param_1,2,0.949999988079071);
  bVar1 = IsDamaged(iVar2,(float)dVar3);
  lua_pushboolean(param_1,(uint)bVar1);
  return 1;
}
