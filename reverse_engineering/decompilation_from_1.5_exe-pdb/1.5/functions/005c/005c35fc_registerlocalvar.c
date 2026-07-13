/*
 * Entry: 005c35fc
 * Name: registerlocalvar
 * Namespace: Global
 * Signature: int registerlocalvar(LexState * param_1, TString * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl registerlocalvar(LexState *param_1,TString *param_2)

{
  int *piVar1;
  short sVar2;
  FuncState *pFVar3;
  GCObject *pGVar4;
  GCObject *pGVar5;
  int iVar6;
  int iVar7;
  
  pFVar3 = param_1->fs;
  pGVar4 = (GCObject *)pFVar3->f;
  piVar1 = &(pGVar4->p).sizelocvars;
  iVar6 = *piVar1;
  if (iVar6 < pFVar3->nlocvars + 1) {
    pGVar5 = luaM_growaux_(param_1->L,(pGVar4->h).gclist,piVar1,0xc,0x7fff,
                           "too many local variables");
    (pGVar4->h).gclist = pGVar5;
  }
  if (iVar6 < *piVar1) {
    iVar7 = iVar6 * 0xc;
    do {
      *(undefined4 *)(iVar7 + (int)(pGVar4->h).gclist) = 0;
      iVar6 = iVar6 + 1;
      iVar7 = iVar7 + 0xc;
    } while (iVar6 < *piVar1);
  }
  *(TString **)(pFVar3->nlocvars * 0xc + (int)(pGVar4->h).gclist) = param_2;
  if ((((param_2->tsv).marked & 3) != 0) && (((pGVar4->gch).marked & 4) != 0)) {
    luaC_barrierf(param_1->L,pGVar4,(GCObject *)param_2);
  }
  sVar2 = pFVar3->nlocvars;
  pFVar3->nlocvars = sVar2 + 1;
  return (int)sVar2;
}
