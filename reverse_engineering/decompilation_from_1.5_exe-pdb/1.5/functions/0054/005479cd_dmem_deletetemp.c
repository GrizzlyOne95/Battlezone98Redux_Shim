/*
 * Entry: 005479cd
 * Name: dmem_deletetemp
 * Namespace: Global
 * Signature: void dmem_deletetemp(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl dmem_deletetemp(void)

{
  hDefaultTempHeap = (void *)0x0;
  hDefaultHeap = hDefaultProcessHeap;
  return;
}
