/*
 * Entry: 005bea40
 * Name: settabss
 * Namespace: Global
 * Signature: void settabss(lua_State * param_1, char * param_2, char * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl settabss(lua_State *param_1,char *param_2,char *param_3)

{
  lua_pushstring(param_1,param_3);
  lua_setfield(param_1,-2,param_2);
  return;
}
