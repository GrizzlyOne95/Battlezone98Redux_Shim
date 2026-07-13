/*
 * Entry: 005b63c9
 * Name: lua_pushboolean
 * Namespace: Global
 * Signature: void lua_pushboolean(lua_State * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl lua_pushboolean(lua_State *param_1,int param_2)

{
  lua_TValue *plVar1;
  
  plVar1 = param_1->top;
  plVar1->tt = 1;
  *(uint *)&plVar1->value = (uint)(param_2 != 0);
  param_1->top = param_1->top + 1;
  return;
}
