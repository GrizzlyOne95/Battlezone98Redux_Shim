/*
 * Entry: 005c2f11
 * Name: luaB_tostring
 * Namespace: Global
 * Signature: int luaB_tostring(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl luaB_tostring(lua_State *param_1)

{
  int iVar1;
  char *pcVar2;
  
  luaL_checkany(param_1,1);
  iVar1 = luaL_callmeta(param_1,1,"__tostring");
  if (iVar1 == 0) {
    iVar1 = lua_type(param_1,1);
    if (iVar1 == 0) {
      lua_pushlstring(param_1,"nil",3);
    }
    else if (iVar1 == 1) {
      iVar1 = lua_toboolean(param_1,1);
      pcVar2 = "true";
      if (iVar1 == 0) {
        pcVar2 = "false";
      }
      lua_pushstring(param_1,pcVar2);
    }
    else if (iVar1 == 3) {
      pcVar2 = lua_tolstring(param_1,1,(uint *)0x0);
      lua_pushstring(param_1,pcVar2);
    }
    else if (iVar1 == 4) {
      lua_pushvalue(param_1,1);
    }
    else {
      lua_topointer(param_1,1);
      iVar1 = lua_type(param_1,1);
      lua_typename(param_1,iVar1);
      lua_pushfstring(param_1,"%s: %p");
    }
  }
  return 1;
}
