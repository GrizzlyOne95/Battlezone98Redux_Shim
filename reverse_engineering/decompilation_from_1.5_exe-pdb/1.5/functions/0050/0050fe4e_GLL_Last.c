/*
 * Entry: 0050fe4e
 * Name: GLL_Last
 * Namespace: Global
 * Signature: void GLL_Last(GLL_GenLListType * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl GLL_Last(GLL_GenLListType *param_1)

{
  int iVar1;
  GLL_LinkStruct *pGVar2;
  int iVar3;
  
  Debug_Assert((uint)(param_1 != (GLL_GenLListType *)0x0),0x133,".\\Schedule\\Genllist.c",
               "gll != NULL");
  iVar3 = param_1->pos;
  if (iVar3 < 0) {
LAB_0050fed1:
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
    goto LAB_0050fed1;
    iVar3 = 1;
  }
  Debug_Assert(iVar3,0x134,".\\Schedule\\Genllist.c","GLL_Invariant(gll)");
  pGVar2 = param_1->last;
  if (pGVar2 != (GLL_LinkStruct *)0x0) {
    param_1->curr = pGVar2;
    param_1->pos = param_1->size;
  }
  iVar3 = param_1->pos;
  if (-1 < iVar3) {
    iVar1 = param_1->size;
    if (((((iVar3 <= iVar1 + 1) && ((iVar3 != 0 || (param_1->curr == (GLL_LinkStruct *)0x0)))) &&
         ((iVar3 != 1 || (param_1->curr == param_1->first)))) &&
        ((((iVar3 != iVar1 || (param_1->curr == pGVar2)) &&
          ((iVar3 != iVar1 + 1 || (param_1->curr == (GLL_LinkStruct *)0x0)))) &&
         ((iVar1 == 0 ||
          ((param_1->first != (GLL_LinkStruct *)0x0 && (pGVar2 != (GLL_LinkStruct *)0x0)))))))) &&
       ((iVar3 < 1 || ((iVar1 < iVar3 || (param_1->curr != (GLL_LinkStruct *)0x0)))))) {
      iVar3 = 1;
      goto LAB_0050ff58;
    }
  }
  iVar3 = 0;
LAB_0050ff58:
  Debug_Assert(iVar3,0x13a,".\\Schedule\\Genllist.c","GLL_Invariant(gll)");
  return;
}
