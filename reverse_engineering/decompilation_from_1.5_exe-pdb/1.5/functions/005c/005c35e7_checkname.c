/*
 * Entry: 005c35e7
 * Name: checkname
 * Namespace: Global
 * Signature: void checkname(LexState * param_1, expdesc * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl checkname(LexState *param_1,expdesc *param_2)

{
  TString *pTVar1;
  LexState *unaff_retaddr;
  
  pTVar1 = str_checkname(unaff_retaddr);
  codestring((LexState *)&pTVar1->tsv,(expdesc *)unaff_retaddr,(TString *)param_1);
  return;
}
