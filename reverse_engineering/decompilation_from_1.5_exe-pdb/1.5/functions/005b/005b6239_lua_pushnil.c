/*
 * Entry: 005b6239
 * Name: lua_pushnil
 * Namespace: Global
 * Signature: void lua_pushnil(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl lua_pushnil(lua_State *param_1)

{
  param_1->top->tt = 0;
  param_1->top = param_1->top + 1;
  return;
}
