/*
 * Entry: 00510778
 * Name: GLL_OrderedInsert
 * Namespace: Global
 * Signature: int GLL_OrderedInsert(GLL_GenLListType * param_1, void * param_2, _func___cdecl_int_void_ptr_void_ptr * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl
GLL_OrderedInsert(GLL_GenLListType *param_1,void *param_2,
                 _func___cdecl_int_void_ptr_void_ptr *param_3)

{
  void *pvVar1;
  int iVar2;
  
  GLL_First(param_1);
  while ((param_1->pos <= param_1->size && (param_1->size != 0))) {
    pvVar1 = GLL_Get(param_1);
    iVar2 = (*param_3)(param_2,pvVar1);
    if (iVar2 < 1) break;
    GLL_Next(param_1);
  }
  iVar2 = GLL_Insert(param_1,param_2);
  return iVar2;
}
