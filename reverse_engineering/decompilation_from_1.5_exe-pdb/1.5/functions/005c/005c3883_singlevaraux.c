/*
 * Entry: 005c3883
 * Name: singlevaraux
 * Namespace: Global
 * Signature: int singlevaraux(FuncState * param_1, TString * param_2, expdesc * param_3, int param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl singlevaraux(FuncState *param_1,TString *param_2,expdesc *param_3,int param_4)

{
  int iVar1;
  int iVar2;
  uchar *puVar3;
  BlockCnt *pBVar4;
  expdesc *unaff_EDI;
  
  if (param_1 == (FuncState *)0x0) {
    param_3->t = -1;
    param_3->f = -1;
    param_3->k = VGLOBAL;
    (param_3->u).s.info = 0xff;
    iVar2 = 8;
  }
  else {
    iVar1 = param_1->nactvar - 1;
    if (-1 < iVar1) {
      puVar3 = &param_1->upvalues[param_1->nactvar + 0x3b].info;
      do {
        if (param_2 == param_1->f->locvars[*(ushort *)puVar3].varname) goto LAB_005c38db;
        iVar1 = iVar1 + -1;
        puVar3 = puVar3 + -2;
      } while (-1 < iVar1);
    }
    iVar1 = -1;
LAB_005c38db:
    if (iVar1 < 0) {
      iVar2 = singlevaraux(param_1->prev,param_2,param_3,0);
      if (iVar2 != 8) {
        iVar1 = indexupvalue((FuncState *)&param_2->tsv,(TString *)param_3,unaff_EDI);
        (param_3->u).s.info = iVar1;
        iVar2 = 7;
        param_3->k = VUPVAL;
      }
    }
    else {
      param_3->t = -1;
      param_3->f = -1;
      iVar2 = 6;
      param_3->k = VLOCAL;
      (param_3->u).s.info = iVar1;
      if ((param_4 == 0) && (pBVar4 = param_1->bl, pBVar4 != (BlockCnt *)0x0)) {
        do {
          if ((int)(uint)pBVar4->nactvar <= iVar1) break;
          pBVar4 = pBVar4->previous;
        } while (pBVar4 != (BlockCnt *)0x0);
        if (pBVar4 != (BlockCnt *)0x0) {
          pBVar4->upval = '\x01';
        }
      }
    }
  }
  return iVar2;
}
