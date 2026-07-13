/*
 * Entry: 00510368
 * Name: GLL_Traverse
 * Namespace: Global
 * Signature: int GLL_Traverse(GLL_GenLListType * param_1, _func___cdecl_int_void_ptr_int * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl GLL_Traverse(GLL_GenLListType *param_1,_func___cdecl_int_void_ptr_int *param_2)

{
  GLL_LinkStruct *pGVar1;
  int iVar2;
  int iVar3;
  int local_8;
  
  local_8 = 0;
  Debug_Assert((uint)(param_1 != (GLL_GenLListType *)0x0),0x1a9,".\\Schedule\\Genllist.c",
               "gll != NULL");
  iVar2 = param_1->pos;
  if (iVar2 < 0) {
LAB_005103f4:
    iVar2 = 0;
  }
  else {
    iVar3 = param_1->size;
    if ((((((iVar3 + 1 < iVar2) || ((iVar2 == 0 && (param_1->curr != (GLL_LinkStruct *)0x0)))) ||
          ((iVar2 == 1 && (param_1->curr != param_1->first)))) ||
         (((iVar2 == iVar3 && (param_1->curr != param_1->last)) ||
          ((iVar2 == iVar3 + 1 && (param_1->curr != (GLL_LinkStruct *)0x0)))))) ||
        ((iVar3 != 0 &&
         ((param_1->first == (GLL_LinkStruct *)0x0 || (param_1->last == (GLL_LinkStruct *)0x0))))))
       || ((0 < iVar2 && ((iVar2 <= iVar3 && (param_1->curr == (GLL_LinkStruct *)0x0))))))
    goto LAB_005103f4;
    iVar2 = 1;
  }
  Debug_Assert(iVar2,0x1aa,".\\Schedule\\Genllist.c","GLL_Invariant(gll)");
  iVar2 = 1;
  for (pGVar1 = param_1->first; pGVar1 != (GLL_LinkStruct *)0x0; pGVar1 = pGVar1->next) {
    iVar3 = (*param_2)(pGVar1->elem,iVar2);
    local_8 = local_8 + iVar3;
    iVar2 = iVar2 + 1;
  }
  iVar2 = param_1->pos;
  if (-1 < iVar2) {
    iVar3 = param_1->size;
    if (((((iVar2 <= iVar3 + 1) && ((iVar2 != 0 || (param_1->curr == (GLL_LinkStruct *)0x0)))) &&
         ((iVar2 != 1 || (param_1->curr == param_1->first)))) &&
        ((((iVar2 != iVar3 || (param_1->curr == param_1->last)) &&
          ((iVar2 != iVar3 + 1 || (param_1->curr == (GLL_LinkStruct *)0x0)))) &&
         ((iVar3 == 0 ||
          ((param_1->first != (GLL_LinkStruct *)0x0 && (param_1->last != (GLL_LinkStruct *)0x0))))))
        )) && ((iVar2 < 1 || ((iVar3 < iVar2 || (param_1->curr != (GLL_LinkStruct *)0x0)))))) {
      iVar2 = 1;
      goto LAB_00510487;
    }
  }
  iVar2 = 0;
LAB_00510487:
  Debug_Assert(iVar2,0x1af,".\\Schedule\\Genllist.c","GLL_Invariant(gll)");
  return local_8;
}
