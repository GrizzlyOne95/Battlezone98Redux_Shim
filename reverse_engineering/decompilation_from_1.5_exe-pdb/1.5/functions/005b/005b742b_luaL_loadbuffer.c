/*
 * Entry: 005b742b
 * Name: luaL_loadbuffer
 * Namespace: Global
 * Signature: int luaL_loadbuffer(lua_State * param_1, char * param_2, uint param_3, char * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl luaL_loadbuffer(lua_State *param_1,char *param_2,uint param_3,char *param_4)

{
  int iVar1;
  char *local_c;
  uint local_8;
  
  local_c = param_2;
  local_8 = param_3;
  iVar1 = lua_load(param_1,getS,&local_c,param_4);
  return iVar1;
}
