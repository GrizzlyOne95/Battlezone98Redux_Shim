/*
 * Entry: 0059a244
 * Name: _GetCurrentProcess@0
 * Namespace: Global
 * Signature: HANDLE _GetCurrentProcess@0(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

HANDLE _GetCurrentProcess_0(void)

{
  HANDLE pvVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a244. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pvVar1 = GetCurrentProcess();
  return pvVar1;
}
