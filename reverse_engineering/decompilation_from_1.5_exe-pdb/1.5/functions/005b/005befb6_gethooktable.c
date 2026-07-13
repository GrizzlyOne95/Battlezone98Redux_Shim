/*
 * Entry: 005befb6
 * Name: gethooktable
 * Namespace: Global
 * Signature: void gethooktable(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl gethooktable(lua_State *param_1)

{
  int iVar1;
  lua_State *unaff_ESI;
  
  lua_pushlightuserdata(unaff_ESI,"h");
  lua_rawget(unaff_ESI,-10000);
  iVar1 = lua_type(unaff_ESI,-1);
  if (iVar1 != 5) {
    lua_settop(unaff_ESI,-2);
    lua_createtable(unaff_ESI,0,1);
    lua_pushlightuserdata(unaff_ESI,"h");
    lua_pushvalue(unaff_ESI,-2);
    lua_rawset(unaff_ESI,-10000);
  }
  return;
}
