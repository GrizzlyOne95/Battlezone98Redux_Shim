/*
 * Entry: 005c2783
 * Name: luaB_setmetatable
 * Namespace: Global
 * Signature: int luaB_setmetatable(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl luaB_setmetatable(lua_State *param_1)

{
  int iVar1;
  
  iVar1 = lua_type(param_1,2);
  luaL_checktype(param_1,1,5);
  if ((iVar1 != 0) && (iVar1 != 5)) {
    luaL_argerror(param_1,2,"nil or table expected");
  }
  iVar1 = luaL_getmetafield(param_1,1,"__metatable");
  if (iVar1 != 0) {
    luaL_error(param_1,"cannot change a protected metatable");
  }
  lua_settop(param_1,2);
  lua_setmetatable(param_1,1);
  return 1;
}
