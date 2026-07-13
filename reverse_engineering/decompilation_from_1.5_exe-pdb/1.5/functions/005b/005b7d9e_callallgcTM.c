/*
 * Entry: 005b7d9e
 * Name: callallgcTM
 * Namespace: Global
 * Signature: void callallgcTM(lua_State * param_1, void * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl callallgcTM(lua_State *param_1,void *param_2)

{
  luaC_callGCTM(param_1);
  return;
}
