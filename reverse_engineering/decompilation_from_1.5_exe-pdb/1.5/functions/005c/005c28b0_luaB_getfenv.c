/*
 * Entry: 005c28b0
 * Name: luaB_getfenv
 * Namespace: Global
 * Signature: int luaB_getfenv(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl luaB_getfenv(lua_State *param_1)

{
  int iVar1;
  int unaff_ESI;
  
  getfunc((lua_State *)0x1,unaff_ESI);
  iVar1 = lua_iscfunction(param_1,-1);
  if (iVar1 == 0) {
    lua_getfenv(param_1,-1);
  }
  else {
    lua_pushvalue(param_1,-0x2712);
  }
  return 1;
}
