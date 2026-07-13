/*
 * Entry: 005c4833
 * Name: block
 * Namespace: Global
 * Signature: void block(LexState * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl block(LexState *param_1)

{
  FuncState *pFVar1;
  LexState *in_EAX;
  FuncState *unaff_EDI;
  BlockCnt local_10;
  
  local_10.breaklist = -1;
  pFVar1 = in_EAX->fs;
  local_10.isbreakable = '\0';
  local_10.nactvar = pFVar1->nactvar;
  local_10.upval = '\0';
  local_10.previous = pFVar1->bl;
  pFVar1->bl = &local_10;
  chunk(in_EAX);
  leaveblock(unaff_EDI);
  return;
}
