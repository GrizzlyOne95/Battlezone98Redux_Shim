/*
 * Entry: 005b5e0d
 * Name: lua_replace
 * Namespace: Global
 * Signature: void lua_replace(lua_State * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl lua_replace(lua_State *param_1,int param_2)

{
  byte bVar1;
  lua_TValue *plVar2;
  GCObject *pGVar3;
  GCObject *pGVar4;
  lua_TValue *plVar5;
  int unaff_ESI;
  lua_State *unaff_EDI;
  
  if ((param_2 == -0x2711) && (param_1->ci == param_1->base_ci)) {
    luaG_runerror(param_1,"no calling environment");
  }
  plVar5 = index2adr(unaff_EDI,unaff_ESI);
  plVar2 = param_1->top;
  if (param_2 == -0x2711) {
    pGVar3 = (param_1->ci->func->value).gc;
    (pGVar3->h).array = (lua_TValue *)plVar2[-1].value.gc;
    if ((param_1->top[-1].tt < 4) ||
       (pGVar4 = param_1->top[-1].value.gc, ((pGVar4->gch).marked & 3) == 0)) goto LAB_005b5eb6;
    bVar1 = (pGVar3->gch).marked;
  }
  else {
    (plVar5->value).gc = plVar2[-1].value.gc;
    *(undefined4 *)((int)&plVar5->value + 4) = *(undefined4 *)((int)&plVar2[-1].value + 4);
    plVar5->tt = plVar2[-1].tt;
    if (((-0x2713 < param_2) || (param_1->top[-1].tt < 4)) ||
       (pGVar4 = param_1->top[-1].value.gc, ((pGVar4->gch).marked & 3) == 0)) goto LAB_005b5eb6;
    pGVar3 = (param_1->ci->func->value).gc;
    bVar1 = (pGVar3->gch).marked;
  }
  if ((bVar1 & 4) != 0) {
    luaC_barrierf(param_1,pGVar3,pGVar4);
  }
LAB_005b5eb6:
  param_1->top = param_1->top + -1;
  return;
}
