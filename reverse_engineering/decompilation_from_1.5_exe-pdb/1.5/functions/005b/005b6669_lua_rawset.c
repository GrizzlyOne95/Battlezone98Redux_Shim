/*
 * Entry: 005b6669
 * Name: lua_rawset
 * Namespace: Global
 * Signature: void lua_rawset(lua_State * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl lua_rawset(lua_State *param_1,int param_2)

{
  lua_TValue *plVar1;
  lua_TValue *plVar2;
  lua_TValue *plVar3;
  int unaff_ESI;
  lua_State *unaff_EDI;
  
  plVar2 = index2adr(unaff_EDI,unaff_ESI);
  plVar1 = param_1->top;
  plVar3 = luaH_set(param_1,&((plVar2->value).gc)->h,plVar1 + -2);
  (plVar3->value).gc = plVar1[-1].value.gc;
  *(undefined4 *)((int)&plVar3->value + 4) = *(undefined4 *)((int)&plVar1[-1].value + 4);
  plVar3->tt = plVar1[-1].tt;
  if (((3 < param_1->top[-1].tt) && ((*(byte *)(param_1->top[-1].value.b + 5) & 3) != 0)) &&
     (((((plVar2->value).gc)->gch).marked & 4) != 0)) {
    luaC_barrierback(param_1,&((plVar2->value).gc)->h);
  }
  param_1->top = param_1->top + -2;
  return;
}
