/*
 * Entry: 005c7c88
 * Name: _GetSystemTimeAsFileTime@4
 * Namespace: Global
 * Signature: void _GetSystemTimeAsFileTime@4(LPFILETIME lpSystemTimeAsFileTime)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void _GetSystemTimeAsFileTime_4(LPFILETIME lpSystemTimeAsFileTime)

{
                    /* WARNING: Could not recover jumptable at 0x005c7c88. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  GetSystemTimeAsFileTime(lpSystemTimeAsFileTime);
  return;
}
