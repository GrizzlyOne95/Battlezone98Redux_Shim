/*
 * Entry: 005c48c2
 * Name: assignment
 * Namespace: Global
 * Signature: void assignment(LexState * param_1, LHS_assign * param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl assignment(LexState *param_1,LHS_assign *param_2,int param_3)

{
  expdesc *peVar1;
  int *piVar2;
  int iVar3;
  FuncState *pFVar4;
  LexState *pLVar5;
  expdesc *unaff_EBX;
  LHS_assign *unaff_ESI;
  LexState *unaff_EDI;
  LHS_assign local_3c;
  SemInfo local_1c;
  int local_14;
  undefined4 local_c;
  undefined4 local_8;
  
  peVar1 = &param_2->v;
  if (((int)peVar1->k < 6) || (9 < (int)peVar1->k)) {
    luaX_syntaxerror(param_1,"syntax error");
  }
  iVar3 = testnext((LexState *)0x2c,(int)unaff_EDI);
  if (iVar3 == 0) {
    checknext(unaff_EDI,(int)unaff_ESI);
    pLVar5 = (LexState *)explist1((LexState *)&local_1c,(expdesc *)unaff_EDI);
    if (pLVar5 == (LexState *)param_3) {
      luaK_setoneret(param_1->fs,(expdesc *)&local_1c);
      luaK_storevar(param_1->fs,peVar1,(expdesc *)&local_1c);
      return;
    }
    adjust_assign(pLVar5,(int)unaff_EDI,(int)unaff_ESI,unaff_EBX);
    if (param_3 < (int)pLVar5) {
      piVar2 = &param_1->fs->freereg;
      *piVar2 = *piVar2 + (param_3 - (int)pLVar5);
    }
  }
  else {
    local_3c.prev = param_2;
    primaryexp((LexState *)&local_3c.v,(expdesc *)unaff_EDI);
    if (local_3c.v.k == VLOCAL) {
      check_conflict(unaff_EDI,unaff_ESI,unaff_EBX);
    }
    pFVar4 = (FuncState *)(200 - (uint)param_1->L->nCcalls);
    if ((int)pFVar4 < param_3) {
      errorlimit(pFVar4,0x622464,(char *)unaff_EDI);
    }
    assignment(param_1,&local_3c,param_3 + 1);
  }
  local_c = 0xffffffff;
  local_8 = 0xffffffff;
  local_14 = param_1->fs->freereg + -1;
  local_1c.ts = (TString *)&DAT_0000000c;
  luaK_storevar(param_1->fs,peVar1,(expdesc *)&local_1c);
  return;
}
