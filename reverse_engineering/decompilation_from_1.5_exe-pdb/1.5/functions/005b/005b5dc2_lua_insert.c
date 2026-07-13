/*
 * Entry: 005b5dc2
 * Name: lua_insert
 * Namespace: Global
 * Signature: void lua_insert(lua_State * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl lua_insert(lua_State *param_1,int param_2)

{
  lua_TValue *plVar1;
  lua_TValue *plVar2;
  lua_TValue *plVar3;
  lua_State *unaff_ESI;
  int unaff_retaddr;
  
  plVar2 = index2adr(unaff_ESI,unaff_retaddr);
  plVar3 = param_1->top;
  plVar1 = plVar3;
  for (; plVar2 < plVar3; plVar3 = plVar3 + -1) {
    (plVar3->value).gc = plVar1[-1].value.gc;
    *(undefined4 *)((int)&plVar3->value + 4) = *(undefined4 *)((int)&plVar1[-1].value + 4);
    plVar1->tt = plVar1[-1].tt;
    plVar1 = plVar1 + -1;
  }
  plVar3 = param_1->top;
  (plVar2->value).gc = (plVar3->value).gc;
  *(undefined4 *)((int)&plVar2->value + 4) = *(undefined4 *)((int)&plVar3->value + 4);
  plVar2->tt = plVar3->tt;
  return;
}
