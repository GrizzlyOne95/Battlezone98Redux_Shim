/*
 * Entry: 005c529c
 * Name: statement
 * Namespace: Global
 * Signature: int statement(LexState * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl statement(LexState *param_1)

{
  LexState *pLVar1;
  LexState *in_EAX;
  int iVar2;
  int unaff_EBX;
  int unaff_ESI;
  LexState *unaff_EDI;
  
  pLVar1 = (LexState *)in_EAX->linenumber;
  switch((in_EAX->t).token) {
  case 0x102:
    luaX_next(in_EAX);
    breakstat(unaff_EDI);
    return 1;
  case 0x103:
    luaX_next(in_EAX);
    block(in_EAX);
    check_match((LexState *)0x106,0x103,(int)unaff_EDI,unaff_EBX);
    break;
  default:
    exprstat(unaff_EDI);
    break;
  case 0x108:
    forstat(unaff_EDI,unaff_EBX);
    break;
  case 0x109:
    funcstat(pLVar1,(int)unaff_EDI);
    break;
  case 0x10a:
    ifstat(pLVar1,unaff_ESI);
    break;
  case 0x10c:
    luaX_next(in_EAX);
    iVar2 = testnext((LexState *)0x109,(int)unaff_EDI);
    if (iVar2 == 0) {
      localstat(unaff_EDI);
    }
    else {
      localfunc(unaff_EDI);
    }
    break;
  case 0x110:
    repeatstat(pLVar1,(int)unaff_EDI);
    break;
  case 0x111:
    retstat(unaff_EDI);
    return 1;
  case 0x115:
    whilestat(pLVar1,(int)unaff_EDI);
  }
  return 0;
}
