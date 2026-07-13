/*
 * Entry: 005b5c1e
 * Name: luaA_pushobject
 * Namespace: Global
 * Signature: void luaA_pushobject(lua_State * param_1, lua_TValue * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl luaA_pushobject(lua_State *param_1,lua_TValue *param_2)

{
  lua_TValue *plVar1;
  
  plVar1 = param_1->top;
  (plVar1->value).gc = (param_2->value).gc;
  *(undefined4 *)((int)&plVar1->value + 4) = *(undefined4 *)((int)&param_2->value + 4);
  plVar1->tt = param_2->tt;
  param_1->top = param_1->top + 1;
  return;
}
