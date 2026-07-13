/*
 * Entry: 005b6499
 * Name: lua_rawget
 * Namespace: Global
 * Signature: void lua_rawget(lua_State * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl lua_rawget(lua_State *param_1,int param_2)

{
  lua_TValue *plVar1;
  lua_TValue *plVar2;
  lua_State *unaff_ESI;
  int unaff_retaddr;
  
  plVar1 = index2adr(unaff_ESI,unaff_retaddr);
  plVar2 = luaH_get(&((plVar1->value).gc)->h,param_1->top + -1);
  plVar1 = param_1->top;
  plVar1[-1].value.gc = (plVar2->value).gc;
  *(undefined4 *)((int)&plVar1[-1].value + 4) = *(undefined4 *)((int)&plVar2->value + 4);
  plVar1[-1].tt = plVar2->tt;
  return;
}
