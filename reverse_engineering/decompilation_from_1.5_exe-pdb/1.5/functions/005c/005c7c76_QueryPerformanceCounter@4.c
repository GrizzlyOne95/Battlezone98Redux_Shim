/*
 * Entry: 005c7c76
 * Name: _QueryPerformanceCounter@4
 * Namespace: Global
 * Signature: BOOL _QueryPerformanceCounter@4(LARGE_INTEGER * lpPerformanceCount)
 * Symbol source: IMPORTED
 * Export status: ok
 */

BOOL _QueryPerformanceCounter_4(LARGE_INTEGER *lpPerformanceCount)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x005c7c76. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = QueryPerformanceCounter(lpPerformanceCount);
  return BVar1;
}
