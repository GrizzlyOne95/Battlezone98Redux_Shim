/*
 * Entry: 00418e3e
 * Name: GetCurAmmo
 * Namespace: Global
 * Signature: int GetCurAmmo(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl GetCurAmmo(lua_State *param_1)

{
  int iVar1;
  long lVar2;
  
  iVar1 = GetHandle(param_1,1);
  lVar2 = GetCurAmmo(iVar1);
  lua_pushinteger(param_1,lVar2);
  return 1;
}
