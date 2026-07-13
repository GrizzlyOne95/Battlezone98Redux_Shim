/*
 * Entry: 0050fc27
 * Name: GLL_Get
 * Namespace: Global
 * Signature: void * GLL_Get(GLL_GenLListType * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __cdecl GLL_Get(GLL_GenLListType *param_1)

{
  int iVar1;
  int iVar2;
  
  Debug_Assert((uint)(param_1 != (GLL_GenLListType *)0x0),0x112,".\\Schedule\\Genllist.c",
               "gll != NULL");
  iVar2 = param_1->pos;
  if (-1 < iVar2) {
    iVar1 = param_1->size;
    if ((((((iVar2 <= iVar1 + 1) && ((iVar2 != 0 || (param_1->curr == (GLL_LinkStruct *)0x0)))) &&
          ((iVar2 != 1 || (param_1->curr == param_1->first)))) &&
         (((iVar2 != iVar1 || (param_1->curr == param_1->last)) &&
          ((iVar2 != iVar1 + 1 || (param_1->curr == (GLL_LinkStruct *)0x0)))))) &&
        ((iVar1 == 0 ||
         ((param_1->first != (GLL_LinkStruct *)0x0 && (param_1->last != (GLL_LinkStruct *)0x0))))))
       && ((iVar2 < 1 || ((iVar1 < iVar2 || (param_1->curr != (GLL_LinkStruct *)0x0)))))) {
      iVar2 = 1;
      goto LAB_0050fcb0;
    }
  }
  iVar2 = 0;
LAB_0050fcb0:
  Debug_Assert(iVar2,0x113,".\\Schedule\\Genllist.c","GLL_Invariant(gll)");
  Debug_Assert((uint)(param_1->size != 0),0x114,".\\Schedule\\Genllist.c","!GLL_Empty(gll)");
  Debug_Assert((uint)(param_1->pos != 0),0x115,".\\Schedule\\Genllist.c","!GLL_OffLeft(gll)");
  if ((param_1->size < param_1->pos) || (param_1->size == 0)) {
    iVar2 = 0;
  }
  else {
    iVar2 = 1;
  }
  Debug_Assert(iVar2,0x116,".\\Schedule\\Genllist.c","!GLL_OffRight(gll)");
  return param_1->curr->elem;
}
