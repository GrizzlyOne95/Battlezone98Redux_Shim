/*
 * Entry: 0059a2a4
 * Name: _InitializeCriticalSection@4
 * Namespace: Global
 * Signature: void _InitializeCriticalSection@4(LPCRITICAL_SECTION lpCriticalSection)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void _InitializeCriticalSection_4(LPCRITICAL_SECTION lpCriticalSection)

{
                    /* WARNING: Could not recover jumptable at 0x0059a2a4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  InitializeCriticalSection(lpCriticalSection);
  return;
}
