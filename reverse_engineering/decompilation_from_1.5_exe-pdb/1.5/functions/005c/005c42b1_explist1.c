/*
 * Entry: 005c42b1
 * Name: explist1
 * Namespace: Global
 * Signature: int explist1(LexState * param_1, expdesc * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl explist1(LexState *param_1,expdesc *param_2)

{
  int iVar1;
  LexState *unaff_ESI;
  int iVar2;
  LexState *pLVar3;
  
  iVar2 = 1;
  pLVar3 = unaff_ESI;
  subexpr(unaff_ESI,(expdesc *)param_1,0);
  iVar1 = testnext((LexState *)0x2c,(int)pLVar3);
  while (iVar1 != 0) {
    luaK_exp2nextreg(unaff_ESI->fs,(expdesc *)param_1);
    pLVar3 = unaff_ESI;
    subexpr(unaff_ESI,(expdesc *)param_1,0);
    iVar2 = iVar2 + 1;
    iVar1 = testnext((LexState *)0x2c,(int)pLVar3);
  }
  return iVar2;
}
