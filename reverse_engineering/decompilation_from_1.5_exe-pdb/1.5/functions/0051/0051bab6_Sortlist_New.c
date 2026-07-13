/*
 * Entry: 0051bab6
 * Name: Sortlist_New
 * Namespace: Global
 * Signature: tag_sortlist * Sortlist_New(int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

tag_sortlist * __cdecl Sortlist_New(int param_1)

{
  tag_sortlist *ptVar1;
  void **ppvVar2;
  double *pdVar3;
  
  ptVar1 = calloc(1,0x10);
  ppvVar2 = calloc(1,param_1 << 2);
  ptVar1->data_list = ppvVar2;
  pdVar3 = calloc(1,param_1 << 3);
  ptVar1->count = 0;
  ptVar1->key_list = pdVar3;
  ptVar1->max_count = param_1;
  return ptVar1;
}
