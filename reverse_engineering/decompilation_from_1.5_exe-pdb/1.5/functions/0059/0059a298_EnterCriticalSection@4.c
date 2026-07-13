/*
 * Entry: 0059a298
 * Name: _EnterCriticalSection@4
 * Namespace: Global
 * Signature: void _EnterCriticalSection@4(LPCRITICAL_SECTION lpCriticalSection)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void _EnterCriticalSection_4(LPCRITICAL_SECTION lpCriticalSection)

{
                    /* WARNING: Could not recover jumptable at 0x0059a298. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  EnterCriticalSection(lpCriticalSection);
  return;
}
