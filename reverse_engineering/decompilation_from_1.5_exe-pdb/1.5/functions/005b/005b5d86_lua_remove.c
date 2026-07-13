/*
 * Entry: 005b5d86
 * Name: lua_remove
 * Namespace: Global
 * Signature: void lua_remove(lua_State * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl lua_remove(lua_State *param_1,int param_2)

{
  lua_TValue *plVar1;
  lua_TValue *plVar2;
  lua_State *unaff_ESI;
  int unaff_retaddr;
  
  plVar1 = index2adr(unaff_ESI,unaff_retaddr);
  plVar2 = plVar1 + 1;
  if (plVar2 < param_1->top) {
    do {
      (plVar1->value).gc = (plVar2->value).gc;
      *(undefined4 *)((int)&plVar1->value + 4) = *(undefined4 *)((int)&plVar2->value + 4);
      plVar1->tt = plVar1[1].tt;
      plVar2 = plVar2 + 1;
      plVar1 = plVar1 + 1;
    } while (plVar2 < param_1->top);
  }
  param_1->top = param_1->top + -1;
  return;
}
