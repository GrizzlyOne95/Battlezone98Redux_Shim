/*
 * Entry: 00416948
 * Name: LuaOutput
 * Namespace: Global
 * Signature: int LuaOutput(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl LuaOutput(lua_State *param_1)

{
  lua_State *unaff_ESI;
  int iVar1;
  uint local_10;
  char *local_c;
  int local_8;
  
  local_8 = lua_gettop(unaff_ESI);
  lua_getfield(unaff_ESI,-0x2712,"tostring");
  iVar1 = 1;
  if (0 < local_8) {
    do {
      lua_pushvalue(unaff_ESI,-1);
      lua_pushvalue(unaff_ESI,iVar1);
      lua_call(unaff_ESI,1,1);
      local_c = lua_tolstring(unaff_ESI,-1,&local_10);
      if (local_c == (char *)0x0) {
        iVar1 = luaL_error(unaff_ESI,"\'tostring\' must return a string to \'print\'");
        return iVar1;
      }
      if (1 < iVar1) {
        DebugPrint("\t");
      }
      DebugPrint("%s");
      lua_settop(unaff_ESI,-2);
      iVar1 = iVar1 + 1;
    } while (iVar1 <= local_8);
  }
  DebugPrint("\n");
  return 0;
}
