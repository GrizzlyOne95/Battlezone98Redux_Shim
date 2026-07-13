/*
 * Entry: 005b4b70
 * Name: floor0_free_info
 * Namespace: Global
 * Signature: void floor0_free_info(void * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl floor0_free_info(void *param_1)

{
  if (param_1 != (void *)0x0) {
    memset(param_1,0,0x60);
    free(param_1);
  }
  return;
}
