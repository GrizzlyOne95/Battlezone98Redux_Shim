/*
 * Entry: 00418e82
 * Name: SetCurAmmo
 * Namespace: Global
 * Signature: int SetCurAmmo(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl SetCurAmmo(lua_State *param_1)

{
  int iVar1;
  int iVar2;
  
  iVar1 = GetHandle(param_1,1);
  iVar2 = luaL_checkinteger(param_1,2);
  SetCurAmmo(iVar1,iVar2);
  return 0;
}
