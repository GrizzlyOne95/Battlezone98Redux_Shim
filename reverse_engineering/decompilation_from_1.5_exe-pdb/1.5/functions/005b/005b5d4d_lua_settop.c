/*
 * Entry: 005b5d4d
 * Name: lua_settop
 * Namespace: Global
 * Signature: void lua_settop(lua_State * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl lua_settop(lua_State *param_1,int param_2)

{
  if (param_2 < 0) {
    param_1->top = param_1->top + param_2 + 1;
    return;
  }
  while (param_1->top < param_1->base + param_2) {
    param_1->top->tt = 0;
    param_1->top = param_1->top + 1;
  }
  param_1->top = param_1->base + param_2;
  return;
}
