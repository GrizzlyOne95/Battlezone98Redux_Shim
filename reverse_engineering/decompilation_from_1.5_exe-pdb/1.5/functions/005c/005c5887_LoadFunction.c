/*
 * Entry: 005c5887
 * Name: LoadFunction
 * Namespace: Global
 * Signature: Proto * LoadFunction(LoadState * param_1, TString * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Proto * __cdecl LoadFunction(LoadState *param_1,TString *param_2)

{
  ushort *puVar1;
  lua_TValue **pplVar2;
  lua_TValue *plVar3;
  lua_State *plVar4;
  Proto *pPVar5;
  TString *pTVar6;
  int iVar7;
  Proto *pPVar8;
  LoadState *unaff_EBX;
  LoadState *unaff_EDI;
  LoadState *pLVar9;
  
  puVar1 = &param_1->L->nCcalls;
  *puVar1 = *puVar1 + 1;
  if (200 < param_1->L->nCcalls) {
    error((LoadState *)"code too deep",(char *)unaff_EDI);
  }
  pPVar5 = luaF_newproto(param_1->L);
  plVar3 = param_1->L->top;
  (plVar3->value).b = (int)pPVar5;
  plVar3->tt = 9;
  plVar4 = param_1->L;
  if ((int)plVar4->stack_last - (int)plVar4->top < 0x11) {
    luaD_growstack(plVar4,1);
  }
  pplVar2 = &param_1->L->top;
  *pplVar2 = *pplVar2 + 1;
  pTVar6 = LoadString(unaff_EDI);
  pPVar5->source = pTVar6;
  if (pTVar6 == (TString *)0x0) {
    pPVar5->source = param_2;
  }
  iVar7 = LoadInt(unaff_EBX);
  pPVar5->linedefined = iVar7;
  iVar7 = LoadInt(unaff_EBX);
  pPVar5->lastlinedefined = iVar7;
  iVar7 = LoadChar(param_1);
  pPVar5->nups = (uchar)iVar7;
  iVar7 = LoadChar(param_1);
  pPVar5->numparams = (uchar)iVar7;
  iVar7 = LoadChar(param_1);
  pPVar5->is_vararg = (uchar)iVar7;
  iVar7 = LoadChar(param_1);
  pPVar5->maxstacksize = (uchar)iVar7;
  iVar7 = LoadInt(unaff_EBX);
  if (iVar7 + 1U < 0x40000000) {
    pPVar8 = luaM_realloc_(param_1->L,(void *)0x0,0,iVar7 << 2);
  }
  else {
    pPVar8 = luaM_toobig(param_1->L);
  }
  pPVar5->code = (uint *)pPVar8;
  pPVar5->sizecode = iVar7;
  LoadBlock((LoadState *)pPVar8,(void *)(iVar7 << 2),(uint)unaff_EBX);
  pLVar9 = param_1;
  LoadConstants(param_1,pPVar8);
  LoadDebug(pLVar9,pPVar8);
  iVar7 = luaG_checkcode(pPVar5);
  if (iVar7 == 0) {
    error((LoadState *)"bad code",(char *)unaff_EDI);
  }
  pplVar2 = &param_1->L->top;
  *pplVar2 = *pplVar2 + -1;
  puVar1 = &param_1->L->nCcalls;
  *puVar1 = *puVar1 - 1;
  return pPVar5;
}
