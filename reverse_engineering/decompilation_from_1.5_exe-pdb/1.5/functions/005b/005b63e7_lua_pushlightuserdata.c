/*
 * Entry: 005b63e7
 * Name: lua_pushlightuserdata
 * Namespace: Global
 * Signature: void lua_pushlightuserdata(lua_State * param_1, void * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl lua_pushlightuserdata(lua_State *param_1,void *param_2)

{
  lua_TValue *plVar1;
  
  plVar1 = param_1->top;
  (plVar1->value).p = param_2;
  plVar1->tt = 2;
  param_1->top = param_1->top + 1;
  return;
}
