/*
 * Entry: 005c338b
 * Name: base_open
 * Namespace: Global
 * Signature: void base_open(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl base_open(lua_State *param_1)

{
  lua_State *unaff_ESI;
  
  lua_pushvalue(unaff_ESI,-0x2712);
  lua_setfield(unaff_ESI,-0x2712,"_G");
  luaL_register(unaff_ESI,"_G",base_funcs);
  lua_pushlstring(unaff_ESI,"Lua 5.1",7);
  lua_setfield(unaff_ESI,-0x2712,"_VERSION");
  auxopen(unaff_ESI,"ipairs",luaB_ipairs,ipairsaux);
  auxopen(unaff_ESI,"pairs",luaB_pairs,luaB_next);
  lua_createtable(unaff_ESI,0,1);
  lua_pushvalue(unaff_ESI,-1);
  lua_setmetatable(unaff_ESI,-2);
  lua_pushlstring(unaff_ESI,"kv",2);
  lua_setfield(unaff_ESI,-2,"__mode");
  lua_pushcclosure(unaff_ESI,luaB_newproxy,1);
  lua_setfield(unaff_ESI,-0x2712,"newproxy");
  return;
}
