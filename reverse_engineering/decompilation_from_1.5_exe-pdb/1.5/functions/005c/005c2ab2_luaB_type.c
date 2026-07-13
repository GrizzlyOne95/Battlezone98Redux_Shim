/*
 * Entry: 005c2ab2
 * Name: luaB_type
 * Namespace: Global
 * Signature: int luaB_type(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl luaB_type(lua_State *param_1)

{
  int iVar1;
  char *pcVar2;
  
  luaL_checkany(param_1,1);
  iVar1 = lua_type(param_1,1);
  pcVar2 = lua_typename(param_1,iVar1);
  lua_pushstring(param_1,pcVar2);
  return 1;
}
