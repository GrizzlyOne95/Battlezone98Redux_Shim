/*
 * Entry: 005b6827
 * Name: lua_call
 * Namespace: Global
 * Signature: void lua_call(lua_State * param_1, int param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl lua_call(lua_State *param_1,int param_2,int param_3)

{
  luaD_call(param_1,param_1->top + -(param_2 + 1),param_3);
  if (param_3 == -1) {
    if (param_1->ci->top <= param_1->top) {
      param_1->ci->top = param_1->top;
    }
  }
  return;
}
