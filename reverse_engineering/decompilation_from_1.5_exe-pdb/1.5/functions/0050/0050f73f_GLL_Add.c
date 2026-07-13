/*
 * Entry: 0050f73f
 * Name: GLL_Add
 * Namespace: Global
 * Signature: int GLL_Add(GLL_GenLListType * param_1, void * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl GLL_Add(GLL_GenLListType *param_1,void *param_2)

{
  int iVar1;
  int iVar2;
  GLL_LinkStruct *pGVar3;
  
  Debug_Assert((uint)(param_1 != (GLL_GenLListType *)0x0),0x91,".\\Schedule\\Genllist.c",
               "gll != NULL");
  iVar2 = param_1->pos;
  if (iVar2 < 0) {
LAB_0050f7c2:
    iVar2 = 0;
  }
  else {
    iVar1 = param_1->size;
    if ((((iVar1 + 1 < iVar2) || ((iVar2 == 0 && (param_1->curr != (GLL_LinkStruct *)0x0)))) ||
        ((iVar2 == 1 && (param_1->curr != param_1->first)))) ||
       (((((iVar2 == iVar1 && (param_1->curr != param_1->last)) ||
          ((iVar2 == iVar1 + 1 && (param_1->curr != (GLL_LinkStruct *)0x0)))) ||
         ((iVar1 != 0 &&
          ((param_1->first == (GLL_LinkStruct *)0x0 || (param_1->last == (GLL_LinkStruct *)0x0))))))
        || ((0 < iVar2 && ((iVar2 <= iVar1 && (param_1->curr == (GLL_LinkStruct *)0x0))))))))
    goto LAB_0050f7c2;
    iVar2 = 1;
  }
  Debug_Assert(iVar2,0x92,".\\Schedule\\Genllist.c","GLL_Invariant(gll)");
  iVar2 = param_1->size;
  if (((iVar2 < param_1->pos) || (iVar2 == 0)) && (iVar2 != 0)) {
    iVar2 = 0;
  }
  else {
    iVar2 = 1;
  }
  Debug_Assert(iVar2,0x93,".\\Schedule\\Genllist.c",
               "(GLL_OffRight(gll) != TRUE) || (GLL_Empty(gll))");
  iVar2 = param_1->size;
  if (((iVar2 < param_1->pos) || (iVar2 == 0)) && (iVar2 != 0)) {
    iVar2 = GLL_Insert(param_1,param_2);
    return iVar2;
  }
  pGVar3 = calloc(1,0xc);
  if (pGVar3 == (GLL_LinkStruct *)0x0) {
    return 1;
  }
  pGVar3->elem = param_2;
  if (param_1->size == 0) {
    pGVar3->next = (GLL_LinkStruct *)0x0;
    pGVar3->prev = (GLL_LinkStruct *)0x0;
    param_1->first = pGVar3;
    param_1->pos = 0;
  }
  else {
    if (param_1->pos == 0) {
      param_1->first->prev = pGVar3;
      pGVar3->prev = (GLL_LinkStruct *)0x0;
      pGVar3->next = param_1->first;
      param_1->first = pGVar3;
      goto LAB_0050f85a;
    }
    pGVar3->prev = param_1->curr;
    pGVar3->next = param_1->curr->next;
    param_1->curr->next = pGVar3;
    if (pGVar3->next != (GLL_LinkStruct *)0x0) {
      pGVar3->next->prev = pGVar3;
      goto LAB_0050f85a;
    }
  }
  param_1->last = pGVar3;
LAB_0050f85a:
  param_1->pos = param_1->pos + 1;
  iVar2 = param_1->pos;
  param_1->size = param_1->size + 1;
  iVar1 = param_1->size;
  param_1->curr = pGVar3;
  if ((((iVar2 < 0) || (iVar1 + 1 < iVar2)) ||
      ((iVar2 == 0 || ((iVar2 == 1 && (pGVar3 != param_1->first)))))) ||
     ((((iVar2 == iVar1 && (pGVar3 != param_1->last)) || (iVar2 == iVar1 + 1)) ||
      ((param_1->size != 0 &&
       ((param_1->first == (GLL_LinkStruct *)0x0 || (param_1->last == (GLL_LinkStruct *)0x0))))))))
  {
    iVar2 = 0;
  }
  else {
    iVar2 = 1;
  }
  Debug_Assert(iVar2,0xb1,".\\Schedule\\Genllist.c","GLL_Invariant(gll)");
  return 0;
}
