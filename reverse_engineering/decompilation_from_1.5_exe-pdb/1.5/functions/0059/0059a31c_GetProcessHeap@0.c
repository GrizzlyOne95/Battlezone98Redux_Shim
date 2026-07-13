/*
 * Entry: 0059a31c
 * Name: _GetProcessHeap@0
 * Namespace: Global
 * Signature: HANDLE _GetProcessHeap@0(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

HANDLE _GetProcessHeap_0(void)

{
  HANDLE pvVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a31c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pvVar1 = GetProcessHeap();
  return pvVar1;
}
