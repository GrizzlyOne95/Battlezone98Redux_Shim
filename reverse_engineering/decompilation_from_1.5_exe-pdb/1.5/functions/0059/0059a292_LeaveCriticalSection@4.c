/*
 * Entry: 0059a292
 * Name: _LeaveCriticalSection@4
 * Namespace: Global
 * Signature: void _LeaveCriticalSection@4(LPCRITICAL_SECTION lpCriticalSection)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void _LeaveCriticalSection_4(LPCRITICAL_SECTION lpCriticalSection)

{
                    /* WARNING: Could not recover jumptable at 0x0059a292. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  LeaveCriticalSection(lpCriticalSection);
  return;
}
