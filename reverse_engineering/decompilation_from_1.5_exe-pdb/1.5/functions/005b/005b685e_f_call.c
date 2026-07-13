/*
 * Entry: 005b685e
 * Name: f_call
 * Namespace: Global
 * Signature: void f_call(lua_State * param_1, void * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl f_call(lua_State *param_1,void *param_2)

{
  luaD_call(param_1,*(lua_TValue **)param_2,*(int *)((int)param_2 + 4));
  return;
}
