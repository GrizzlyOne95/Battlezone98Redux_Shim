/*
 * Entry: 005c3329
 * Name: luaB_yield
 * Namespace: Global
 * Signature: int luaB_yield(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl luaB_yield(lua_State *param_1)

{
  int iVar1;
  
  iVar1 = lua_gettop(param_1);
  iVar1 = lua_yield(param_1,iVar1);
  return iVar1;
}
