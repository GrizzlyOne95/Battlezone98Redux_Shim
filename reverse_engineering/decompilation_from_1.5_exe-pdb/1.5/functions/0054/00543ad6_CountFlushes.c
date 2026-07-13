/*
 * Entry: 00543ad6
 * Name: CountFlushes
 * Namespace: Global
 * Signature: void CountFlushes(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl CountFlushes(void)

{
  if (D3DTextLoads != 0) {
    D3DTextFlushes = D3DTextFlushes + 1;
  }
  return;
}
