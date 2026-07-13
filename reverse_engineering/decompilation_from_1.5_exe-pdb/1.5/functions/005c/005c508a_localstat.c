/*
 * Entry: 005c508a
 * Name: localstat
 * Namespace: Global
 * Signature: void localstat(LexState * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl localstat(LexState *param_1)

{
  TString *pTVar1;
  int iVar2;
  LexState *pLVar3;
  TString *unaff_EBX;
  int unaff_ESI;
  LexState *unaff_EDI;
  expdesc *in_stack_ffffffe4;
  
  do {
    pTVar1 = str_checkname((LexState *)&unaff_EBX->tsv);
    new_localvar((LexState *)&pTVar1->tsv,unaff_EBX,(int)unaff_EDI);
    iVar2 = testnext((LexState *)0x2c,(int)pTVar1);
  } while (iVar2 != 0);
  iVar2 = testnext((LexState *)0x3d,(int)unaff_EBX);
  if (iVar2 == 0) {
    pLVar3 = (LexState *)0x0;
    in_stack_ffffffe4 = (expdesc *)0x0;
  }
  else {
    pLVar3 = (LexState *)explist1((LexState *)&stack0xffffffe4,(expdesc *)unaff_EDI);
  }
  adjust_assign(pLVar3,(int)unaff_EDI,unaff_ESI,in_stack_ffffffe4);
  adjustlocalvars(unaff_EDI,unaff_ESI);
  return;
}
