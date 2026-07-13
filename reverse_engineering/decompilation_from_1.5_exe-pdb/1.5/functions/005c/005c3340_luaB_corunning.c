/*
 * Entry: 005c3340
 * Name: luaB_corunning
 * Namespace: Global
 * Signature: int luaB_corunning(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl luaB_corunning(lua_State *param_1)

{
  int iVar1;
  
  iVar1 = lua_pushthread(param_1);
  if (iVar1 != 0) {
    lua_pushnil(param_1);
  }
  return 1;
}
