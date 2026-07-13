/*
 * Entry: 00417916
 * Name: UnAlly
 * Namespace: Global
 * Signature: int UnAlly(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl UnAlly(lua_State *param_1)

{
  int iVar1;
  int iVar2;
  
  iVar1 = luaL_checkinteger(param_1,1);
  iVar2 = luaL_checkinteger(param_1,2);
  UnAlly(iVar1,iVar2);
  return 0;
}
