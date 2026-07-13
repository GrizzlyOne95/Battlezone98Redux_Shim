/*
 * Entry: 0050faa5
 * Name: GLL_Replace
 * Namespace: Global
 * Signature: void * GLL_Replace(GLL_GenLListType * param_1, void * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __cdecl GLL_Replace(GLL_GenLListType *param_1,void *param_2)

{
  int iVar1;
  void *pvVar2;
  int iVar3;
  
  Debug_Assert((uint)(param_1 != (GLL_GenLListType *)0x0),0xff,".\\Schedule\\Genllist.c",
               "gll != NULL");
  iVar3 = param_1->pos;
  if (iVar3 < 0) {
LAB_0050fb2b:
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
    goto LAB_0050fb2b;
    iVar3 = 1;
  }
  Debug_Assert(iVar3,0x100,".\\Schedule\\Genllist.c","GLL_Invariant(gll)");
  Debug_Assert((uint)(param_1->size != 0),0x101,".\\Schedule\\Genllist.c","!GLL_Empty(gll)");
  Debug_Assert((uint)(param_1->pos != 0),0x102,".\\Schedule\\Genllist.c","!GLL_OffLeft(gll)");
  if ((param_1->size < param_1->pos) || (param_1->size == 0)) {
    iVar3 = 0;
  }
  else {
    iVar3 = 1;
  }
  Debug_Assert(iVar3,0x103,".\\Schedule\\Genllist.c","!GLL_OffRight(gll)");
  pvVar2 = param_1->curr->elem;
  param_1->curr->elem = param_2;
  iVar3 = param_1->pos;
  if (-1 < iVar3) {
    iVar1 = param_1->size;
    if (((((iVar3 <= iVar1 + 1) && ((iVar3 != 0 || (param_1->curr == (GLL_LinkStruct *)0x0)))) &&
         ((iVar3 != 1 || (param_1->curr == param_1->first)))) &&
        ((((iVar3 != iVar1 || (param_1->curr == param_1->last)) &&
          ((iVar3 != iVar1 + 1 || (param_1->curr == (GLL_LinkStruct *)0x0)))) &&
         ((iVar1 == 0 ||
          ((param_1->first != (GLL_LinkStruct *)0x0 && (param_1->last != (GLL_LinkStruct *)0x0))))))
        )) && ((iVar3 < 1 || ((iVar1 < iVar3 || (param_1->curr != (GLL_LinkStruct *)0x0)))))) {
      iVar3 = 1;
      goto LAB_0050fc0b;
    }
  }
  iVar3 = 0;
LAB_0050fc0b:
  Debug_Assert(iVar3,0x108,".\\Schedule\\Genllist.c","GLL_Invariant(gll)");
  return pvVar2;
}
