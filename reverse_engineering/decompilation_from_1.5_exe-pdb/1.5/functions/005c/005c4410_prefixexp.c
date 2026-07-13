/*
 * Entry: 005c4410
 * Name: prefixexp
 * Namespace: Global
 * Signature: void prefixexp(LexState * param_1, expdesc * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl prefixexp(LexState *param_1,expdesc *param_2)

{
  int iVar1;
  LexState *unaff_ESI;
  LexState *unaff_EDI;
  expdesc *unaff_retaddr;
  LexState *pLVar2;
  LexState *pLVar3;
  
  iVar1 = (unaff_ESI->t).token;
  if (iVar1 == 0x28) {
    luaX_next(unaff_ESI);
    pLVar2 = unaff_ESI;
    pLVar3 = param_1;
    subexpr(unaff_ESI,(expdesc *)param_1,0);
    check_match((LexState *)0x29,0x28,(int)pLVar2,(int)pLVar3);
    luaK_dischargevars(unaff_ESI->fs,(expdesc *)param_1);
    return;
  }
  if (iVar1 != 0x11d) {
    luaX_syntaxerror(unaff_ESI,"unexpected symbol");
    return;
  }
  singlevar(unaff_EDI,unaff_retaddr);
  return;
}
