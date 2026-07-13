/*
 * Entry: 005bd529
 * Name: DumpFunction
 * Namespace: Global
 * Signature: void DumpFunction(Proto * param_1, TString * param_2, DumpState * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl DumpFunction(Proto *param_1,TString *param_2,DumpState *param_3)

{
  DumpState *pDVar1;
  DumpState *pDVar2;
  DumpState *pDVar3;
  DumpState *unaff_ESI;
  TString *unaff_EDI;
  DumpState *pDVar4;
  
  DumpString(unaff_EDI,unaff_ESI);
  pDVar1 = (DumpState *)param_1->linedefined;
  DumpInt((int)pDVar1,(DumpState *)&unaff_EDI->tsv);
  pDVar2 = (DumpState *)param_1->lastlinedefined;
  DumpInt((int)pDVar2,pDVar1);
  pDVar1 = (DumpState *)(uint)param_1->nups;
  DumpChar((int)pDVar1,pDVar2);
  pDVar2 = (DumpState *)(uint)param_1->numparams;
  DumpChar((int)pDVar2,pDVar1);
  pDVar1 = (DumpState *)(uint)param_1->is_vararg;
  DumpChar((int)pDVar1,pDVar2);
  pDVar3 = (DumpState *)(uint)param_1->maxstacksize;
  DumpChar((int)pDVar3,pDVar1);
  pDVar1 = (DumpState *)param_1->sizecode;
  pDVar2 = (DumpState *)param_1->code;
  pDVar4 = pDVar1;
  DumpInt((int)pDVar1,pDVar3);
  DumpBlock(pDVar2,(int)pDVar1 << 2,pDVar4);
  DumpConstants((Proto *)param_3,pDVar2);
  DumpDebug((Proto *)&unaff_EDI->tsv,unaff_ESI);
  return;
}
