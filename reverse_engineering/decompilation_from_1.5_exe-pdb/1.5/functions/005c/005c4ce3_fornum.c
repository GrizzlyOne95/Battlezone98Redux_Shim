/*
 * Entry: 005c4ce3
 * Name: fornum
 * Namespace: Global
 * Signature: void fornum(LexState * param_1, TString * param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl fornum(LexState *param_1,TString *param_2,int param_3)

{
  GCObject *pGVar1;
  LexState *pLVar2;
  TString *in_EAX;
  TString *pTVar3;
  TString *pTVar4;
  int iVar5;
  uint uVar6;
  LexState *unaff_EDI;
  char *pcVar7;
  
  pGVar1 = in_EAX[3].tsv.next;
  pLVar2 = (LexState *)(pGVar1->th).end_ci;
  pcVar7 = "(for index)";
  pTVar4 = in_EAX;
  pTVar3 = luaX_newstring((LexState *)&in_EAX->tsv,"(for index)",0xb);
  new_localvar((LexState *)&pTVar3->tsv,pTVar4,(int)pcVar7);
  pcVar7 = "(for limit)";
  pTVar4 = in_EAX;
  pTVar3 = luaX_newstring((LexState *)&in_EAX->tsv,"(for limit)",0xb);
  new_localvar((LexState *)&pTVar3->tsv,pTVar4,(int)pcVar7);
  pcVar7 = "(for step)";
  pTVar4 = luaX_newstring((LexState *)&in_EAX->tsv,"(for step)",10);
  new_localvar((LexState *)&pTVar4->tsv,in_EAX,(int)pcVar7);
  new_localvar(param_1,pTVar4,(int)in_EAX);
  checknext(param_1,(int)pTVar4);
  exp1(param_1);
  checknext(param_1,(int)pTVar4);
  exp1(param_1);
  iVar5 = testnext((LexState *)0x2c,(int)param_1);
  if (iVar5 == 0) {
    uVar6 = luaK_numberK((FuncState *)&pGVar1->gch,(double)CONCAT44(unaff_EDI,0x3ff00000));
    luaK_codeABx((FuncState *)&pGVar1->gch,OP_LOADK,(pGVar1->p).sizeupvalues,uVar6);
    luaK_reserveregs((FuncState *)&pGVar1->gch,1);
  }
  else {
    exp1(unaff_EDI);
  }
  forbody(pLVar2,(int)param_2,1,1,(int)unaff_EDI);
  return;
}
