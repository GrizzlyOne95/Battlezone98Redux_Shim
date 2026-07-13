/*
 * Entry: 0054ec8e
 * Name: LastResource
 * Namespace: Global
 * Signature: void LastResource(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl LastResource(void)

{
  FreeCache();
  zixClearPaths();
  zfsMemoryCleanup();
  return;
}
