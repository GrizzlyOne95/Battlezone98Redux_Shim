/*
 * Entry: 005b76a3
 * Name: luaL_checklstring
 * Namespace: Global
 * Signature: char * luaL_checklstring(lua_State * param_1, int param_2, uint * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

char * __cdecl luaL_checklstring(lua_State *param_1,int param_2,uint *param_3)

{
  char *pcVar1;
  
  pcVar1 = lua_tolstring(param_1,param_2,param_3);
  if (pcVar1 == (char *)0x0) {
    tag_error(param_1,param_2,4);
  }
  return pcVar1;
}
