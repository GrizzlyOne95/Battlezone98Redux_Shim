/*
 * Entry: 005c3e1c
 * Name: recfield
 * Namespace: Global
 * Signature: void recfield(LexState * param_1, ConsControl * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl recfield(LexState *param_1,ConsControl *param_2)

{
  FuncState *pFVar1;
  TString *pTVar2;
  int iVar3;
  int iVar4;
  int unaff_EBX;
  TString *unaff_ESI;
  LexState *unaff_EDI;
  expdesc local_38;
  expdesc local_20;
  undefined4 local_8;
  
  pFVar1 = param_1->fs;
  local_8 = pFVar1->freereg;
  if ((param_1->t).token == 0x11d) {
    if (0x7ffffffd < *(int *)(unaff_EBX + 0x1c)) {
      errorlimit((FuncState *)0x7ffffffd,0x622394,(char *)unaff_EDI);
    }
    pTVar2 = str_checkname(unaff_EDI);
    codestring((LexState *)&pTVar2->tsv,(expdesc *)unaff_EDI,unaff_ESI);
  }
  else {
    yindex((LexState *)&local_20,(expdesc *)unaff_EDI);
  }
  *(int *)(unaff_EBX + 0x1c) = *(int *)(unaff_EBX + 0x1c) + 1;
  checknext(unaff_EDI,(int)unaff_ESI);
  iVar3 = luaK_exp2RK(pFVar1,&local_20);
  subexpr(param_1,&local_38,0);
  iVar4 = luaK_exp2RK(pFVar1,&local_38);
  luaK_codeABC(pFVar1,OP_SETTABLE,*(int *)(*(int *)(unaff_EBX + 0x18) + 8),iVar3,iVar4);
  pFVar1->freereg = local_8;
  return;
}
