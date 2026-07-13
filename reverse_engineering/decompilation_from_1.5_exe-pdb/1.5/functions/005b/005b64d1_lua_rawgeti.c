/*
 * Entry: 005b64d1
 * Name: lua_rawgeti
 * Namespace: Global
 * Signature: void lua_rawgeti(lua_State * param_1, int param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl lua_rawgeti(lua_State *param_1,int param_2,int param_3)

{
  lua_TValue *plVar1;
  lua_TValue *plVar2;
  lua_State *unaff_ESI;
  int unaff_retaddr;
  
  plVar1 = index2adr(unaff_ESI,unaff_retaddr);
  plVar2 = luaH_getnum(&((plVar1->value).gc)->h,param_3);
  plVar1 = param_1->top;
  (plVar1->value).gc = (plVar2->value).gc;
  *(undefined4 *)((int)&plVar1->value + 4) = *(undefined4 *)((int)&plVar2->value + 4);
  plVar1->tt = plVar2->tt;
  param_1->top = param_1->top + 1;
  return;
}
