/*
 * Entry: 0050ff74
 * Name: GLL_Next
 * Namespace: Global
 * Signature: void GLL_Next(GLL_GenLListType * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl GLL_Next(GLL_GenLListType *param_1)

{
  int iVar1;
  int iVar2;
  GLL_LinkStruct *pGVar3;
  
  Debug_Assert((uint)(param_1 != (GLL_GenLListType *)0x0),0x145,".\\Schedule\\Genllist.c",
               "gll != NULL");
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
      goto LAB_0050fff9;
    }
  }
  iVar2 = 0;
LAB_0050fff9:
  Debug_Assert(iVar2,0x146,".\\Schedule\\Genllist.c","GLL_Invariant(gll)");
  iVar2 = param_1->size;
  if ((param_1->pos <= iVar2) && (iVar2 != 0)) {
    if (param_1->curr == (GLL_LinkStruct *)0x0) {
      pGVar3 = param_1->first;
    }
    else {
      pGVar3 = param_1->curr->next;
    }
    param_1->curr = pGVar3;
    param_1->pos = param_1->pos + 1;
  }
  iVar1 = param_1->pos;
  if (((((((iVar1 < 0) || (iVar2 + 1 < iVar1)) ||
         ((iVar1 == 0 && (param_1->curr != (GLL_LinkStruct *)0x0)))) ||
        ((iVar1 == 1 && (param_1->curr != param_1->first)))) ||
       ((iVar1 == iVar2 && (param_1->curr != param_1->last)))) ||
      (((iVar1 == iVar2 + 1 && (param_1->curr != (GLL_LinkStruct *)0x0)) ||
       ((iVar2 != 0 &&
        ((param_1->first == (GLL_LinkStruct *)0x0 || (param_1->last == (GLL_LinkStruct *)0x0))))))))
     || ((0 < iVar1 && ((iVar1 <= iVar2 && (param_1->curr == (GLL_LinkStruct *)0x0)))))) {
    iVar2 = 0;
  }
  else {
    iVar2 = 1;
  }
  Debug_Assert(iVar2,0x14d,".\\Schedule\\Genllist.c","GLL_Invariant(gll)");
  return;
}
