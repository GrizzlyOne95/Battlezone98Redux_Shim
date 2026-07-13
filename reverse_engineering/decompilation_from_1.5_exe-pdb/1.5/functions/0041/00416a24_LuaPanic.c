/*
 * Entry: 00416a24
 * Name: LuaPanic
 * Namespace: Global
 * Signature: int LuaPanic(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl LuaPanic(lua_State *param_1)

{
  lua_tolstring(param_1,-1,(uint *)0x0);
  DEBUG_systemError("Lua panic:\n%s");
  return 0;
}
