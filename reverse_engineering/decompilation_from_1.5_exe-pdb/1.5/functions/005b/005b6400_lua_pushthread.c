/*
 * Entry: 005b6400
 * Name: lua_pushthread
 * Namespace: Global
 * Signature: int lua_pushthread(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl lua_pushthread(lua_State *param_1)

{
  lua_TValue *plVar1;
  
  plVar1 = param_1->top;
  (plVar1->value).gc = (GCObject *)param_1;
  plVar1->tt = 8;
  param_1->top = param_1->top + 1;
  return (uint)(param_1->l_G->mainthread == param_1);
}
