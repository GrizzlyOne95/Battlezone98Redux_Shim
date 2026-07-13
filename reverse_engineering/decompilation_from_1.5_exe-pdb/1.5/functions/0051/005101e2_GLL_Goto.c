/*
 * Entry: 005101e2
 * Name: GLL_Goto
 * Namespace: Global
 * Signature: void GLL_Goto(GLL_GenLListType * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl GLL_Goto(GLL_GenLListType *param_1,int param_2)

{
  int iVar1;
  int iVar2;
  GLL_LinkStruct *pGVar3;
  GLL_LinkStruct *pGVar4;
  int iVar5;
  
  Debug_Assert((uint)(param_1 != (GLL_GenLListType *)0x0),0x16b,".\\Schedule\\Genllist.c",
               "gll != NULL");
  iVar1 = param_1->pos;
  if (iVar1 < 0) {
LAB_00510265:
    iVar1 = 0;
  }
  else {
    iVar2 = param_1->size;
    if ((((((iVar2 + 1 < iVar1) || ((iVar1 == 0 && (param_1->curr != (GLL_LinkStruct *)0x0)))) ||
          ((iVar1 == 1 && (param_1->curr != param_1->first)))) ||
         (((iVar1 == iVar2 && (param_1->curr != param_1->last)) ||
          ((iVar1 == iVar2 + 1 && (param_1->curr != (GLL_LinkStruct *)0x0)))))) ||
        ((iVar2 != 0 &&
         ((param_1->first == (GLL_LinkStruct *)0x0 || (param_1->last == (GLL_LinkStruct *)0x0))))))
       || ((0 < iVar1 && ((iVar1 <= iVar2 && (param_1->curr == (GLL_LinkStruct *)0x0))))))
    goto LAB_00510265;
    iVar1 = 1;
  }
  Debug_Assert(iVar1,0x16c,".\\Schedule\\Genllist.c","GLL_Invariant(gll)");
  iVar1 = param_1->pos;
  iVar2 = param_2 - iVar1;
  if (iVar2 != 0) {
    if (iVar2 < 1) {
      if (-1 < iVar2) goto LAB_005102ef;
      if (iVar1 == 0) {
        return;
      }
      pGVar4 = param_1->curr;
      if (pGVar4 == (GLL_LinkStruct *)0x0) {
        pGVar4 = param_1->last;
        iVar1 = iVar1 + -1;
        iVar2 = iVar2 + 1;
      }
      iVar5 = 0;
      pGVar3 = pGVar4;
      if (iVar2 < 0) {
        do {
          pGVar4 = (GLL_LinkStruct *)0x0;
          if (pGVar3 == (GLL_LinkStruct *)0x0) break;
          pGVar4 = pGVar3->prev;
          iVar1 = iVar1 + -1;
          iVar5 = iVar5 + -1;
          pGVar3 = pGVar4;
        } while (iVar2 < iVar5);
      }
    }
    else {
      if (param_1->size < iVar1) {
        return;
      }
      if (param_1->size == 0) {
        return;
      }
      pGVar4 = param_1->curr;
      if (pGVar4 == (GLL_LinkStruct *)0x0) {
        pGVar4 = param_1->first;
        iVar1 = iVar1 + 1;
        iVar2 = iVar2 + -1;
      }
      iVar5 = 0;
      pGVar3 = pGVar4;
      if (0 < iVar2) {
        do {
          pGVar4 = (GLL_LinkStruct *)0x0;
          if (pGVar3 == (GLL_LinkStruct *)0x0) break;
          pGVar4 = pGVar3->next;
          iVar1 = iVar1 + 1;
          iVar5 = iVar5 + 1;
          pGVar3 = pGVar4;
        } while (iVar5 < iVar2);
      }
    }
    param_1->pos = iVar1;
    param_1->curr = pGVar4;
  }
LAB_005102ef:
  iVar1 = param_1->pos;
  if (-1 < iVar1) {
    iVar2 = param_1->size;
    if (((((iVar1 <= iVar2 + 1) && ((iVar1 != 0 || (param_1->curr == (GLL_LinkStruct *)0x0)))) &&
         ((iVar1 != 1 || (param_1->curr == param_1->first)))) &&
        ((((iVar1 != iVar2 || (param_1->curr == param_1->last)) &&
          ((iVar1 != iVar2 + 1 || (param_1->curr == (GLL_LinkStruct *)0x0)))) &&
         ((iVar2 == 0 ||
          ((param_1->first != (GLL_LinkStruct *)0x0 && (param_1->last != (GLL_LinkStruct *)0x0))))))
        )) && ((iVar1 < 1 || ((iVar2 < iVar1 || (param_1->curr != (GLL_LinkStruct *)0x0)))))) {
      iVar1 = 1;
      goto LAB_0051034c;
    }
  }
  iVar1 = 0;
LAB_0051034c:
  Debug_Assert(iVar1,0x195,".\\Schedule\\Genllist.c","GLL_Invariant(gll)");
  return;
}
