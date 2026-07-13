/*
 * Entry: 0050f67b
 * Name: GLL_Destroy
 * Namespace: Global
 * Signature: void GLL_Destroy(GLL_GenLListType * param_1, _func___cdecl_void_void_ptr * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl GLL_Destroy(GLL_GenLListType *param_1,_func___cdecl_void_void_ptr *param_2)

{
  int iVar1;
  GLL_LinkStruct *pGVar2;
  GLL_LinkStruct *_Memory;
  int iVar3;
  
  if (param_1 == (GLL_GenLListType *)0x0) {
    return;
  }
  iVar3 = param_1->pos;
  if (-1 < iVar3) {
    iVar1 = param_1->size;
    if ((((((iVar3 <= iVar1 + 1) && ((iVar3 != 0 || (param_1->curr == (GLL_LinkStruct *)0x0)))) &&
          ((iVar3 != 1 || (param_1->curr == param_1->first)))) &&
         (((iVar3 != iVar1 || (param_1->curr == param_1->last)) &&
          ((iVar3 != iVar1 + 1 || (param_1->curr == (GLL_LinkStruct *)0x0)))))) &&
        ((iVar1 == 0 ||
         ((param_1->first != (GLL_LinkStruct *)0x0 && (param_1->last != (GLL_LinkStruct *)0x0))))))
       && ((iVar3 < 1 || ((iVar1 < iVar3 || (param_1->curr != (GLL_LinkStruct *)0x0)))))) {
      iVar3 = 1;
      goto LAB_0050f6eb;
    }
  }
  iVar3 = 0;
LAB_0050f6eb:
  Debug_Assert(iVar3,0x49,".\\Schedule\\Genllist.c","GLL_Invariant(gll)");
  _Memory = param_1->first;
  while (_Memory != (GLL_LinkStruct *)0x0) {
    pGVar2 = _Memory->next;
    if (param_2 == (_func___cdecl_void_void_ptr *)0xffffffff) {
      free(_Memory->elem);
    }
    else if (param_2 != (_func___cdecl_void_void_ptr *)0x0) {
      (*param_2)(_Memory->elem);
    }
    free(_Memory);
    _Memory = pGVar2;
  }
  free(param_1);
  return;
}
