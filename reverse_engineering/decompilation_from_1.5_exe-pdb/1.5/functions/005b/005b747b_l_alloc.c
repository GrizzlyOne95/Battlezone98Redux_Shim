/*
 * Entry: 005b747b
 * Name: l_alloc
 * Namespace: Global
 * Signature: void * l_alloc(void * param_1, void * param_2, uint param_3, uint param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __cdecl l_alloc(void *param_1,void *param_2,uint param_3,uint param_4)

{
  void *pvVar1;
  
  if (param_4 == 0) {
    free(param_2);
    return (void *)0x0;
  }
  pvVar1 = realloc(param_2,param_4);
  return pvVar1;
}
