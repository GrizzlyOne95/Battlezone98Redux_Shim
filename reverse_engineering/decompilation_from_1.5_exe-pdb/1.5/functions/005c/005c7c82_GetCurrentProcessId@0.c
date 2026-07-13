/*
 * Entry: 005c7c82
 * Name: _GetCurrentProcessId@0
 * Namespace: Global
 * Signature: DWORD _GetCurrentProcessId@0(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

DWORD _GetCurrentProcessId_0(void)

{
  DWORD DVar1;
  
                    /* WARNING: Could not recover jumptable at 0x005c7c82. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  DVar1 = GetCurrentProcessId();
  return DVar1;
}
