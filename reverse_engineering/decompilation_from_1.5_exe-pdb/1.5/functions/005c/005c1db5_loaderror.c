/*
 * Entry: 005c1db5
 * Name: loaderror
 * Namespace: Global
 * Signature: void loaderror(lua_State * param_1, char * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl loaderror(lua_State *param_1,char *param_2)

{
  lua_tolstring(param_1,-1,(uint *)0x0);
  lua_tolstring(param_1,1,(uint *)0x0);
  luaL_error(param_1,"error loading module \'%s\' from file \'%s\':\n\t%s");
  return;
}
