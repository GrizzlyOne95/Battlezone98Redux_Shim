/*
 * Entry: 005c11d9
 * Name: luaopen_string
 * Namespace: Global
 * Signature: int luaopen_string(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl luaopen_string(lua_State *param_1)

{
  luaL_register(param_1,"string",strlib);
  lua_getfield(param_1,-1,"gmatch");
  lua_setfield(param_1,-2,"gfind");
  lua_createtable(param_1,0,1);
  lua_pushlstring(param_1,"",0);
  lua_pushvalue(param_1,-2);
  lua_setmetatable(param_1,-2);
  lua_settop(param_1,-2);
  lua_pushvalue(param_1,-2);
  lua_setfield(param_1,-2,"__index");
  lua_settop(param_1,-2);
  return 1;
}
