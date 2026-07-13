/*
 * Entry: 005105f5
 * Name: GLL_Insert
 * Namespace: Global
 * Signature: int GLL_Insert(GLL_GenLListType * param_1, void * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl GLL_Insert(GLL_GenLListType *param_1,void *param_2)

{
  int iVar1;
  int iVar2;
  GLL_LinkStruct *pGVar3;
  int iVar4;
  
  Debug_Assert((uint)(param_1 != (GLL_GenLListType *)0x0),99,".\\Schedule\\Genllist.c","gll != NULL"
              );
  iVar2 = param_1->pos;
  if (iVar2 < 0) {
LAB_00510676:
    iVar4 = 0;
  }
  else {
    iVar1 = param_1->size;
    if ((((iVar1 + 1 < iVar2) || ((iVar2 == 0 && (param_1->curr != (GLL_LinkStruct *)0x0)))) ||
        ((iVar2 == 1 && (param_1->curr != param_1->first)))) ||
       (((((iVar2 == iVar1 && (param_1->curr != param_1->last)) ||
          ((iVar2 == iVar1 + 1 && (param_1->curr != (GLL_LinkStruct *)0x0)))) ||
         ((iVar1 != 0 &&
          ((param_1->first == (GLL_LinkStruct *)0x0 || (param_1->last == (GLL_LinkStruct *)0x0))))))
        || ((iVar4 = 1, 0 < iVar2 && ((iVar2 <= iVar1 && (param_1->curr == (GLL_LinkStruct *)0x0))))
           )))) goto LAB_00510676;
  }
  Debug_Assert(iVar4,100,".\\Schedule\\Genllist.c","GLL_Invariant(gll)");
  if ((param_1->pos == 0) && (param_1->size != 0)) {
    iVar2 = GLL_Add(param_1,param_2);
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
    param_1->pos = 1;
  }
  else {
    if (param_1->pos <= param_1->size) {
      pGVar3->prev = param_1->curr->prev;
      pGVar3->next = param_1->curr;
      param_1->curr->prev = pGVar3;
      if (pGVar3->prev == (GLL_LinkStruct *)0x0) {
        param_1->first = pGVar3;
      }
      else {
        pGVar3->prev->next = pGVar3;
      }
      goto LAB_00510713;
    }
    param_1->last->next = pGVar3;
    pGVar3->prev = param_1->last;
    pGVar3->next = (GLL_LinkStruct *)0x0;
  }
  param_1->last = pGVar3;
LAB_00510713:
  param_1->size = param_1->size + 1;
  iVar2 = param_1->pos;
  iVar1 = param_1->size;
  param_1->curr = pGVar3;
  if (((((((iVar2 < 0) || (iVar1 + 1 < iVar2)) || (iVar2 == 0)) ||
        ((iVar2 == 1 && (pGVar3 != param_1->first)))) ||
       ((iVar2 == iVar1 && (pGVar3 != param_1->last)))) || (iVar2 == iVar1 + 1)) ||
     ((param_1->size != 0 &&
      ((param_1->first == (GLL_LinkStruct *)0x0 || (param_1->last == (GLL_LinkStruct *)0x0)))))) {
    iVar2 = 0;
  }
  else {
    iVar2 = 1;
  }
  Debug_Assert(iVar2,0x81,".\\Schedule\\Genllist.c","GLL_Invariant(gll)");
  return 0;
}
