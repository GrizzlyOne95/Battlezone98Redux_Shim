/*
 * Entry: 0050e8ca
 * Name: Debug_Free
 * Namespace: Global
 * Signature: void Debug_Free(void * * param_1, char * param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Debug_Free(void **param_1,char *param_2,int param_3)

{
  if (param_1 == (void **)0x0) {
    LogError(-1,"FREE  NULL??? [0x%08lX] [%06d] in [%s] @ line [%d]\n");
  }
  else {
    counter = counter + 1;
    LogError(-2,"FREE  Address [0x%08lX] [%06d]                 in [%s] @ line [%d]\n");
    if (*param_1 != (void *)0x0) {
      free(*param_1);
      *param_1 = (void *)0x0;
      allocations = allocations + -1;
    }
  }
  return;
}
