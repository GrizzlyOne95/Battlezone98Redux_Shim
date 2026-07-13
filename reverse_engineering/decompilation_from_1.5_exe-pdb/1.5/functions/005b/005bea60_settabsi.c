/*
 * Entry: 005bea60
 * Name: settabsi
 * Namespace: Global
 * Signature: void settabsi(lua_State * param_1, char * param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl settabsi(lua_State *param_1,char *param_2,int param_3)

{
  lua_pushinteger(param_1,param_3);
  lua_setfield(param_1,-2,param_2);
  return;
}
