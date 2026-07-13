/*
 * Entry: 005b5c40
 * Name: lua_checkstack
 * Namespace: Global
 * Signature: int lua_checkstack(lua_State * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl lua_checkstack(lua_State *param_1,int param_2)

{
  if ((8000 < param_2) || (8000 < ((int)param_1->top - (int)param_1->base >> 4) + param_2)) {
    return 0;
  }
  if (param_2 < 1) {
    return 1;
  }
  if ((int)param_1->stack_last - (int)param_1->top <= param_2 * 0x10) {
    luaD_growstack(param_1,param_2);
  }
  if (param_1->top + param_2 <= param_1->ci->top) {
    return 1;
  }
  param_1->ci->top = param_1->top + param_2;
  return 1;
}
