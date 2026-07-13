/*
 * Entry: 005b2910
 * Name: floor1_free_look
 * Namespace: Global
 * Signature: void floor1_free_look(void * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl floor1_free_look(void *param_1)

{
  if (param_1 != (void *)0x0) {
    memset(param_1,0,0x520);
    free(param_1);
  }
  return;
}
