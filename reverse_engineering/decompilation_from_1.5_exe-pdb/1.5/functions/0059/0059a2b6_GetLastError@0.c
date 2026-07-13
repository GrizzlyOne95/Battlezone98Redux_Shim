/*
 * Entry: 0059a2b6
 * Name: _GetLastError@0
 * Namespace: Global
 * Signature: DWORD _GetLastError@0(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

DWORD _GetLastError_0(void)

{
  DWORD DVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a2b6. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  DVar1 = GetLastError();
  return DVar1;
}
