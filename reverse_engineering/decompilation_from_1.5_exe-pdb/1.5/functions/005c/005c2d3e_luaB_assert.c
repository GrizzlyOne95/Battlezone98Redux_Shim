/*
 * Entry: 005c2d3e
 * Name: luaB_assert
 * Namespace: Global
 * Signature: int luaB_assert(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl luaB_assert(lua_State *param_1)

{
  int iVar1;
  
  luaL_checkany(param_1,1);
  iVar1 = lua_toboolean(param_1,1);
  if (iVar1 == 0) {
    luaL_optlstring(param_1,2,"assertion failed!",(uint *)0x0);
    iVar1 = luaL_error(param_1,"%s");
    return iVar1;
  }
  iVar1 = lua_gettop(param_1);
  return iVar1;
}
