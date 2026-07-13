/*
 * Entry: 005c30ef
 * Name: luaB_costatus
 * Namespace: Global
 * Signature: int luaB_costatus(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl luaB_costatus(lua_State *param_1)

{
  lua_State *plVar1;
  int iVar2;
  lua_State *unaff_EDI;
  
  plVar1 = lua_tothread(param_1,1);
  if (plVar1 == (lua_State *)0x0) {
    luaL_argerror(param_1,1,"coroutine expected");
  }
  iVar2 = costatus(param_1,unaff_EDI);
  lua_pushstring(param_1,statnames[iVar2]);
  return 1;
}
