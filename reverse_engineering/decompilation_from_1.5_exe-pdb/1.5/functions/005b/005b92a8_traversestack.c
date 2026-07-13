/*
 * Entry: 005b92a8
 * Name: traversestack
 * Namespace: Global
 * Signature: void traversestack(global_State * param_1, lua_State * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl traversestack(global_State *param_1,lua_State *param_2)

{
  GCObject *pGVar1;
  int iVar2;
  CallInfo *pCVar3;
  lua_TValue *extraout_EDX;
  lua_TValue *plVar4;
  lua_State *unaff_ESI;
  lua_TValue *plVar5;
  
  if ((3 < (unaff_ESI->l_gt).tt) &&
     (pGVar1 = (unaff_ESI->l_gt).value.gc, ((pGVar1->gch).marked & 3) != 0)) {
    reallymarkobject(param_1,pGVar1);
  }
  plVar5 = unaff_ESI->top;
  for (pCVar3 = unaff_ESI->base_ci; pCVar3 <= unaff_ESI->ci; pCVar3 = pCVar3 + 1) {
    if (plVar5 < pCVar3->top) {
      plVar5 = pCVar3->top;
    }
  }
  plVar4 = unaff_ESI->stack;
  if (plVar4 < unaff_ESI->top) {
    do {
      if ((3 < plVar4->tt) && (((((plVar4->value).gc)->gch).marked & 3) != 0)) {
        reallymarkobject(param_1,(plVar4->value).gc);
        plVar4 = extraout_EDX;
      }
      plVar4 = plVar4 + 1;
    } while (plVar4 < unaff_ESI->top);
  }
  for (; plVar4 <= plVar5; plVar4 = plVar4 + 1) {
    plVar4->tt = 0;
  }
  plVar4 = unaff_ESI->stack;
  iVar2 = unaff_ESI->size_ci;
  if (iVar2 < 0x4e21) {
    if (((((int)unaff_ESI->ci - (int)unaff_ESI->base_ci) / 0x18) * 4 < iVar2) && (0x10 < iVar2)) {
      luaD_reallocCI(unaff_ESI,iVar2 / 2);
    }
    iVar2 = unaff_ESI->stacksize;
    if ((((int)plVar5 - (int)plVar4 >> 4) * 4 < iVar2) && (0x5a < iVar2)) {
      luaD_reallocstack(unaff_ESI,iVar2 / 2);
    }
  }
  return;
}
