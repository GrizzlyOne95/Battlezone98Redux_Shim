/*
 * Entry: 005b28e0
 * Name: floor1_free_info
 * Namespace: Global
 * Signature: void floor1_free_info(void * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl floor1_free_info(void *param_1)

{
  if (param_1 != (void *)0x0) {
    memset(param_1,0,0x460);
    free(param_1);
  }
  return;
}
