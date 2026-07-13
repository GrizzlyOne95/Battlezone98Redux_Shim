/*
 * Entry: 005c28e7
 * Name: luaB_setfenv
 * Namespace: Global
 * Signature: int luaB_setfenv(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl luaB_setfenv(lua_State *param_1)

{
  int iVar1;
  double dVar2;
  lua_State *plVar3;
  
  plVar3 = param_1;
  luaL_checktype(param_1,2,5);
  getfunc((lua_State *)0x0,(int)plVar3);
  lua_pushvalue(param_1,2);
  iVar1 = lua_isnumber(param_1,1);
  if ((iVar1 != 0) && (dVar2 = lua_tonumber(param_1,1), dVar2 == 0.0)) {
    lua_pushthread(param_1);
    lua_insert(param_1,-2);
    lua_setfenv(param_1,-2);
    return 0;
  }
  iVar1 = lua_iscfunction(param_1,-2);
  if ((iVar1 == 0) && (iVar1 = lua_setfenv(param_1,-2), iVar1 != 0)) {
    return 1;
  }
  luaL_error(param_1,"\'setfenv\' cannot change environment of given object");
  return 1;
}
