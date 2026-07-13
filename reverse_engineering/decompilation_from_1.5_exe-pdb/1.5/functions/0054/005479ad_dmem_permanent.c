/*
 * Entry: 005479ad
 * Name: dmem_permanent
 * Namespace: Global
 * Signature: void dmem_permanent(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl dmem_permanent(void)

{
  hDefaultHeap = hDefaultProcessHeap;
  return;
}
