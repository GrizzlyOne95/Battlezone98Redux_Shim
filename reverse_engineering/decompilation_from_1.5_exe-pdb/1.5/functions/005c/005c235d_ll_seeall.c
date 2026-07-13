/*
 * Entry: 005c235d
 * Name: ll_seeall
 * Namespace: Global
 * Signature: int ll_seeall(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl ll_seeall(lua_State *param_1)

{
  int iVar1;
  
  luaL_checktype(param_1,1,5);
  iVar1 = lua_getmetatable(param_1,1);
  if (iVar1 == 0) {
    lua_createtable(param_1,0,1);
    lua_pushvalue(param_1,-1);
    lua_setmetatable(param_1,1);
  }
  lua_pushvalue(param_1,-0x2712);
  lua_setfield(param_1,-2,"__index");
  return 0;
}
