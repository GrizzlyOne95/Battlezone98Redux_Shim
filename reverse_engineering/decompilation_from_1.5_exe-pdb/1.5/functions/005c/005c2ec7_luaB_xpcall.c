/*
 * Entry: 005c2ec7
 * Name: luaB_xpcall
 * Namespace: Global
 * Signature: int luaB_xpcall(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl luaB_xpcall(lua_State *param_1)

{
  int iVar1;
  
  luaL_checkany(param_1,2);
  lua_settop(param_1,2);
  lua_insert(param_1,1);
  iVar1 = lua_pcall(param_1,0,-1,1);
  lua_pushboolean(param_1,(uint)(iVar1 == 0));
  lua_replace(param_1,1);
  iVar1 = lua_gettop(param_1);
  return iVar1;
}
