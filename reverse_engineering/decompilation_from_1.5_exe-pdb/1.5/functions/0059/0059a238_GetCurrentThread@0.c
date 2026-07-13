/*
 * Entry: 0059a238
 * Name: _GetCurrentThread@0
 * Namespace: Global
 * Signature: HANDLE _GetCurrentThread@0(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

HANDLE _GetCurrentThread_0(void)

{
  HANDLE pvVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a238. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pvVar1 = GetCurrentThread();
  return pvVar1;
}
