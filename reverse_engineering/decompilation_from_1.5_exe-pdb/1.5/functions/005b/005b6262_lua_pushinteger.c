/*
 * Entry: 005b6262
 * Name: lua_pushinteger
 * Namespace: Global
 * Signature: void lua_pushinteger(lua_State * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl lua_pushinteger(lua_State *param_1,int param_2)

{
  lua_TValue *plVar1;
  
  plVar1 = param_1->top;
  plVar1->tt = 3;
  (plVar1->value).n = (double)param_2;
  param_1->top = param_1->top + 1;
  return;
}
