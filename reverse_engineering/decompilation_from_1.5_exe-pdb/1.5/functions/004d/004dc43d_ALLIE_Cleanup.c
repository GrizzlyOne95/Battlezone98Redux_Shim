/*
 * Entry: 004dc43d
 * Name: ALLIE_Cleanup
 * Namespace: Global
 * Signature: void ALLIE_Cleanup(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl ALLIE_Cleanup(void)

{
  TextInput_DestroyRegion(allie_entry);
  allie_entry = (void *)0x0;
  return;
}
