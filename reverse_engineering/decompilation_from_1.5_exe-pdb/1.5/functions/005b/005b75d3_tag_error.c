/*
 * Entry: 005b75d3
 * Name: tag_error
 * Namespace: Global
 * Signature: void tag_error(lua_State * param_1, int param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl tag_error(lua_State *param_1,int param_2,int param_3)

{
  char *pcVar1;
  
  pcVar1 = lua_typename(param_1,param_3);
  luaL_typerror(param_1,param_2,pcVar1);
  return;
}
