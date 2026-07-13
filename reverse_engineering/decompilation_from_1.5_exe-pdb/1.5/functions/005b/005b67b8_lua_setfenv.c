/*
 * Entry: 005b67b8
 * Name: lua_setfenv
 * Namespace: Global
 * Signature: int lua_setfenv(lua_State * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl lua_setfenv(lua_State *param_1,int param_2)

{
  int iVar1;
  GCObject *pGVar2;
  lua_TValue *plVar3;
  int unaff_ESI;
  lua_State *unaff_EDI;
  int iVar4;
  
  iVar4 = 1;
  plVar3 = index2adr(unaff_EDI,unaff_ESI);
  iVar1 = plVar3->tt;
  if ((iVar1 == 6) || (iVar1 == 7)) {
    *(GCObject **)((plVar3->value).b + 0xc) = param_1->top[-1].value.gc;
  }
  else {
    if (iVar1 != 8) {
      iVar4 = 0;
      goto LAB_005b681e;
    }
    iVar1 = (plVar3->value).b;
    *(GCObject **)(iVar1 + 0x48) = param_1->top[-1].value.gc;
    *(undefined4 *)(iVar1 + 0x50) = 5;
  }
  pGVar2 = param_1->top[-1].value.gc;
  if ((((pGVar2->gch).marked & 3) != 0) && (((((plVar3->value).gc)->gch).marked & 4) != 0)) {
    luaC_barrierf(param_1,(plVar3->value).gc,pGVar2);
  }
LAB_005b681e:
  param_1->top = param_1->top + -1;
  return iVar4;
}
