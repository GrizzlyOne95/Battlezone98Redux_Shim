/*
 * Entry: 00582b46
 * Name: TextInput_Cleanup
 * Namespace: Global
 * Signature: void TextInput_Cleanup(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl TextInput_Cleanup(void)

{
  while (region_list != (wrap_struct *)0x0) {
    TextInput_DestroyRegion(region_list);
  }
  return;
}
