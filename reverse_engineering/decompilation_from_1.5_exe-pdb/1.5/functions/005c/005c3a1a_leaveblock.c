/*
 * Entry: 005c3a1a
 * Name: leaveblock
 * Namespace: Global
 * Signature: void leaveblock(FuncState * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl leaveblock(FuncState *param_1)

{
  BlockCnt *pBVar1;
  int unaff_ESI;
  FuncState *unaff_EDI;
  
  pBVar1 = unaff_EDI->bl;
  unaff_EDI->bl = pBVar1->previous;
  removevars((LexState *)(uint)pBVar1->nactvar,unaff_ESI);
  if (pBVar1->upval != '\0') {
    luaK_codeABC(unaff_EDI,OP_CLOSE,(uint)pBVar1->nactvar,0,0);
  }
  unaff_EDI->freereg = (uint)unaff_EDI->nactvar;
  luaK_patchtohere(unaff_EDI,pBVar1->breaklist);
  return;
}
