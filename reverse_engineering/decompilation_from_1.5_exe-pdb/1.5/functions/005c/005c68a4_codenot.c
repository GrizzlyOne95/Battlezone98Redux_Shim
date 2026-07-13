/*
 * Entry: 005c68a4
 * Name: codenot
 * Namespace: Global
 * Signature: void codenot(FuncState * param_1, expdesc * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl codenot(FuncState *param_1,expdesc *param_2)

{
  expkind eVar1;
  int iVar2;
  expdesc *unaff_ESI;
  FuncState *unaff_EDI;
  FuncState *unaff_retaddr;
  FuncState *pFVar3;
  
  luaK_dischargevars(unaff_EDI,unaff_ESI);
  eVar1 = unaff_ESI->k;
  if (5 < (int)eVar1) {
    if (eVar1 == VJMP) {
      invertjump(unaff_EDI,(expdesc *)unaff_retaddr);
    }
    else if (eVar1 - VRELOCABLE < 2) {
      discharge2anyreg(unaff_retaddr,(expdesc *)param_1);
      freeexp(unaff_EDI,(expdesc *)unaff_retaddr);
      iVar2 = luaK_codeABC(unaff_EDI,OP_NOT,0,(unaff_ESI->u).s.info,0);
      (unaff_ESI->u).s.info = iVar2;
      unaff_ESI->k = VRELOCABLE;
    }
    goto LAB_005c6916;
  }
  if ((int)eVar1 < 4) {
    if (eVar1 != VNIL) {
      if (eVar1 == VTRUE) goto LAB_005c68ca;
      if (eVar1 != VFALSE) goto LAB_005c6916;
    }
    unaff_ESI->k = VTRUE;
  }
  else {
LAB_005c68ca:
    unaff_ESI->k = VFALSE;
  }
LAB_005c6916:
  iVar2 = unaff_ESI->t;
  unaff_ESI->t = unaff_ESI->f;
  unaff_ESI->f = iVar2;
  pFVar3 = unaff_EDI;
  removevalues(unaff_EDI,(int)unaff_retaddr);
  removevalues(unaff_EDI,(int)pFVar3);
  return;
}
