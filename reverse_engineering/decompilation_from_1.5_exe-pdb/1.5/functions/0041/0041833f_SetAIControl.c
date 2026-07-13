/*
 * Entry: 0041833f
 * Name: SetAIControl
 * Namespace: Global
 * Signature: int SetAIControl(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl SetAIControl(lua_State *param_1)

{
  int iVar1;
  int iVar2;
  
  iVar1 = luaL_checkinteger(param_1,1);
  iVar2 = lua_type(param_1,2);
  if (iVar2 < 1) {
    iVar2 = 1;
  }
  else {
    iVar2 = lua_toboolean(param_1,2);
  }
  SetAIControl(iVar1,iVar2 != 0);
  return 0;
}
