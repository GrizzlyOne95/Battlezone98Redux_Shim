/*
 * Entry: 004839d2
 * Name: MCmemalloc
 * Namespace: Global
 * Signature: void * MCmemalloc(MULTICACHE * param_1, uint param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __cdecl MCmemalloc(MULTICACHE *param_1,uint param_2)

{
  void *pvVar1;
  
  pvVar1 = calloc(1,param_2);
  return pvVar1;
}
