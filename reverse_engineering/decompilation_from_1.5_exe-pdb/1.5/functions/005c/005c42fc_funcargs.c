/*
 * Entry: 005c42fc
 * Name: funcargs
 * Namespace: Global
 * Signature: void funcargs(LexState * param_1, expdesc * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl funcargs(LexState *param_1,expdesc *param_2)

{
  int iVar1;
  LexState *in_EAX;
  int iVar2;
  TString *unaff_ESI;
  LexState *unaff_EDI;
  undefined4 uVar3;
  expdesc local_24;
  SemInfo local_c;
  
  iVar1 = (in_EAX->t).token;
  local_c._4_4_ = in_EAX->linenumber;
  uVar3 = in_EAX->fs;
  local_c.ts = (TString *)uVar3;
  if (iVar1 == 0x28) {
    if (local_c._4_4_ != in_EAX->lastline) {
      luaX_syntaxerror(in_EAX,"ambiguous syntax (function call x new statement)");
    }
    luaX_next(in_EAX);
    if ((in_EAX->t).token == 0x29) {
      local_24.k = VVOID;
    }
    else {
      explist1((LexState *)&local_24,(expdesc *)unaff_EDI);
      luaK_setreturns((FuncState *)uVar3,&local_24,-1);
    }
    check_match((LexState *)0x29,0x28,(int)unaff_EDI,(int)unaff_ESI);
    uVar3 = local_c.ts;
  }
  else if (iVar1 == 0x7b) {
    constructor(unaff_EDI,(expdesc *)&unaff_ESI->tsv);
  }
  else {
    if (iVar1 != 0x11e) {
      luaX_syntaxerror(in_EAX,"function arguments expected");
      return;
    }
    codestring((LexState *)&((in_EAX->t).seminfo.ts)->tsv,(expdesc *)unaff_EDI,unaff_ESI);
    luaX_next(in_EAX);
  }
  iVar1 = param_1->lastline;
  if ((local_24.k == VCALL) || (local_24.k == VVARARG)) {
    iVar2 = -1;
  }
  else {
    if (local_24.k != VVOID) {
      luaK_exp2nextreg((FuncState *)uVar3,&local_24);
    }
    iVar2 = (*(int *)(uVar3 + 0x24) - iVar1) + -1;
  }
  iVar2 = luaK_codeABC((FuncState *)uVar3,OP_CALL,iVar1,iVar2 + 1,2);
  (param_1->t).token = -1;
  *(undefined4 *)&(param_1->t).field_0x4 = 0xffffffff;
  param_1->current = 0xd;
  param_1->lastline = iVar2;
  luaK_fixline((FuncState *)uVar3,local_c._4_4_);
  *(int *)(uVar3 + 0x24) = iVar1 + 1;
  return;
}
