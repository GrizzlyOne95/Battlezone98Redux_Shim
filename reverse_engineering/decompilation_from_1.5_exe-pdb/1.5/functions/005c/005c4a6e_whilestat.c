/*
 * Entry: 005c4a6e
 * Name: whilestat
 * Namespace: Global
 * Signature: void whilestat(LexState * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl whilestat(LexState *param_1,int param_2)

{
  FuncState *pFVar1;
  LexState *in_EAX;
  int iVar2;
  int iVar3;
  int unaff_ESI;
  LexState *unaff_EDI;
  FuncState *pFVar4;
  FuncState *pFVar5;
  BlockCnt local_14;
  int local_8;
  
  pFVar1 = in_EAX->fs;
  luaX_next(in_EAX);
  iVar2 = luaK_getlabel(pFVar1);
  local_8 = cond(unaff_EDI);
  local_14.breaklist = -1;
  local_14.isbreakable = '\x01';
  local_14.nactvar = pFVar1->nactvar;
  local_14.upval = '\0';
  local_14.previous = pFVar1->bl;
  pFVar1->bl = &local_14;
  checknext(unaff_EDI,unaff_ESI);
  block(unaff_EDI);
  iVar3 = luaK_jump(pFVar1);
  pFVar5 = pFVar1;
  luaK_patchlist(pFVar1,iVar3,iVar2);
  pFVar4 = (FuncState *)0x106;
  check_match((LexState *)0x106,0x115,(int)pFVar5,iVar3);
  leaveblock(pFVar4);
  luaK_patchtohere(pFVar1,local_8);
  return;
}
