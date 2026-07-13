/*
 * Entry: 00455250
 * Name: ReloadPathing
 * Namespace: Global
 * Signature: void ReloadPathing(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl ReloadPathing(void)

{
  stripSeqNo = 0;
  BuildStrips();
  return;
}
