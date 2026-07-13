/*
 * Entry: 0050e84e
 * Name: Debug_Calloc
 * Namespace: Global
 * Signature: void * Debug_Calloc(uint param_1, uint param_2, char * param_3, int param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __cdecl Debug_Calloc(uint param_1,uint param_2,char *param_3,int param_4)

{
  void *pvVar1;
  int *piVar2;
  
  pvVar1 = calloc(param_1,param_2);
  if (pvVar1 == (void *)0x0) {
    Debug_HeapCheck();
    piVar2 = _errno();
    strerror(*piVar2);
    LogError(-1,
             "Debug error: Could not calloc %d items of size %d bytes in source file %s, line %d : %s\n"
            );
  }
  else {
    allocations = allocations + 1;
  }
  counter = counter + 1;
  LogError(-2,"ALLOC Address [0x%08lX] [%06d] size [0x%06X] in [%s] @ line [%d]\n");
  return pvVar1;
}
