/*
 * Entry: 004178d5
 * Name: Ally
 * Namespace: Global
 * Signature: int Ally(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl Ally(lua_State *param_1)

{
  int iVar1;
  int iVar2;
  
  iVar1 = luaL_checkinteger(param_1,1);
  iVar2 = luaL_checkinteger(param_1,2);
  Ally(iVar1,iVar2);
  return 0;
}
