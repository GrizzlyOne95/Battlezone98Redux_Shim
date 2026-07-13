/*
 * Entry: 005b01c0
 * Name: mapping0_free_info
 * Namespace: Global
 * Signature: void mapping0_free_info(void * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl mapping0_free_info(void *param_1)

{
  if (param_1 != (void *)0x0) {
    memset(param_1,0,0xc88);
    free(param_1);
  }
  return;
}
