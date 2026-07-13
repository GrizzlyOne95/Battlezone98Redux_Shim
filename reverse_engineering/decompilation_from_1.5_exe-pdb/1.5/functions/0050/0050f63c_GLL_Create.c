/*
 * Entry: 0050f63c
 * Name: GLL_Create
 * Namespace: Global
 * Signature: GLL_GenLListType * GLL_Create(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GLL_GenLListType * __cdecl GLL_Create(void)

{
  GLL_GenLListType *pGVar1;
  
  pGVar1 = calloc(1,0x14);
  if (pGVar1 == (GLL_GenLListType *)0x0) {
    return (GLL_GenLListType *)0x0;
  }
  pGVar1->last = (GLL_LinkStruct *)0x0;
  pGVar1->curr = (GLL_LinkStruct *)0x0;
  pGVar1->first = (GLL_LinkStruct *)0x0;
  pGVar1->pos = 0;
  pGVar1->size = 0;
  Debug_Assert(1,0x39,".\\Schedule\\Genllist.c","GLL_Invariant(gll)");
  return pGVar1;
}
