/*
 * Entry: 005479df
 * Name: dmemcleanup
 * Namespace: Global
 * Signature: void dmemcleanup(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl dmemcleanup(void)

{
  hDefaultTempHeap = (void *)0x0;
  hDefaultHeap = hDefaultProcessHeap;
  return;
}
