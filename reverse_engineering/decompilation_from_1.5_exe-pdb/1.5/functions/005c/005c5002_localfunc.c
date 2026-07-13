/*
 * Entry: 005c5002
 * Name: localfunc
 * Namespace: Global
 * Signature: void localfunc(LexState * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl localfunc(LexState *param_1)

{
  int in_EAX;
  TString *pTVar1;
  int unaff_ESI;
  TString *unaff_EDI;
  FuncState *pFVar2;
  int iVar3;
  expdesc local_38;
  SemInfo local_20;
  int local_18;
  SemInfo local_10;
  FuncState *local_8;
  
  pFVar2 = *(FuncState **)(in_EAX + 0x30);
  local_8 = pFVar2;
  pTVar1 = str_checkname((LexState *)&unaff_EDI->tsv);
  new_localvar((LexState *)&pTVar1->tsv,unaff_EDI,unaff_ESI);
  local_18 = pFVar2->freereg;
  local_10.ts = (TString *)0xffffffff;
  local_10._4_4_ = 0xffffffff;
  iVar3 = 1;
  local_20.ts = (TString *)0x6;
  luaK_reserveregs(pFVar2,1);
  adjustlocalvars((LexState *)pFVar2,iVar3);
  body((LexState *)&local_38,(expdesc *)0x0,(int)pFVar2,iVar3);
  pFVar2 = local_8;
  luaK_storevar(local_8,(expdesc *)&local_20,&local_38);
  pFVar2->f->locvars[*(ushort *)&pFVar2->upvalues[pFVar2->nactvar + 0x3b].info].startpc = pFVar2->pc
  ;
  return;
}
