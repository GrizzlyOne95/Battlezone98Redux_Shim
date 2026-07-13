/*
 * Entry: 005b7101
 * Name: luaL_ref
 * Namespace: Global
 * Signature: int luaL_ref(lua_State * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl luaL_ref(lua_State *param_1,int param_2)

{
  int iVar1;
  uint uVar2;
  
  if (param_2 + 9999U < 10000) {
    iVar1 = lua_gettop(param_1);
    param_2 = param_2 + 1 + iVar1;
  }
  iVar1 = lua_type(param_1,-1);
  if (iVar1 == 0) {
    lua_settop(param_1,-2);
    iVar1 = -1;
  }
  else {
    lua_rawgeti(param_1,param_2,0);
    iVar1 = lua_tointeger(param_1,-1);
    lua_settop(param_1,-2);
    if (iVar1 == 0) {
      uVar2 = lua_objlen(param_1,param_2);
      iVar1 = uVar2 + 1;
    }
    else {
      lua_rawgeti(param_1,param_2,iVar1);
      lua_rawseti(param_1,param_2,0);
    }
    lua_rawseti(param_1,param_2,iVar1);
  }
  return iVar1;
}
