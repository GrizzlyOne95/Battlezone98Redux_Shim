/*
 * Entry: 00484249
 * Name: memalloc
 * Namespace: Global
 * Signature: void * memalloc(uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __cdecl memalloc(uint param_1)

{
  void *pvVar1;
  
  pvVar1 = calloc(1,param_1);
  return pvVar1;
}
