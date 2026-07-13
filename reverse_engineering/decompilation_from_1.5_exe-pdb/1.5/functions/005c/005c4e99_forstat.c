/*
 * Entry: 005c4e99
 * Name: forstat
 * Namespace: Global
 * Signature: void forstat(LexState * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl forstat(LexState *param_1,int param_2)

{
  FuncState *pFVar1;
  int iVar2;
  TString *in_EAX;
  TString *pTVar3;
  LexState *unaff_EBX;
  int unaff_ESI;
  TString *unaff_EDI;
  BlockCnt local_10;
  
  local_10.breaklist = -1;
  pFVar1 = unaff_EBX->fs;
  local_10.isbreakable = '\x01';
  local_10.nactvar = pFVar1->nactvar;
  local_10.upval = '\0';
  local_10.previous = pFVar1->bl;
  pFVar1->bl = &local_10;
  luaX_next(unaff_EBX);
  pTVar3 = str_checkname((LexState *)&unaff_EDI->tsv);
  iVar2 = (unaff_EBX->t).token;
  if (iVar2 != 0x2c) {
    if (iVar2 == 0x3d) {
      fornum((LexState *)&pTVar3->tsv,in_EAX,(int)unaff_EDI);
      goto LAB_005c4f08;
    }
    if (iVar2 != 0x10b) {
      luaX_syntaxerror(unaff_EBX,"\'=\' or \'in\' expected");
      goto LAB_005c4f08;
    }
  }
  forlist((LexState *)&pTVar3->tsv,unaff_EDI);
LAB_005c4f08:
  check_match((LexState *)0x106,0x108,(int)unaff_EDI,unaff_ESI);
  leaveblock((FuncState *)&unaff_EDI->tsv);
  return;
}
