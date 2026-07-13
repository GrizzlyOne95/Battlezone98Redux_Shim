/*
 * Entry: 005c3a5e
 * Name: pushclosure
 * Namespace: Global
 * Signature: void pushclosure(LexState * param_1, FuncState * param_2, expdesc * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl pushclosure(LexState *param_1,FuncState *param_2,expdesc *param_3)

{
  int *piVar1;
  FuncState *pFVar2;
  GCObject *pGVar3;
  Node *pNVar4;
  int iVar5;
  upvaldesc *puVar6;
  
  pFVar2 = param_1->fs;
  pGVar3 = (GCObject *)pFVar2->f;
  piVar1 = &(pGVar3->p).sizep;
  iVar5 = *piVar1;
  if (iVar5 < pFVar2->np + 1) {
    pNVar4 = luaM_growaux_(param_1->L,(pGVar3->h).node,piVar1,4,0x3ffff,"constant table overflow");
    (pGVar3->h).node = pNVar4;
  }
  for (; iVar5 < *piVar1; iVar5 = iVar5 + 1) {
    *(undefined4 *)((int)&(((pGVar3->h).node)->i_val).value + iVar5 * 4) = 0;
  }
  *(Proto **)((int)&(((pGVar3->h).node)->i_val).value + pFVar2->np * 4) = param_2->f;
  pFVar2->np = pFVar2->np + 1;
  if ((((((GCObject *)param_2->f)->gch).marked & 3) != 0) && (((pGVar3->gch).marked & 4) != 0)) {
    luaC_barrierf(param_1->L,pGVar3,(GCObject *)param_2->f);
  }
  iVar5 = luaK_codeABx(pFVar2,OP_CLOSURE,0,pFVar2->np - 1);
  param_3->t = -1;
  param_3->f = -1;
  param_1 = (LexState *)0x0;
  param_3->k = VRELOCABLE;
  (param_3->u).s.info = iVar5;
  if (param_2->f->nups != '\0') {
    puVar6 = param_2->upvalues;
    do {
      luaK_codeABC(pFVar2,-(uint)(puVar6->k != '\x06') & OP_GETUPVAL,0,(uint)puVar6->info,0);
      param_1 = (LexState *)((int)&param_1->current + 1);
      puVar6 = puVar6 + 1;
    } while ((int)param_1 < (int)(uint)param_2->f->nups);
  }
  return;
}
