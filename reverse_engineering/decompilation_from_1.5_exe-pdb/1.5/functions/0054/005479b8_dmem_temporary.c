/*
 * Entry: 005479b8
 * Name: dmem_temporary
 * Namespace: Global
 * Signature: void dmem_temporary(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl dmem_temporary(void)

{
  if (hDefaultTempHeap == (void *)0x0) {
    hDefaultTempHeap = (void *)0x1;
  }
  hDefaultHeap = hDefaultTempHeap;
  return;
}
