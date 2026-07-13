/*
 * Entry: 00478c3e
 * Name: QuickExit
 * Namespace: Global
 * Signature: void QuickExit(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl QuickExit(void)

{
  SetLastSessionFlag();
  cleanup_before_exit();
                    /* WARNING: Subroutine does not return */
  exit(0x29a);
}
