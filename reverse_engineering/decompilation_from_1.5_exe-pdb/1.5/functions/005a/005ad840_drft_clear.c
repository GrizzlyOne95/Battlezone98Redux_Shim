/*
 * Entry: 005ad840
 * Name: drft_clear
 * Namespace: Global
 * Signature: void drft_clear(drft_lookup * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl drft_clear(drft_lookup *param_1)

{
  if (param_1 != (drft_lookup *)0x0) {
    if (param_1->trigcache != (float *)0x0) {
      free(param_1->trigcache);
    }
    if (param_1->splitcache != (int *)0x0) {
      free(param_1->splitcache);
    }
    param_1->n = 0;
    param_1->trigcache = (float *)0x0;
    param_1->splitcache = (int *)0x0;
  }
  return;
}
