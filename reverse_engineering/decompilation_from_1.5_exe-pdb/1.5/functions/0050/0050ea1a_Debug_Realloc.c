/*
 * Entry: 0050ea1a
 * Name: Debug_Realloc
 * Namespace: Global
 * Signature: void * Debug_Realloc(void * param_1, uint param_2, char * param_3, int param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __cdecl Debug_Realloc(void *param_1,uint param_2,char *param_3,int param_4)

{
  void *pvVar1;
  
  Debug_Assert((int)param_1,0xe7,".\\Schedule\\DR_Debug.c","old_buffer");
  pvVar1 = realloc(param_1,param_2);
  if (pvVar1 != param_1) {
    Debug_Assert((int)pvVar1,0xec,".\\Schedule\\DR_Debug.c","new_buffer");
    counter = counter + 1;
    LogError(-2,"FREE  Address [0x%08lX] [%06d]                 in [%s] @ line [%d]\n");
    counter = counter + 1;
    LogError(-2,"ALLOC Address [0x%08lX] [%06d] size [0x%06X] in [%s] @ line [%d]\n");
  }
  return pvVar1;
}
