/*
 * Entry: 005c446d
 * Name: primaryexp
 * Namespace: Global
 * Signature: void primaryexp(LexState * param_1, expdesc * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl primaryexp(LexState *param_1,expdesc *param_2)

{
  int iVar1;
  TString *pTVar2;
  LexState *unaff_EBX;
  expdesc *unaff_ESI;
  TString *unaff_EDI;
  undefined4 uVar3;
  LexState *pLVar4;
  LexState *pLVar5;
  expdesc local_20;
  undefined4 local_8;
  
  local_8 = unaff_EBX->fs;
  iVar1 = (unaff_EBX->t).token;
  if (iVar1 == 0x28) {
    luaX_next(unaff_EBX);
    pLVar4 = unaff_EBX;
    pLVar5 = param_1;
    subexpr(unaff_EBX,(expdesc *)param_1,0);
    check_match((LexState *)0x29,0x28,(int)pLVar4,(int)pLVar5);
    luaK_dischargevars(unaff_EBX->fs,(expdesc *)param_1);
  }
  else if (iVar1 == 0x11d) {
    singlevar((LexState *)&unaff_EDI->tsv,unaff_ESI);
  }
  else {
    luaX_syntaxerror(unaff_EBX,"unexpected symbol");
  }
LAB_005c44d4:
  do {
    while (iVar1 = (unaff_EBX->t).token, iVar1 == 0x28) {
LAB_005c44ff:
      uVar3 = local_8;
      luaK_exp2nextreg((FuncState *)local_8,(expdesc *)param_1);
      funcargs(param_1,(expdesc *)uVar3);
    }
    if (iVar1 != 0x2e) {
      if (iVar1 == 0x3a) {
        pLVar4 = unaff_EBX;
        luaX_next(unaff_EBX);
        pTVar2 = str_checkname(pLVar4);
        codestring((LexState *)&pTVar2->tsv,(expdesc *)pLVar4,unaff_EDI);
        uVar3 = local_8;
        luaK_self((FuncState *)local_8,(expdesc *)param_1,&local_20);
        funcargs(param_1,(expdesc *)uVar3);
      }
      else {
        if (iVar1 != 0x5b) {
          if ((iVar1 != 0x7b) && (iVar1 != 0x11e)) {
            return;
          }
          goto LAB_005c44ff;
        }
        uVar3 = local_8;
        luaK_exp2anyreg((FuncState *)local_8,(expdesc *)param_1);
        yindex((LexState *)&local_20,(expdesc *)uVar3);
        luaK_indexed((FuncState *)local_8,(expdesc *)param_1,&local_20);
      }
      goto LAB_005c44d4;
    }
    field(param_1,(expdesc *)&unaff_EDI->tsv);
  } while( true );
}
