/*
 * Entry: 005c09cb
 * Name: gmatch
 * Namespace: Global
 * Signature: int gmatch(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl gmatch(lua_State *param_1)

{
  luaL_checklstring(param_1,1,(uint *)0x0);
  luaL_checklstring(param_1,2,(uint *)0x0);
  lua_settop(param_1,2);
  lua_pushinteger(param_1,0);
  lua_pushcclosure(param_1,gmatch_aux,3);
  return 1;
}
