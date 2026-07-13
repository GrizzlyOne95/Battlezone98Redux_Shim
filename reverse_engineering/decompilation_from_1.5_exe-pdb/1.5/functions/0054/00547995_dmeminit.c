/*
 * Entry: 00547995
 * Name: dmeminit
 * Namespace: Global
 * Signature: void dmeminit(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl dmeminit(void)

{
  hDefaultProcessHeap = GetProcessHeap();
  hDefaultTempHeap = (void *)0x0;
  hDefaultHeap = hDefaultProcessHeap;
  return;
}
