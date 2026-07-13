/*
 * Entry: 005b884a
 * Name: lua_yield
 * Namespace: Global
 * Signature: int lua_yield(lua_State * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl lua_yield(lua_State *param_1,int param_2)

{
  if (param_1->baseCcalls < param_1->nCcalls) {
    luaG_runerror(param_1,"attempt to yield across metamethod/C-call boundary");
  }
  param_1->base = param_1->top + -param_2;
  param_1->status = '\x01';
  return -1;
}
