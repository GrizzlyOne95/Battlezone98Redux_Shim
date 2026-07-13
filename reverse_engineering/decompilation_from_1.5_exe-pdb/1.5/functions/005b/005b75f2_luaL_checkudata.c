/*
 * Entry: 005b75f2
 * Name: luaL_checkudata
 * Namespace: Global
 * Signature: void * luaL_checkudata(lua_State * param_1, int param_2, char * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __cdecl luaL_checkudata(lua_State *param_1,int param_2,char *param_3)

{
  void *pvVar1;
  int iVar2;
  
  pvVar1 = lua_touserdata(param_1,param_2);
  if ((pvVar1 != (void *)0x0) && (iVar2 = lua_getmetatable(param_1,param_2), iVar2 != 0)) {
    lua_getfield(param_1,-10000,param_3);
    iVar2 = lua_rawequal(param_1,-1,-2);
    if (iVar2 != 0) {
      lua_settop(param_1,-3);
      return pvVar1;
    }
  }
  luaL_typerror(param_1,param_2,param_3);
  return (void *)0x0;
}
