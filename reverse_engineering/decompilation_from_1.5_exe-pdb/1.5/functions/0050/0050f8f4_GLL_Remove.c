/*
 * Entry: 0050f8f4
 * Name: GLL_Remove
 * Namespace: Global
 * Signature: void * GLL_Remove(GLL_GenLListType * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __cdecl GLL_Remove(GLL_GenLListType *param_1)

{
  int iVar1;
  GLL_LinkStruct *_Memory;
  void *pvVar2;
  GLL_LinkStruct *pGVar3;
  int iVar4;
  
  Debug_Assert((uint)(param_1 != (GLL_GenLListType *)0x0),0xd2,".\\Schedule\\Genllist.c",
               "gll != NULL");
  iVar4 = param_1->pos;
  if (iVar4 < 0) {
LAB_0050f97a:
    iVar4 = 0;
  }
  else {
    iVar1 = param_1->size;
    if ((((((iVar1 + 1 < iVar4) || ((iVar4 == 0 && (param_1->curr != (GLL_LinkStruct *)0x0)))) ||
          ((iVar4 == 1 && (param_1->curr != param_1->first)))) ||
         (((iVar4 == iVar1 && (param_1->curr != param_1->last)) ||
          ((iVar4 == iVar1 + 1 && (param_1->curr != (GLL_LinkStruct *)0x0)))))) ||
        ((iVar1 != 0 &&
         ((param_1->first == (GLL_LinkStruct *)0x0 || (param_1->last == (GLL_LinkStruct *)0x0))))))
       || ((0 < iVar4 && ((iVar4 <= iVar1 && (param_1->curr == (GLL_LinkStruct *)0x0))))))
    goto LAB_0050f97a;
    iVar4 = 1;
  }
  Debug_Assert(iVar4,0xd3,".\\Schedule\\Genllist.c","GLL_Invariant(gll)");
  Debug_Assert((uint)(param_1->size != 0),0xd4,".\\Schedule\\Genllist.c","!GLL_Empty(gll)");
  Debug_Assert((uint)(param_1->pos != 0),0xd5,".\\Schedule\\Genllist.c","!GLL_OffLeft(gll)");
  if ((param_1->size < param_1->pos) || (param_1->size == 0)) {
    iVar4 = 0;
  }
  else {
    iVar4 = 1;
  }
  Debug_Assert(iVar4,0xd6,".\\Schedule\\Genllist.c","!GLL_OffRight(gll)");
  _Memory = param_1->curr;
  pvVar2 = _Memory->elem;
  if (_Memory->prev == (GLL_LinkStruct *)0x0) {
    param_1->first = _Memory->next;
  }
  else {
    _Memory->prev->next = _Memory->next;
  }
  if (_Memory->next == (GLL_LinkStruct *)0x0) {
    param_1->last = _Memory->prev;
  }
  else {
    _Memory->next->prev = _Memory->prev;
  }
  pGVar3 = _Memory->next;
  param_1->size = param_1->size + -1;
  param_1->curr = pGVar3;
  free(_Memory);
  iVar4 = param_1->pos;
  if (-1 < iVar4) {
    iVar1 = param_1->size;
    if (((((iVar4 <= iVar1 + 1) && ((iVar4 != 0 || (param_1->curr == (GLL_LinkStruct *)0x0)))) &&
         ((iVar4 != 1 || (param_1->curr == param_1->first)))) &&
        ((((iVar4 != iVar1 || (param_1->curr == param_1->last)) &&
          ((iVar4 != iVar1 + 1 || (param_1->curr == (GLL_LinkStruct *)0x0)))) &&
         ((iVar1 == 0 ||
          ((param_1->first != (GLL_LinkStruct *)0x0 && (param_1->last != (GLL_LinkStruct *)0x0))))))
        )) && ((iVar4 < 1 || ((iVar1 < iVar4 || (param_1->curr != (GLL_LinkStruct *)0x0)))))) {
      iVar4 = 1;
      goto LAB_0050fa89;
    }
  }
  iVar4 = 0;
LAB_0050fa89:
  Debug_Assert(iVar4,0xe2,".\\Schedule\\Genllist.c","GLL_Invariant(gll)");
  return pvVar2;
}
