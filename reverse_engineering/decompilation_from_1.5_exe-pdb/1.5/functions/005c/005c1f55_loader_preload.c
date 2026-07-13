/*
 * Entry: 005c1f55
 * Name: loader_preload
 * Namespace: Global
 * Signature: int loader_preload(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl loader_preload(lua_State *param_1)

{
  char *pcVar1;
  int iVar2;
  
  pcVar1 = luaL_checklstring(param_1,1,(uint *)0x0);
  lua_getfield(param_1,-0x2711,"preload");
  iVar2 = lua_type(param_1,-1);
  if (iVar2 != 5) {
    luaL_error(param_1,"\'package.preload\' must be a table");
  }
  lua_getfield(param_1,-1,pcVar1);
  iVar2 = lua_type(param_1,-1);
  if (iVar2 == 0) {
    lua_pushfstring(param_1,"\n\tno field package.preload[\'%s\']");
  }
  return 1;
}
