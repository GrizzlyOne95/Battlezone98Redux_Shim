/*
 * Entry: 005b5cec
 * Name: lua_setlevel
 * Namespace: Global
 * Signature: void lua_setlevel(lua_State * param_1, lua_State * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl lua_setlevel(lua_State *param_1,lua_State *param_2)

{
  param_2->nCcalls = param_1->nCcalls;
  return;
}
