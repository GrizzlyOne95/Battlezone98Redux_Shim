/*
 * Entry: 005b83c9
 * Name: luaD_reallocstack
 * Namespace: Global
 * Signature: void luaD_reallocstack(lua_State * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl luaD_reallocstack(lua_State *param_1,int param_2)

{
  lua_State *plVar1;
  lua_TValue *plVar2;
  
  plVar1 = (lua_State *)param_1->stack;
  if (param_2 + 7U < 0x10000000) {
    plVar2 = luaM_realloc_(param_1,plVar1,param_1->stacksize << 4,(param_2 + 6) * 0x10);
  }
  else {
    plVar2 = luaM_toobig(param_1);
  }
  param_1->stack_last = plVar2 + param_2;
  param_1->stack = plVar2;
  param_1->stacksize = param_2 + 6;
  correctstack(plVar1,(lua_TValue *)param_2);
  return;
}
