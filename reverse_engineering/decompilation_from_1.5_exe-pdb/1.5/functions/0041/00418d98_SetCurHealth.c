/*
 * Entry: 00418d98
 * Name: SetCurHealth
 * Namespace: Global
 * Signature: int SetCurHealth(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl SetCurHealth(lua_State *param_1)

{
  int iVar1;
  double dVar2;
  
  iVar1 = GetHandle(param_1,1);
  dVar2 = luaL_checknumber(param_1,2);
  SetCurHealth(iVar1,(float)dVar2);
  return 0;
}
