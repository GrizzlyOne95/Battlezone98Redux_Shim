/*
 * Entry: 005c3bf2
 * Name: close_func
 * Namespace: Global
 * Signature: void close_func(LexState * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl close_func(LexState *param_1)

{
  lua_State *plVar1;
  FuncState *pFVar2;
  Proto *pPVar3;
  int iVar4;
  TString *pTVar5;
  uint *puVar6;
  int *piVar7;
  lua_TValue *plVar8;
  Proto **ppPVar9;
  LocVar *pLVar10;
  TString **ppTVar11;
  int unaff_EDI;
  
  plVar1 = param_1->L;
  pFVar2 = param_1->fs;
  pPVar3 = pFVar2->f;
  removevars((LexState *)0x0,unaff_EDI);
  luaK_ret(pFVar2,0,0);
  if (pFVar2->pc + 1U < 0x40000000) {
    puVar6 = luaM_realloc_(plVar1,pPVar3->code,pPVar3->sizecode << 2,pFVar2->pc << 2);
  }
  else {
    puVar6 = luaM_toobig(plVar1);
  }
  pPVar3->code = puVar6;
  pPVar3->sizecode = pFVar2->pc;
  if (pFVar2->pc + 1U < 0x40000000) {
    piVar7 = luaM_realloc_(plVar1,pPVar3->lineinfo,pPVar3->sizelineinfo << 2,pFVar2->pc << 2);
  }
  else {
    piVar7 = luaM_toobig(plVar1);
  }
  pPVar3->lineinfo = piVar7;
  pPVar3->sizelineinfo = pFVar2->pc;
  if (pFVar2->nk + 1U < 0x10000000) {
    plVar8 = luaM_realloc_(plVar1,pPVar3->k,pPVar3->sizek << 4,pFVar2->nk << 4);
  }
  else {
    plVar8 = luaM_toobig(plVar1);
  }
  pPVar3->k = plVar8;
  pPVar3->sizek = pFVar2->nk;
  if (pFVar2->np + 1U < 0x40000000) {
    ppPVar9 = luaM_realloc_(plVar1,pPVar3->p,pPVar3->sizep << 2,pFVar2->np << 2);
  }
  else {
    ppPVar9 = luaM_toobig(plVar1);
  }
  pPVar3->p = ppPVar9;
  pPVar3->sizep = pFVar2->np;
  if ((int)pFVar2->nlocvars + 1U < 0x15555556) {
    pLVar10 = luaM_realloc_(plVar1,pPVar3->locvars,pPVar3->sizelocvars * 0xc,pFVar2->nlocvars * 0xc)
    ;
  }
  else {
    pLVar10 = luaM_toobig(plVar1);
  }
  pPVar3->locvars = pLVar10;
  pPVar3->sizelocvars = (int)pFVar2->nlocvars;
  if (pPVar3->nups + 1 < 0x40000000) {
    ppTVar11 = luaM_realloc_(plVar1,pPVar3->upvalues,pPVar3->sizeupvalues << 2,
                             (uint)pPVar3->nups << 2);
  }
  else {
    ppTVar11 = luaM_toobig(plVar1);
  }
  pPVar3->upvalues = ppTVar11;
  pPVar3->sizeupvalues = (uint)pPVar3->nups;
  param_1->fs = pFVar2->prev;
  iVar4 = (param_1->t).token;
  if ((iVar4 == 0x11d) || (iVar4 == 0x11e)) {
    pTVar5 = (param_1->t).seminfo.ts;
    luaX_newstring(param_1,(char *)(pTVar5 + 1),(pTVar5->tsv).len);
  }
  plVar1->top = plVar1->top + -2;
  return;
}
