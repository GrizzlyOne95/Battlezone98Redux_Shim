/*
 * Entry: 005c2749
 * Name: luaB_getmetatable
 * Namespace: Global
 * Signature: int luaB_getmetatable(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl luaB_getmetatable(lua_State *param_1)

{
  int iVar1;
  
  luaL_checkany(param_1,1);
  iVar1 = lua_getmetatable(param_1,1);
  if (iVar1 == 0) {
    lua_pushnil(param_1);
  }
  else {
    luaL_getmetafield(param_1,1,"__metatable");
  }
  return 1;
}
