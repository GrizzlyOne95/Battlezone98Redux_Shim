/*
 * Entry: 0059a32e
 * Name: _GetSystemInfo@4
 * Namespace: Global
 * Signature: void _GetSystemInfo@4(LPSYSTEM_INFO lpSystemInfo)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void _GetSystemInfo_4(LPSYSTEM_INFO lpSystemInfo)

{
                    /* WARNING: Could not recover jumptable at 0x0059a32e. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  GetSystemInfo(lpSystemInfo);
  return;
}
