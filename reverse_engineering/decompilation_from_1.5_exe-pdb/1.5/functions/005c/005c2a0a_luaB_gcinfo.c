/*
 * Entry: 005c2a0a
 * Name: luaB_gcinfo
 * Namespace: Global
 * Signature: int luaB_gcinfo(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl luaB_gcinfo(lua_State *param_1)

{
  int iVar1;
  
  iVar1 = lua_gc(param_1,3,0);
  lua_pushinteger(param_1,iVar1);
  return 1;
}
