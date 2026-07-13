/*
 * Entry: 0054fbde
 * Name: Scroll_Cleanup
 * Namespace: Global
 * Signature: void Scroll_Cleanup(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Scroll_Cleanup(void)

{
  while (region_list != (wrap_struct *)0x0) {
    Scroll_DestroyRegion(region_list);
  }
  return;
}
