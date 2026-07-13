/*
 * Entry: 005c4b00
 * Name: repeatstat
 * Namespace: Global
 * Signature: void repeatstat(LexState * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl repeatstat(LexState *param_1,int param_2)

{
  FuncState *pFVar1;
  LexState *in_EAX;
  int iVar2;
  FuncState *unaff_EDI;
  LexState *pLVar3;
  LexState *pLVar4;
  int iVar5;
  BlockCnt local_24;
  BlockCnt local_18;
  int local_c;
  int local_8;
  
  pFVar1 = in_EAX->fs;
  local_c = luaK_getlabel(pFVar1);
  local_24.breaklist = -1;
  local_24.isbreakable = '\x01';
  local_24.nactvar = pFVar1->nactvar;
  local_24.upval = '\0';
  local_24.previous = pFVar1->bl;
  pFVar1->bl = &local_24;
  local_18.breaklist = -1;
  local_18.isbreakable = '\0';
  local_18.nactvar = pFVar1->nactvar;
  local_18.upval = '\0';
  local_18.previous = pFVar1->bl;
  pFVar1->bl = &local_18;
  pLVar4 = in_EAX;
  luaX_next(in_EAX);
  pLVar3 = in_EAX;
  chunk(in_EAX);
  check_match((LexState *)0x114,0x110,(int)pLVar3,(int)pLVar4);
  local_8 = cond((LexState *)unaff_EDI);
  if (local_18.upval == '\0') {
    leaveblock(unaff_EDI);
    iVar2 = local_8;
    iVar5 = local_c;
  }
  else {
    breakstat((LexState *)unaff_EDI);
    luaK_patchtohere(in_EAX->fs,local_8);
    leaveblock(unaff_EDI);
    iVar5 = local_c;
    iVar2 = luaK_jump(pFVar1);
  }
  luaK_patchlist(in_EAX->fs,iVar2,iVar5);
  leaveblock(unaff_EDI);
  return;
}
