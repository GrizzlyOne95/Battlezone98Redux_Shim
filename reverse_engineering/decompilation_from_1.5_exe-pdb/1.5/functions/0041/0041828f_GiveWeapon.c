/*
 * Entry: 0041828f
 * Name: GiveWeapon
 * Namespace: Global
 * Signature: int GiveWeapon(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl GiveWeapon(lua_State *param_1)

{
  bool bVar1;
  int iVar2;
  char *pcVar3;
  int iVar4;
  
  iVar2 = GetHandle(param_1,1);
  pcVar3 = luaL_optlstring(param_1,2,(char *)0x0,(uint *)0x0);
  iVar4 = luaL_optinteger(param_1,3,-1);
  if (iVar4 < 0) {
    bVar1 = GiveWeapon(iVar2,pcVar3);
    lua_pushboolean(param_1,(uint)bVar1);
  }
  else {
    bVar1 = GiveWeapon(iVar2,pcVar3,iVar4);
    lua_pushboolean(param_1,(uint)bVar1);
  }
  return 1;
}
