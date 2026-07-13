/*
 * Entry: 0050e7dc
 * Name: Debug_Malloc
 * Namespace: Global
 * Signature: void * Debug_Malloc(uint param_1, char * param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __cdecl Debug_Malloc(uint param_1,char *param_2,int param_3)

{
  void *pvVar1;
  int *piVar2;
  
  pvVar1 = malloc(param_1);
  if (pvVar1 == (void *)0x0) {
    Debug_HeapCheck();
    piVar2 = _errno();
    strerror(*piVar2);
    LogError(-1,"Debug error: Could not malloc %d bytes in source file %s, line %d : %s\n");
  }
  else {
    allocations = allocations + 1;
  }
  counter = counter + 1;
  LogError(-2,"ALLOC Address [0x%08lX] [%06d] size [0x%06X] in [%s] @ line [%d]\n");
  return pvVar1;
}
