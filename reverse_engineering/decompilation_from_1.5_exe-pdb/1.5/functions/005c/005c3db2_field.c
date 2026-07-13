/*
 * Entry: 005c3db2
 * Name: field
 * Namespace: Global
 * Signature: void field(LexState * param_1, expdesc * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl field(LexState *param_1,expdesc *param_2)

{
  TString *pTVar1;
  TString *pTVar2;
  LexState *unaff_EDI;
  TString *pTVar3;
  expdesc local_1c;
  
  pTVar1 = (TString *)unaff_EDI->fs;
  pTVar3 = pTVar1;
  luaK_exp2anyreg((FuncState *)&pTVar1->tsv,(expdesc *)param_1);
  luaX_next(unaff_EDI);
  pTVar2 = str_checkname(unaff_EDI);
  codestring((LexState *)&pTVar2->tsv,(expdesc *)unaff_EDI,pTVar3);
  luaK_indexed((FuncState *)&pTVar1->tsv,(expdesc *)param_1,&local_1c);
  return;
}
