/*
 * Entry: 005c2418
 * Name: luaopen_package
 * Namespace: Global
 * Signature: int luaopen_package(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl luaopen_package(lua_State *param_1)

{
  code *pcVar1;
  int iVar2;
  char *pcVar3;
  lua_State *plVar4;
  
  luaL_newmetatable(param_1,"_LOADLIB");
  lua_pushcclosure(param_1,gctm,0);
  lua_setfield(param_1,-2,"__gc");
  luaL_register(param_1,"package",pk_funcs);
  lua_pushvalue(param_1,-1);
  lua_replace(param_1,-0x2711);
  lua_createtable(param_1,4,0);
  iVar2 = 0;
  pcVar1 = loader_preload;
  while (pcVar1 != (_func___cdecl_int_lua_State_ptr *)0x0) {
    lua_pushcclosure(param_1,pcVar1,0);
    iVar2 = iVar2 + 1;
    lua_rawseti(param_1,-2,iVar2);
    pcVar1 = loaders[iVar2];
  }
  plVar4 = param_1;
  lua_setfield(param_1,-2,"loaders");
  pcVar3 = "path";
  setpath((lua_State *)"path","LUA_PATH",
          ".\\?.lua;!\\lua\\?.lua;!\\lua\\?\\init.lua;!\\?.lua;!\\?\\init.lua",(char *)plVar4);
  setpath((lua_State *)"cpath","LUA_CPATH",".\\?.dll;!\\?.dll;!\\loadall.dll",pcVar3);
  lua_pushlstring(param_1,"\\\n;\n?\n!\n-",9);
  lua_setfield(param_1,-2,"config");
  luaL_findtable(param_1,-10000,"_LOADED",2);
  lua_setfield(param_1,-2,"loaded");
  lua_createtable(param_1,0,0);
  lua_setfield(param_1,-2,"preload");
  lua_pushvalue(param_1,-0x2712);
  luaL_register(param_1,(char *)0x0,ll_funcs);
  lua_settop(param_1,-2);
  return 1;
}
