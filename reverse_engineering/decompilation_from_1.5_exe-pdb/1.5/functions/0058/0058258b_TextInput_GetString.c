/*
 * Entry: 0058258b
 * Name: TextInput_GetString
 * Namespace: Global
 * Signature: char * TextInput_GetString(void * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

char * __cdecl TextInput_GetString(void *param_1)

{
  return (char *)(*(int *)(*(int *)((int)param_1 + 8) + 0x108) + 0x10 + *(int *)((int)param_1 + 8));
}
