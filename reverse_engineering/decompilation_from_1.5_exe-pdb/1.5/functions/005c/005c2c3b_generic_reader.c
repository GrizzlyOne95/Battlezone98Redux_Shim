/*
 * Entry: 005c2c3b
 * Name: generic_reader
 * Namespace: Global
 * Signature: char * generic_reader(lua_State * param_1, void * param_2, uint * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

char * __cdecl generic_reader(lua_State *param_1,void *param_2,uint *param_3)

{
  int iVar1;
  char *pcVar2;
  
  luaL_checkstack(param_1,2,"too many nested functions");
  lua_pushvalue(param_1,1);
  lua_call(param_1,0,1);
  iVar1 = lua_type(param_1,-1);
  if (iVar1 == 0) {
    *param_3 = 0;
  }
  else {
    iVar1 = lua_isstring(param_1,-1);
    if (iVar1 != 0) {
      lua_replace(param_1,3);
      pcVar2 = lua_tolstring(param_1,3,param_3);
      return pcVar2;
    }
    luaL_error(param_1,"reader function must return a string");
  }
  return (char *)0x0;
}
