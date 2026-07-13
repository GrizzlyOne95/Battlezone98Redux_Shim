/*
 * Entry: 005c1fc1
 * Name: ll_require
 * Namespace: Global
 * Signature: int ll_require(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl ll_require(lua_State *param_1)

{
  char *pcVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  
  iVar4 = 1;
  pcVar1 = luaL_checklstring(param_1,1,(uint *)0x0);
  lua_settop(param_1,1);
  lua_getfield(param_1,-10000,"_LOADED");
  lua_getfield(param_1,2,pcVar1);
  iVar2 = lua_toboolean(param_1,-1);
  if (iVar2 == 0) {
    lua_getfield(param_1,-0x2711,"loaders");
    iVar2 = lua_type(param_1,-1);
    if (iVar2 != 5) {
      luaL_error(param_1,"\'package.loaders\' must be a table");
    }
    lua_pushlstring(param_1,"",0);
    while( true ) {
      lua_rawgeti(param_1,-2,iVar4);
      iVar2 = lua_type(param_1,-1);
      if (iVar2 == 0) {
        lua_tolstring(param_1,-2,(uint *)0x0);
        luaL_error(param_1,"module \'%s\' not found:%s");
      }
      lua_pushstring(param_1,pcVar1);
      lua_call(param_1,1,1);
      iVar2 = lua_type(param_1,-1);
      if (iVar2 == 6) break;
      iVar2 = lua_isstring(param_1,-1);
      if (iVar2 == 0) {
        lua_settop(param_1,-2);
      }
      else {
        lua_concat(param_1,2);
      }
      iVar4 = iVar4 + 1;
    }
    lua_pushlightuserdata(param_1,&sentinel_);
    lua_setfield(param_1,2,pcVar1);
    lua_pushstring(param_1,pcVar1);
    lua_call(param_1,1,1);
    iVar2 = lua_type(param_1,-1);
    if (iVar2 != 0) {
      lua_setfield(param_1,2,pcVar1);
    }
    lua_getfield(param_1,2,pcVar1);
    piVar3 = lua_touserdata(param_1,-1);
    if (piVar3 == &sentinel_) {
      lua_pushboolean(param_1,1);
      lua_pushvalue(param_1,-1);
      lua_setfield(param_1,2,pcVar1);
    }
  }
  else {
    piVar3 = lua_touserdata(param_1,-1);
    if (piVar3 == &sentinel_) {
      luaL_error(param_1,"loop or previous error loading module \'%s\'");
    }
  }
  return 1;
}
