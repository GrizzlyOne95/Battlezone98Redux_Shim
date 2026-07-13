/*
 * Entry: 005b672f
 * Name: lua_setmetatable
 * Namespace: Global
 * Signature: int lua_setmetatable(lua_State * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl lua_setmetatable(lua_State *param_1,int param_2)

{
  int iVar1;
  lua_TValue *plVar2;
  GCObject *pGVar3;
  int unaff_ESI;
  lua_State *unaff_EDI;
  
  plVar2 = index2adr(unaff_EDI,unaff_ESI);
  if (param_1->top[-1].tt == 0) {
    pGVar3 = (GCObject *)0x0;
  }
  else {
    pGVar3 = param_1->top[-1].value.gc;
  }
  iVar1 = plVar2->tt;
  if (iVar1 == 5) {
    *(GCObject **)((plVar2->value).b + 8) = pGVar3;
    if (((pGVar3 != (GCObject *)0x0) && (((pGVar3->gch).marked & 3) != 0)) &&
       (((((plVar2->value).gc)->gch).marked & 4) != 0)) {
      luaC_barrierback(param_1,&((plVar2->value).gc)->h);
    }
  }
  else if (iVar1 == 7) {
    *(GCObject **)((plVar2->value).b + 8) = pGVar3;
    if (((pGVar3 != (GCObject *)0x0) && (((pGVar3->gch).marked & 3) != 0)) &&
       (((((plVar2->value).gc)->gch).marked & 4) != 0)) {
      luaC_barrierf(param_1,(plVar2->value).gc,pGVar3);
    }
  }
  else {
    param_1->l_G->mt[iVar1] = (Table *)pGVar3;
  }
  param_1->top = param_1->top + -1;
  return 1;
}
