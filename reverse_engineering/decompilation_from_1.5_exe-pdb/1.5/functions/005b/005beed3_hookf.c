/*
 * Entry: 005beed3
 * Name: hookf
 * Namespace: Global
 * Signature: void hookf(lua_State * param_1, lua_Debug * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl hookf(lua_State *param_1,lua_Debug *param_2)

{
  int iVar1;
  
  lua_pushlightuserdata(param_1,"h");
  lua_rawget(param_1,-10000);
  lua_pushlightuserdata(param_1,param_1);
  lua_rawget(param_1,-2);
  iVar1 = lua_type(param_1,-1);
  if (iVar1 == 6) {
    lua_pushstring(param_1,hooknames[param_2->event]);
    if (param_2->currentline < 0) {
      lua_pushnil(param_1);
    }
    else {
      lua_pushinteger(param_1,param_2->currentline);
    }
    lua_call(param_1,2,0);
  }
  return;
}
