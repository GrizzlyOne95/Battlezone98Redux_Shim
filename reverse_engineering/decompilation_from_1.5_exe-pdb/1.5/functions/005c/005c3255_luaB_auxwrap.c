/*
 * Entry: 005c3255
 * Name: luaB_auxwrap
 * Namespace: Global
 * Signature: int luaB_auxwrap(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl luaB_auxwrap(lua_State *param_1)

{
  lua_State *plVar1;
  int iVar2;
  int iVar3;
  lua_State *plVar4;
  lua_State *plVar5;
  
  plVar5 = param_1;
  lua_tothread(param_1,-0x2713);
  plVar4 = param_1;
  plVar1 = (lua_State *)lua_gettop(param_1);
  iVar2 = auxresume(plVar1,plVar4,(int)plVar5);
  if (iVar2 < 0) {
    iVar3 = lua_isstring(param_1,-1);
    if (iVar3 != 0) {
      luaL_where(param_1,1);
      lua_insert(param_1,-2);
      lua_concat(param_1,2);
    }
    lua_error(param_1);
  }
  return iVar2;
}
