/*
 * Entry: 005be9a4
 * Name: db_setmetatable
 * Namespace: Global
 * Signature: int db_setmetatable(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl db_setmetatable(lua_State *param_1)

{
  int iVar1;
  
  iVar1 = lua_type(param_1,2);
  if ((iVar1 != 0) && (iVar1 != 5)) {
    luaL_argerror(param_1,2,"nil or table expected");
  }
  lua_settop(param_1,2);
  iVar1 = lua_setmetatable(param_1,1);
  lua_pushboolean(param_1,iVar1);
  return 1;
}
