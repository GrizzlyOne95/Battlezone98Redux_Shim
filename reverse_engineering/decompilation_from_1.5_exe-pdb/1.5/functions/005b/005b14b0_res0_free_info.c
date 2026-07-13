/*
 * Entry: 005b14b0
 * Name: res0_free_info
 * Namespace: Global
 * Signature: void res0_free_info(void * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl res0_free_info(void *param_1)

{
  if (param_1 != (void *)0x0) {
    memset(param_1,0,0xb18);
    free(param_1);
  }
  return;
}
