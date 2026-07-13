/*
 * Entry: 00416ed4
 * Name: IsOdf
 * Namespace: Global
 * Signature: int IsOdf(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl IsOdf(lua_State *param_1)

{
  bool bVar1;
  int iVar2;
  char *pcVar3;
  
  iVar2 = GetHandle(param_1,1);
  pcVar3 = luaL_checklstring(param_1,2,(uint *)0x0);
  bVar1 = IsOdf(iVar2,pcVar3);
  lua_pushboolean(param_1,(uint)bVar1);
  return 1;
}
