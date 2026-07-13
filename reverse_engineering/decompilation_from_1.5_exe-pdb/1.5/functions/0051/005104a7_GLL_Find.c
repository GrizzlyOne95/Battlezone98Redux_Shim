/*
 * Entry: 005104a7
 * Name: GLL_Find
 * Namespace: Global
 * Signature: int GLL_Find(GLL_GenLListType * param_1, _func___cdecl_int_void_ptr_long * param_2, long param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl
GLL_Find(GLL_GenLListType *param_1,_func___cdecl_int_void_ptr_long *param_2,long param_3)

{
  int iVar1;
  GLL_GenLListType *pGVar2;
  int iVar3;
  GLL_LinkStruct *pGVar4;
  int local_8;
  
  pGVar2 = param_1;
  local_8 = -1;
  Debug_Assert((uint)(param_1 != (GLL_GenLListType *)0x0),0x1be,".\\Schedule\\Genllist.c",
               "gll != NULL");
  iVar3 = param_1->pos;
  if (iVar3 < 0) {
LAB_00510533:
    iVar3 = 0;
  }
  else {
    iVar1 = param_1->size;
    if ((((((iVar1 + 1 < iVar3) || ((iVar3 == 0 && (param_1->curr != (GLL_LinkStruct *)0x0)))) ||
          ((iVar3 == 1 && (param_1->curr != param_1->first)))) ||
         (((iVar3 == iVar1 && (param_1->curr != param_1->last)) ||
          ((iVar3 == iVar1 + 1 && (param_1->curr != (GLL_LinkStruct *)0x0)))))) ||
        ((iVar1 != 0 &&
         ((param_1->first == (GLL_LinkStruct *)0x0 || (param_1->last == (GLL_LinkStruct *)0x0))))))
       || ((0 < iVar3 && ((iVar3 <= iVar1 && (param_1->curr == (GLL_LinkStruct *)0x0))))))
    goto LAB_00510533;
    iVar3 = 1;
  }
  Debug_Assert(iVar3,0x1bf,".\\Schedule\\Genllist.c","GLL_Invariant(gll)");
  pGVar4 = param_1->first;
  param_1 = (GLL_GenLListType *)0x0;
  while ((pGVar4 != (GLL_LinkStruct *)0x0 && (local_8 < 0))) {
    local_8 = (*param_2)(pGVar4->elem,param_3);
    pGVar4 = pGVar4->next;
    param_1 = (GLL_GenLListType *)((int)&param_1->first + 1);
  }
  iVar3 = pGVar2->pos;
  if (-1 < iVar3) {
    iVar1 = pGVar2->size;
    if (((((iVar3 <= iVar1 + 1) && ((iVar3 != 0 || (pGVar2->curr == (GLL_LinkStruct *)0x0)))) &&
         ((iVar3 != 1 || (pGVar2->curr == pGVar2->first)))) &&
        ((((iVar3 != iVar1 || (pGVar2->curr == pGVar2->last)) &&
          ((iVar3 != iVar1 + 1 || (pGVar2->curr == (GLL_LinkStruct *)0x0)))) &&
         ((iVar1 == 0 ||
          ((pGVar2->first != (GLL_LinkStruct *)0x0 && (pGVar2->last != (GLL_LinkStruct *)0x0))))))))
       && ((iVar3 < 1 || ((iVar1 < iVar3 || (pGVar2->curr != (GLL_LinkStruct *)0x0)))))) {
      iVar3 = 1;
      goto LAB_005105d0;
    }
  }
  iVar3 = 0;
LAB_005105d0:
  Debug_Assert(iVar3,0x1c4,".\\Schedule\\Genllist.c","GLL_Invariant(gll)");
  return ~-(uint)(local_8 != 0) & (uint)param_1;
}
