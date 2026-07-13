/*
 * Entry: 00418ed0
 * Name: AddAmmo
 * Namespace: Global
 * Signature: int AddAmmo(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl AddAmmo(lua_State *param_1)

{
  int iVar1;
  int iVar2;
  
  iVar1 = GetHandle(param_1,1);
  iVar2 = luaL_checkinteger(param_1,2);
  AddAmmo(iVar1,iVar2);
  return 0;
}
