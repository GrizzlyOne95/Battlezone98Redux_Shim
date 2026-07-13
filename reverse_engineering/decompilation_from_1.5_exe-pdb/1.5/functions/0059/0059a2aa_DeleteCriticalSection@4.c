/*
 * Entry: 0059a2aa
 * Name: _DeleteCriticalSection@4
 * Namespace: Global
 * Signature: void _DeleteCriticalSection@4(LPCRITICAL_SECTION lpCriticalSection)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void _DeleteCriticalSection_4(LPCRITICAL_SECTION lpCriticalSection)

{
                    /* WARNING: Could not recover jumptable at 0x0059a2aa. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  DeleteCriticalSection(lpCriticalSection);
  return;
}
