/*
 * Entry: 005c2fcf
 * Name: luaB_newproxy
 * Namespace: Global
 * Signature: int luaB_newproxy(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl luaB_newproxy(lua_State *param_1)

{
  int iVar1;
  
  lua_settop(param_1,1);
  lua_newuserdata(param_1,0);
  iVar1 = lua_toboolean(param_1,1);
  if (iVar1 == 0) {
    return 1;
  }
  iVar1 = lua_type(param_1,1);
  if (iVar1 == 1) {
    lua_createtable(param_1,0,0);
    lua_pushvalue(param_1,-1);
    lua_pushboolean(param_1,1);
    lua_rawset(param_1,-0x2713);
    goto LAB_005c307a;
  }
  iVar1 = lua_getmetatable(param_1,1);
  if (iVar1 == 0) {
LAB_005c3062:
    luaL_argerror(param_1,1,"boolean or proxy expected");
  }
  else {
    lua_rawget(param_1,-0x2713);
    iVar1 = lua_toboolean(param_1,-1);
    lua_settop(param_1,-2);
    if (iVar1 == 0) goto LAB_005c3062;
  }
  lua_getmetatable(param_1,1);
LAB_005c307a:
  lua_setmetatable(param_1,2);
  return 1;
}
