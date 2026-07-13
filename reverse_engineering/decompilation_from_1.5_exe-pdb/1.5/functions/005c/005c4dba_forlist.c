/*
 * Entry: 005c4dba
 * Name: forlist
 * Namespace: Global
 * Signature: void forlist(LexState * param_1, TString * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl forlist(LexState *param_1,TString *param_2)

{
  TString *in_EAX;
  TString *pTVar1;
  int iVar2;
  TString *pTVar3;
  LexState *pLVar4;
  expdesc *unaff_ESI;
  TString *unaff_EDI;
  int iVar5;
  GCObject *pGVar6;
  char *pcVar7;
  LexState *pLVar8;
  SemInfo local_10;
  GCObject *local_8;
  
  local_8 = in_EAX[3].tsv.next;
  local_10.ts = (TString *)(local_8->p).sizeupvalues;
  pcVar7 = "(for generator)";
  pTVar3 = in_EAX;
  pTVar1 = luaX_newstring((LexState *)&in_EAX->tsv,"(for generator)",0xf);
  new_localvar((LexState *)&pTVar1->tsv,pTVar3,(int)pcVar7);
  pcVar7 = "(for state)";
  pTVar3 = in_EAX;
  pTVar1 = luaX_newstring((LexState *)&in_EAX->tsv,"(for state)",0xb);
  new_localvar((LexState *)&pTVar1->tsv,pTVar3,(int)pcVar7);
  pcVar7 = "(for control)";
  pTVar3 = in_EAX;
  pTVar1 = luaX_newstring((LexState *)&in_EAX->tsv,"(for control)",0xd);
  new_localvar((LexState *)&pTVar1->tsv,pTVar3,(int)pcVar7);
  new_localvar(param_1,pTVar1,(int)pTVar3);
  iVar5 = 4;
  iVar2 = testnext((LexState *)0x2c,(int)param_1);
  while (iVar2 != 0) {
    pTVar3 = str_checkname((LexState *)&unaff_EDI->tsv);
    new_localvar((LexState *)&pTVar3->tsv,unaff_EDI,(int)unaff_ESI);
    iVar5 = iVar5 + 1;
    iVar2 = testnext((LexState *)0x2c,(int)pTVar3);
  }
  checknext((LexState *)&unaff_EDI->tsv,(int)unaff_ESI);
  local_10._4_4_ = *(undefined4 *)&(in_EAX->tsv).tt;
  pLVar8 = (LexState *)&stack0xffffffd8;
  pLVar4 = (LexState *)explist1(pLVar8,(expdesc *)&unaff_EDI->tsv);
  adjust_assign(pLVar4,(int)pLVar8,(int)unaff_EDI,unaff_ESI);
  pGVar6 = local_8;
  luaK_checkstack((FuncState *)&local_8->gch,3);
  forbody((LexState *)local_10.ts,local_10._4_4_,iVar5 + -3,0,(int)pGVar6);
  return;
}
