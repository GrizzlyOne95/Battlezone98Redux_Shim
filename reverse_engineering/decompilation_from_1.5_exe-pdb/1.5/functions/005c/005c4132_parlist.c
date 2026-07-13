/*
 * Entry: 005c4132
 * Name: parlist
 * Namespace: Global
 * Signature: void parlist(LexState * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl parlist(LexState *param_1)

{
  GCObject *pGVar1;
  GCObject *pGVar2;
  TString *in_EAX;
  TString *pTVar3;
  TString *pTVar4;
  int iVar5;
  int unaff_ESI;
  TString *unaff_EDI;
  char *pcVar6;
  
  pGVar1 = in_EAX[3].tsv.next;
  pGVar2 = (pGVar1->gch).next;
  (pGVar2->p).is_vararg = '\0';
  if (in_EAX[1].tsv.next != (GCObject *)0x29) {
    do {
      if (in_EAX[1].tsv.next == (GCObject *)0x117) {
        luaX_next((LexState *)&in_EAX->tsv);
        pcVar6 = "arg";
        pTVar3 = in_EAX;
        pTVar4 = luaX_newstring((LexState *)&in_EAX->tsv,"arg",3);
        new_localvar((LexState *)&pTVar4->tsv,pTVar3,(int)pcVar6);
        (pGVar2->p).is_vararg = '\a';
      }
      else if (in_EAX[1].tsv.next == (GCObject *)0x11d) {
        pTVar3 = str_checkname((LexState *)&unaff_EDI->tsv);
        new_localvar((LexState *)&pTVar3->tsv,unaff_EDI,unaff_ESI);
      }
      else {
        luaX_syntaxerror((LexState *)&in_EAX->tsv,"<name> or \'...\' expected");
      }
    } while (((pGVar2->p).is_vararg == '\0') &&
            (iVar5 = testnext((LexState *)0x2c,(int)unaff_EDI), iVar5 != 0));
  }
  adjustlocalvars((LexState *)&unaff_EDI->tsv,unaff_ESI);
  (pGVar2->p).numparams =
       *(uchar *)((int)&(pGVar1->p).sizelineinfo + 2) - ((pGVar2->p).is_vararg & 1);
  luaK_reserveregs((FuncState *)&pGVar1->gch,(uint)*(uchar *)((int)&(pGVar1->p).sizelineinfo + 2));
  return;
}
