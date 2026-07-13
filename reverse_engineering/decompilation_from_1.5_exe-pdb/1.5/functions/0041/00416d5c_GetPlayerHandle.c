/*
 * Entry: 00416d5c
 * Name: GetPlayerHandle
 * Namespace: Global
 * Signature: int GetPlayerHandle(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl GetPlayerHandle(lua_State *param_1)

{
  int iVar1;
  
  iVar1 = lua_isnumber(param_1,1);
  if (iVar1 == 0) {
    iVar1 = GetPlayerHandle();
  }
  else {
    iVar1 = lua_tointeger(param_1,1);
    iVar1 = GetPlayerHandle(iVar1);
  }
  PushHandle(param_1,iVar1);
  return 1;
}
