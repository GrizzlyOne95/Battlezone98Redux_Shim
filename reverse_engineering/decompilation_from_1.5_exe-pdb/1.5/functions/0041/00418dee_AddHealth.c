/*
 * Entry: 00418dee
 * Name: AddHealth
 * Namespace: Global
 * Signature: int AddHealth(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl AddHealth(lua_State *param_1)

{
  int iVar1;
  double dVar2;
  
  iVar1 = GetHandle(param_1,1);
  dVar2 = luaL_checknumber(param_1,2);
  AddHealth(iVar1,(float)dVar2);
  return 0;
}
