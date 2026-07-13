/*
 * Entry: 005c1a65
 * Name: ll_unloadlib
 * Namespace: Global
 * Signature: void ll_unloadlib(void * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl ll_unloadlib(void *param_1)

{
  FreeLibrary(param_1);
  return;
}
