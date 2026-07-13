/*
 * Entry: 005c2976
 * Name: luaB_rawequal
 * Namespace: Global
 * Signature: int luaB_rawequal(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl luaB_rawequal(lua_State *param_1)

{
  int iVar1;
  
  luaL_checkany(param_1,1);
  luaL_checkany(param_1,2);
  iVar1 = lua_rawequal(param_1,1,2);
  lua_pushboolean(param_1,iVar1);
  return 1;
}
