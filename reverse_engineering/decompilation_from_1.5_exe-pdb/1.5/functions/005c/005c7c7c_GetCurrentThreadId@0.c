/*
 * Entry: 005c7c7c
 * Name: _GetCurrentThreadId@0
 * Namespace: Global
 * Signature: DWORD _GetCurrentThreadId@0(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

DWORD _GetCurrentThreadId_0(void)

{
  DWORD DVar1;
  
                    /* WARNING: Could not recover jumptable at 0x005c7c7c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  DVar1 = GetCurrentThreadId();
  return DVar1;
}
