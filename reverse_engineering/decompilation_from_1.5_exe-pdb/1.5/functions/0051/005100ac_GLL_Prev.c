/*
 * Entry: 005100ac
 * Name: GLL_Prev
 * Namespace: Global
 * Signature: void GLL_Prev(GLL_GenLListType * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl GLL_Prev(GLL_GenLListType *param_1)

{
  int iVar1;
  int iVar2;
  GLL_LinkStruct *pGVar3;
  
  Debug_Assert((uint)(param_1 != (GLL_GenLListType *)0x0),0x157,".\\Schedule\\Genllist.c",
               "gll != NULL");
  iVar2 = param_1->pos;
  if (iVar2 < 0) {
LAB_0051012f:
    iVar2 = 0;
  }
  else {
    iVar1 = param_1->size;
    if ((((((iVar1 + 1 < iVar2) || ((iVar2 == 0 && (param_1->curr != (GLL_LinkStruct *)0x0)))) ||
          ((iVar2 == 1 && (param_1->curr != param_1->first)))) ||
         (((iVar2 == iVar1 && (param_1->curr != param_1->last)) ||
          ((iVar2 == iVar1 + 1 && (param_1->curr != (GLL_LinkStruct *)0x0)))))) ||
        ((iVar1 != 0 &&
         ((param_1->first == (GLL_LinkStruct *)0x0 || (param_1->last == (GLL_LinkStruct *)0x0))))))
       || ((0 < iVar2 && ((iVar2 <= iVar1 && (param_1->curr == (GLL_LinkStruct *)0x0))))))
    goto LAB_0051012f;
    iVar2 = 1;
  }
  Debug_Assert(iVar2,0x158,".\\Schedule\\Genllist.c","GLL_Invariant(gll)");
  if (param_1->pos != 0) {
    if (param_1->curr == (GLL_LinkStruct *)0x0) {
      pGVar3 = param_1->last;
    }
    else {
      pGVar3 = param_1->curr->prev;
    }
    param_1->curr = pGVar3;
    param_1->pos = param_1->pos + -1;
  }
  iVar2 = param_1->pos;
  if (-1 < iVar2) {
    iVar1 = param_1->size;
    if (((((iVar2 <= iVar1 + 1) && ((iVar2 != 0 || (param_1->curr == (GLL_LinkStruct *)0x0)))) &&
         ((iVar2 != 1 || (param_1->curr == param_1->first)))) &&
        ((((iVar2 != iVar1 || (param_1->curr == param_1->last)) &&
          ((iVar2 != iVar1 + 1 || (param_1->curr == (GLL_LinkStruct *)0x0)))) &&
         ((iVar1 == 0 ||
          ((param_1->first != (GLL_LinkStruct *)0x0 && (param_1->last != (GLL_LinkStruct *)0x0))))))
        )) && ((iVar2 < 1 || ((iVar1 < iVar2 || (param_1->curr != (GLL_LinkStruct *)0x0)))))) {
      iVar2 = 1;
      goto LAB_005101ca;
    }
  }
  iVar2 = 0;
LAB_005101ca:
  Debug_Assert(iVar2,0x15f,".\\Schedule\\Genllist.c","GLL_Invariant(gll)");
  return;
}
