/*
 * Entry: 005107bc
 * Name: GLL_CircRemove
 * Namespace: Global
 * Signature: void * GLL_CircRemove(GLL_GenLListType * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __cdecl GLL_CircRemove(GLL_GenLListType *param_1)

{
  void *pvVar1;
  
  pvVar1 = GLL_Remove(param_1);
  if ((param_1->size < param_1->pos) || (param_1->size == 0)) {
    GLL_First(param_1);
  }
  return pvVar1;
}
